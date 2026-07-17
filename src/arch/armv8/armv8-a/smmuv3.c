/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 *
 * Minimal ARM SMMUv3 (IHI 0070) driver for Bao — stage-2-only.
 *
 * See arch/smmuv3.h for the design summary. The driver takes over the live
 * non-secure SMMU that firmware (TF-A) leaves enabled: it installs its own
 * linear stream table (all entries BYPASS so masters keep working with their
 * incoming attributes, matching the firmware handoff), command queue and event
 * queue, then promotes individual streams to stage-2 translation as VMs bind
 * them.
 */

#include <arch/smmuv3.h>
#include <arch/spinlock.h>
#include <arch/fences.h>
#include <arch/page_table.h>
#include <platform.h>
#include <cpu.h>
#include <mem.h>
#include <cache.h>
#include <string.h>
#include <bit.h>
#include <interrupts.h>

/* Linear stream table cap: 2^SMMUV3_ST_LOG2_CAP entries (default 2^8 = 256,
 * 16 KiB). A platform whose stream-ID space is sparse or starts high can
 * override this from its platform.mk (e.g. -DSMMUV3_ST_LOG2_CAP=11). */
#ifndef SMMUV3_ST_LOG2_CAP
#define SMMUV3_ST_LOG2_CAP   (8)
#endif
#define SMMUV3_CMDQ_LOG2SIZE (7) /* 128 entries x 16 B = 2 KiB */
#define SMMUV3_EVTQ_LOG2SIZE (7) /* 128 entries x 32 B = 4 KiB */

#define SMMUV3_POLL_LIMIT    (1000000)

struct smmuv3_priv {
    volatile struct smmuv3_hw* hw;

    struct smmuv3_ste* st;
    size_t st_log2size;
    size_t st_entries;

    uint64_t* cmdq;
    uint32_t cmdq_prod; /* raw producer counter, modulo 2*size */

    uint64_t* evtq;
    /* EVENTQ producer/consumer indices live in SMMU page 1 (offset 0x10000); the
     * page-0 0xA8/0xAC copies are RAZ/WI aliases on real silicon. */
    volatile uint32_t* evtq_prod;
    volatile uint32_t* evtq_cons;

    bool coherent;      /* SMMU performs coherent table/queue accesses */
    volatile bool ready; /* published last; gates the poll hook (see below) */
    spinlock_t lock;
};

/* Deliberately a single global instance: this driver assumes one SMMU per SoC.
 * A streamID is only unique within a given instance's stream table, so adding
 * multi-SMMU support later means threading a per-group "which SMMU" selector
 * through struct smmu_group (arch/vm.h) down to here. Kept single for now. */

#define SMMUV3_PAGE1_OFF         (0x10000UL)
#define SMMUV3_PAGE1_EVENTQ_PROD (SMMUV3_PAGE1_OFF + 0xA8UL)
#define SMMUV3_PAGE1_EVENTQ_CONS (SMMUV3_PAGE1_OFF + 0xACUL)

static struct smmuv3_priv smmu;

/* Clean (and on non-coherent SMMUs, flush) a structure we wrote so the SMMU's
 * table/queue walk observes it. On coherent SMMUs a barrier is enough. */
static inline void smmuv3_push(vaddr_t addr, size_t size)
{
    if (smmu.coherent) {
        fence_sync_write();
    } else {
        cache_flush_range(addr, size);
    }
}

static int smmuv3_poll(volatile uint32_t* reg, uint32_t mask, uint32_t val)
{
    for (size_t i = 0; i < SMMUV3_POLL_LIMIT; i++) {
        if ((*reg & mask) == val) {
            return 0;
        }
    }
    return -1;
}

static void smmuv3_check_features(void)
{
    uint32_t aidr = smmu.hw->AIDR & 0xF;
    if (aidr > 2) {
        WARNING("smmuv3: unexpected arch version AIDR=0x%x", aidr);
    }

    if (!(smmu.hw->IDR0 & SMMUV3_IDR0_S2P_BIT)) {
        ERROR("smmuv3 does not support stage-2 translation");
    }

    if (!(smmu.hw->IDR5 & SMMUV3_IDR5_GRAN4K_BIT)) {
        ERROR("smmuv3 does not support 4kb granule");
    }

    size_t oas = bit32_extract(smmu.hw->IDR5, SMMUV3_IDR5_OAS_OFF, SMMUV3_IDR5_OAS_LEN);
    if (oas < parange) {
        ERROR("smmuv3 OAS (%d) smaller than platform parange (%d)", oas, parange);
    }
}

/* Push a 128-bit command into the queue and advance the producer index. The
 * caller must hold smmu.lock. */
static void smmuv3_cmdq_push(uint64_t dword0, uint64_t dword1)
{
    size_t idx = smmu.cmdq_prod & SMMUV3_Q_IDX_MASK(SMMUV3_CMDQ_LOG2SIZE);
    smmu.cmdq[idx * SMMUV3_CMDQ_ENT_DWORDS] = dword0;
    smmu.cmdq[idx * SMMUV3_CMDQ_ENT_DWORDS + 1] = dword1;
    smmuv3_push((vaddr_t)&smmu.cmdq[idx * SMMUV3_CMDQ_ENT_DWORDS],
        SMMUV3_CMDQ_ENT_DWORDS * sizeof(uint64_t));

    /* Producer counter is kept modulo 2*size so its low (log2size+1) bits are
     * exactly the {WRAP, INDEX} encoding the hardware expects. */
    smmu.cmdq_prod = (smmu.cmdq_prod + 1) & ((SMMUV3_Q_WRAP(SMMUV3_CMDQ_LOG2SIZE) << 1) - 1);
    fence_sync_write();
    smmu.hw->CMDQ_PROD = smmu.cmdq_prod;
}

/* Issue CMD_SYNC and wait for the command queue to drain. */
static void smmuv3_cmdq_sync(void)
{
    smmuv3_cmdq_push(CMD_OP_SYNC | CMD_SYNC_CS_NONE, 0);

    /* Compare the full {WRAP, INDEX} field: masking only the index bits makes a
     * completely full queue (PROD = CONS + size) indistinguishable from empty.
     * cmdq_prod is kept modulo 2*size and hardware maintains the wrap bit in
     * CMDQ_CONS, so the full-field compare is robust even under batching. */
    uint32_t fullmask = (SMMUV3_Q_WRAP(SMMUV3_CMDQ_LOG2SIZE) << 1) - 1;
    for (size_t i = 0; i < SMMUV3_POLL_LIMIT; i++) {
        if ((smmu.hw->CMDQ_CONS & fullmask) == (smmu.cmdq_prod & fullmask)) {
            return;
        }
    }
    WARNING("smmuv3: CMD_SYNC timed out (CONS=0x%x PROD=0x%x)", smmu.hw->CMDQ_CONS, smmu.cmdq_prod);
}

static void smmuv3_cmdq_cfgi_ste(streamid_t sid)
{ smmuv3_cmdq_push(CMD_OP_CFGI_STE | ((uint64_t)sid << CMD_CFGI_SID_OFF), CMD_CFGI_STE_LEAF); }

static void smmuv3_cmdq_tlbi_vmid(uint16_t vmid)
{ smmuv3_cmdq_push(CMD_OP_TLBI_S12_VMALL | ((uint64_t)vmid << CMD_TLBI_VMID_OFF), 0); }

/* Populate an STE as BYPASS, passing the master's incoming attributes through
 * unchanged (SHCFG=use-incoming). This deliberately does NOT override
 * shareability/memory-type so that masters the firmware left in bypass behave
 * exactly as before Bao touched the SMMU. */
static void smmuv3_ste_fill_bypass(struct smmuv3_ste* e)
{
    memset(e, 0, sizeof(*e));
    e->data[1] = STE_W1_SHCFG_USE_INCOMING << STE_W1_SHCFG_OFF;
    fence_sync_write();
    e->data[0] = STE_W0_V | (STE_W0_CONFIG_BYPASS << STE_W0_CONFIG_OFF);
}

/* Populate an STE as ABORT: an invalid STE (V=0) terminates any transaction
 * from that stream and records a C_BAD_STE fault in the event queue, so an
 * un-enumerated master is stopped instead of DMAing freely. */
#ifdef SMMUV3_DEFAULT_ABORT
static void smmuv3_ste_fill_abort(struct smmuv3_ste* e)
{
    memset(e, 0, sizeof(*e)); /* V=0 -> abort + fault record */
}
#endif

/* Default STE for streams no VM has bound. BYPASS by default so the firmware
 * handoff stays transparent (masters keep working with incoming attributes). A
 * platform with a fully-known streamID map can flip the default to ABORT --
 * turning the SMMU into an isolation boundary -- via -DSMMUV3_DEFAULT_ABORT in
 * its platform.mk. Note this only changes the unbound default; GBPA is kept in
 * BYPASS during the reconfiguration window regardless (see smmuv3_init), so
 * in-flight transactions during handoff never fault. */
static void smmuv3_ste_fill_default(struct smmuv3_ste* e)
{
#ifdef SMMUV3_DEFAULT_ABORT
    smmuv3_ste_fill_abort(e);
#else
    smmuv3_ste_fill_bypass(e);
#endif
}

/* Drain + log the event queue. Each record is a translation/permission/etc.
 * fault: a DMA the SMMU refused. On a correctly-bound, well-behaved system this
 * stays empty; any line here is a master accessing memory it isn't allowed to
 * (the IOMMU doing its job) -- so we surface it loudly. Caller holds smmu.lock. */
static void smmuv3_drain_events(void)
{
    uint32_t wrapmask = (SMMUV3_Q_WRAP(SMMUV3_EVTQ_LOG2SIZE) << 1) - 1;
    uint32_t idxmask = SMMUV3_Q_IDX_MASK(SMMUV3_EVTQ_LOG2SIZE);
    uint32_t prod = *smmu.evtq_prod & wrapmask;
    uint32_t cons = *smmu.evtq_cons & wrapmask;

    while (cons != prod) {
        uint64_t* e = &smmu.evtq[(cons & idxmask) * SMMUV3_EVTQ_ENT_DWORDS];
        if (!smmu.coherent) {
            cache_flush_range((vaddr_t)e, SMMUV3_EVTQ_ENT_DWORDS * sizeof(uint64_t));
        }
        WARNING("smmuv3 FAULT: type=0x%x stream=%d addr=0x%lx [%lx %lx]",
            (unsigned)(e[0] & SMMUV3_EVT_TYPE_MASK), (int)(e[0] >> SMMUV3_EVT_SID_OFF),
            (unsigned long)e[2], (unsigned long)e[0], (unsigned long)e[1]);
        cons = (cons + 1) & wrapmask;
    }
    fence_sync_write();
    *smmu.evtq_cons = cons;
}

static void smmuv3_eventq_irq_handler(irqid_t id)
{
    (void)id;
    spin_lock(&smmu.lock);
    smmuv3_drain_events();
    spin_unlock(&smmu.lock);
}

/* Cheap poll hook called from the GIC IRQ path: if the SMMU event queue is
 * non-empty, drain+log it. This makes faults visible even if the dedicated
 * wired event IRQ isn't delivered. No-op until the driver is initialised. */
void smmuv3_poll_events(void)
{
    if (!smmu.ready) {
        return;
    }
    /* Acquire: order the ready load before the queue-state loads below. A
     * control dependency alone doesn't order load->load on ARMv8, so without
     * this a core that just saw ready==true could still read a stale evtq /
     * PROD-CONS pair set up before the flag was published. Pairs with the
     * release barrier before "smmu.ready = true" in smmuv3_init(). */
    fence_ord_read();
    uint32_t wrapmask = (SMMUV3_Q_WRAP(SMMUV3_EVTQ_LOG2SIZE) << 1) - 1;
    if ((*smmu.evtq_prod & wrapmask) == (*smmu.evtq_cons & wrapmask)) {
        return; /* empty -- common case, no lock taken */
    }
    spin_lock(&smmu.lock);
    smmuv3_drain_events();
    spin_unlock(&smmu.lock);
}

void smmuv3_init(void)
{
    smmu.lock = SPINLOCK_INITVAL;

    /* Map page 0 (the registers in struct smmuv3_hw) AND page 1 (offset 0x10000,
     * which holds the architectural EVENTQ_PROD/CONS). */
    vaddr_t regs = mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA,
        platform.arch.smmu.base, NUM_PAGES(SMMUV3_PAGE1_EVENTQ_CONS + 4));
    smmu.hw = (volatile struct smmuv3_hw*)regs;
    smmu.evtq_prod = (volatile uint32_t*)(regs + SMMUV3_PAGE1_EVENTQ_PROD);
    smmu.evtq_cons = (volatile uint32_t*)(regs + SMMUV3_PAGE1_EVENTQ_CONS);

    smmu.coherent = (smmu.hw->IDR0 & SMMUV3_IDR0_COHACC_BIT) != 0;
    smmuv3_check_features();

    /* Linear stream table sized to min(SIDSIZE, cap). */
    size_t sidsize = bit32_extract(smmu.hw->IDR1, SMMUV3_IDR1_SIDSIZE_OFF, SMMUV3_IDR1_SIDSIZE_LEN);
    smmu.st_log2size = (sidsize < SMMUV3_ST_LOG2_CAP) ? sidsize : SMMUV3_ST_LOG2_CAP;
    smmu.st_entries = 1UL << smmu.st_log2size;

    size_t st_bytes = smmu.st_entries * sizeof(struct smmuv3_ste);
    smmu.st =
        (struct smmuv3_ste*)mem_alloc_page(NUM_PAGES(st_bytes), SEC_HYP_GLOBAL, MEM_ALIGN_REQ);
    for (size_t i = 0; i < smmu.st_entries; i++) {
        smmuv3_ste_fill_default(&smmu.st[i]);
    }
    smmuv3_push((vaddr_t)smmu.st, st_bytes);

    /* Command queue + event queue. */
    size_t cmdq_bytes = (1UL << SMMUV3_CMDQ_LOG2SIZE) * SMMUV3_CMDQ_ENT_DWORDS * sizeof(uint64_t);
    smmu.cmdq = (uint64_t*)mem_alloc_page(NUM_PAGES(cmdq_bytes), SEC_HYP_GLOBAL, MEM_ALIGN_REQ);
    memset(smmu.cmdq, 0, cmdq_bytes);
    smmu.cmdq_prod = 0;

    size_t evtq_bytes = (1UL << SMMUV3_EVTQ_LOG2SIZE) * SMMUV3_EVTQ_ENT_DWORDS * sizeof(uint64_t);
    smmu.evtq = (uint64_t*)mem_alloc_page(NUM_PAGES(evtq_bytes), SEC_HYP_GLOBAL, MEM_ALIGN_REQ);
    memset(smmu.evtq, 0, evtq_bytes);
    smmuv3_push((vaddr_t)smmu.cmdq, cmdq_bytes);
    smmuv3_push((vaddr_t)smmu.evtq, evtq_bytes);

    paddr_t st_pa, cmdq_pa, evtq_pa;
    mem_translate(&cpu()->as, (vaddr_t)smmu.st, &st_pa);
    mem_translate(&cpu()->as, (vaddr_t)smmu.cmdq, &cmdq_pa);
    mem_translate(&cpu()->as, (vaddr_t)smmu.evtq, &evtq_pa);

    /* Quiesce the SMMU that firmware left enabled before re-pointing its tables.
     * Keep GBPA in BYPASS (not ABORT) so that any in-flight transaction during
     * the reconfiguration window passes through rather than faulting. */
    smmu.hw->GBPA = SMMUV3_GBPA_UPDATE | (STE_W1_SHCFG_USE_INCOMING << 12);
    if (smmuv3_poll(&smmu.hw->GBPA, SMMUV3_GBPA_UPDATE, 0) != 0) {
        ERROR("smmuv3: GBPA update did not complete");
    }
    smmu.hw->CR0 = 0;
    if (smmuv3_poll(&smmu.hw->CR0ACK, SMMUV3_CR0_SMMUEN | SMMUV3_CR0_CMDQEN | SMMUV3_CR0_EVENTQEN,
            0) != 0) {
        ERROR("smmuv3: failed to quiesce CR0");
    }

    /* Table/queue access attributes: inner-shareable, write-back cacheable. */
    smmu.hw->CR1 = SMMUV3_CR1_DEFAULT;

    smmu.hw->STRTAB_BASE = (st_pa & SMMUV3_STRTAB_BASE_ADDR_MASK) | SMMUV3_STRTAB_BASE_RA;
    smmu.hw->STRTAB_BASE_CFG = SMMUV3_STRTAB_BASE_CFG_FMT_LINEAR | (uint32_t)smmu.st_log2size;

    smmu.hw->CMDQ_BASE =
        (cmdq_pa & SMMUV3_Q_BASE_ADDR_MASK) | SMMUV3_Q_BASE_RA | SMMUV3_CMDQ_LOG2SIZE;
    smmu.hw->CMDQ_PROD = 0;
    smmu.hw->CMDQ_CONS = 0;

    smmu.hw->EVENTQ_BASE =
        (evtq_pa & SMMUV3_Q_BASE_ADDR_MASK) | SMMUV3_Q_BASE_RA | SMMUV3_EVTQ_LOG2SIZE;
    *smmu.evtq_prod = 0;
    *smmu.evtq_cons = 0;
    fence_sync_write();

    /* Enable command processing, then event queue. */
    smmu.hw->CR0 = SMMUV3_CR0_CMDQEN;
    if (smmuv3_poll(&smmu.hw->CR0ACK, SMMUV3_CR0_CMDQEN, SMMUV3_CR0_CMDQEN) != 0) {
        ERROR("smmuv3: CMDQEN not acknowledged");
    }
    smmu.hw->CR0 = SMMUV3_CR0_CMDQEN | SMMUV3_CR0_EVENTQEN;
    if (smmuv3_poll(&smmu.hw->CR0ACK, SMMUV3_CR0_EVENTQEN, SMMUV3_CR0_EVENTQEN) != 0) {
        ERROR("smmuv3: EVENTQEN not acknowledged");
    }

    /* Route the event-queue fault interrupt (wired SPI) to a handler that drains
     * + logs faults, so a refused DMA is visible instead of silent. */
    if (platform.arch.smmu.interrupt_id != 0) {
        irqid_t eid =
            interrupts_reserve(platform.arch.smmu.interrupt_id, smmuv3_eventq_irq_handler);
        if (eid != INVALID_IRQID) {
            interrupts_cpu_enable(eid, true);
            smmu.hw->IRQ_CTRL = SMMUV3_IRQ_CTRL_EVENTQ | SMMUV3_IRQ_CTRL_GERROR;
            if (smmuv3_poll(&smmu.hw->IRQ_CTRLACK, SMMUV3_IRQ_CTRL_EVENTQ,
                    SMMUV3_IRQ_CTRL_EVENTQ) != 0) {
                WARNING("smmuv3: IRQ_CTRL not acknowledged; fault IRQ may be inactive");
            }
        } else {
            INFO("smmuv3: could not reserve event irq %d", platform.arch.smmu.interrupt_id);
        }
    }

    /* Drop any stale config/TLB the SMMU cached from firmware's stream table. */
    spin_lock(&smmu.lock);
    smmuv3_cmdq_push(CMD_OP_CFGI_STE_RANGE, CMD_CFGI_STE_RANGE_ALL);
    smmuv3_cmdq_push(CMD_OP_TLBI_NSNH_ALL, 0);
    smmuv3_cmdq_sync();
    spin_unlock(&smmu.lock);

    /* Finally re-enable translation against our stream table. */
    smmu.hw->CR0 = SMMUV3_CR0_CMDQEN | SMMUV3_CR0_EVENTQEN | SMMUV3_CR0_SMMUEN;
    if (smmuv3_poll(&smmu.hw->CR0ACK, SMMUV3_CR0_SMMUEN, SMMUV3_CR0_SMMUEN) != 0) {
        ERROR("smmuv3: SMMUEN not acknowledged");
    }

    /* Publish "ready" last, once SMMUEN is acked and everything the poll hook
     * touches (evtq buffer, EVENTQ_BASE, the PROD/CONS pointers and their reset
     * values) is live. Release barrier first so those prior stores are visible
     * to any other core before it observes ready==true; the poll hook does the
     * matching acquire. Without this a secondary CPU taking an IRQ mid-init
     * could see ready==true while smmu.evtq is still NULL from its viewpoint. */
    fence_ord_write();
    smmu.ready = true;

    INFO("smmuv3: enabled, %d stream-table entries, %s table walks", (int)smmu.st_entries,
        smmu.coherent ? "coherent" : "non-coherent");
}

bool smmuv3_write_ste_bypass(streamid_t sid)
{
    if (sid >= smmu.st_entries) {
        INFO("smmuv3: stream id %d exceeds stream table (%d entries)", sid, (int)smmu.st_entries);
        return false;
    }

    spin_lock(&smmu.lock);
    struct smmuv3_ste* e = &smmu.st[sid];
    e->data[0] = 0; /* invalidate while we rewrite */
    smmuv3_push((vaddr_t)e, sizeof(*e));
    smmuv3_cmdq_cfgi_ste(sid);
    smmuv3_cmdq_sync();

    smmuv3_ste_fill_bypass(e);
    smmuv3_push((vaddr_t)e, sizeof(*e));
    smmuv3_cmdq_cfgi_ste(sid);
    smmuv3_cmdq_sync();
    spin_unlock(&smmu.lock);

    return true;
}

bool smmuv3_write_ste_s2(streamid_t sid, paddr_t root_pt, uint16_t vmid)
{
    if (sid >= smmu.st_entries) {
        INFO("smmuv3: stream id %d exceeds stream table (%d entries)", sid, (int)smmu.st_entries);
        return false;
    }

    /* Stage-2 config mirrors the VTCR Bao programs for the VM's stage-2 page
     * table (see vmm_arch_init / smmuv2 smmu_write_ctxbnk): same parange-derived
     * T0SZ / start-level / PS so the SMMU walks the identical tables. */
    size_t t0sz = 64 - parange_table[parange];
    uint64_t sl0 = (parange_table[parange] < 44) ? 0x1ULL : 0x2ULL;
    uint64_t ps = (uint64_t)parange;

    uint64_t w2 = ((uint64_t)vmid << STE_W2_S2VMID_OFF) | ((uint64_t)t0sz << STE_W2_S2T0SZ_OFF) |
        (sl0 << STE_W2_S2SL0_OFF) | (STE_W2_WB << STE_W2_S2IR0_OFF) |
        (STE_W2_WB << STE_W2_S2OR0_OFF) | (STE_W2_ISH << STE_W2_S2SH0_OFF) |
        (STE_W2_TG_4K << STE_W2_S2TG_OFF) | (ps << STE_W2_S2PS_OFF) | STE_W2_S2AA64 |
        STE_W2_S2AFFD | STE_W2_S2R;

    spin_lock(&smmu.lock);
    struct smmuv3_ste* e = &smmu.st[sid];

    /* Clear valid first so the SMMU never sees a half-written translate STE. */
    e->data[0] = 0;
    smmuv3_push((vaddr_t)e, sizeof(*e));
    smmuv3_cmdq_cfgi_ste(sid);
    smmuv3_cmdq_sync();

    e->data[1] = 0;
    e->data[2] = w2;
    e->data[3] = root_pt & STE_W3_S2TTB_MASK;
    e->data[4] = 0;
    e->data[5] = 0;
    e->data[6] = 0;
    e->data[7] = 0;
    smmuv3_push((vaddr_t)e, sizeof(*e));

    e->data[0] = STE_W0_V | (STE_W0_CONFIG_S2 << STE_W0_CONFIG_OFF);
    smmuv3_push((vaddr_t)e, sizeof(*e));

    smmuv3_cmdq_cfgi_ste(sid);
    smmuv3_cmdq_tlbi_vmid(vmid);
    smmuv3_cmdq_sync();
    spin_unlock(&smmu.lock);

    /* NOTE: this TLBI at bind is the ONLY SMMU stage-2 invalidation. The driver
     * assumes a bound VM's stage-2 mappings are static afterwards -- true under
     * Bao's static-partitioning model. Nothing invalidates the SMMU when a VM
     * stage-2 is mutated at runtime (see the // TODO: inval iommu tlbs sites in
     * core/inc/tlb.h); adding dynamic remap MUST hook SMMU invalidation there or
     * the SMMU will translate against stale walk-cache/TLB entries. */

    INFO("smmuv3: stream %d -> stage-2 (vmid %d, s2ttb 0x%lx)", sid, vmid,
        (unsigned long)(root_pt & STE_W3_S2TTB_MASK));
    return true;
}
