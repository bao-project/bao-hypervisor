/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 *
 * Minimal ARM SMMUv3 (IHI 0070) driver for Bao — stage-2-only.
 *
 * See arch/smmuv3.h for the design summary. The driver takes over the live
 * non-secure SMMU that firmware leaves enabled: it installs a linear stream
 * table (every entry aborts until a VM binds it), a command queue, and
 * promotes individual streams to stage-2 translation as VMs bind them.
 * Runtime stage-2 invalidation rides on broadcast TLB maintenance.
 */

#include <arch/smmuv3.h>
#include <arch/spinlock.h>
#include <arch/fences.h>
#include <arch/page_table.h>
#include <platform.h>
#include <config.h>
#include <cpu.h>
#include <mem.h>
#include <string.h>
#include <bit.h>

#define SMMUV3_CMDQ_LOG2SIZE (7) /* 128 entries x 16 B = 2 KiB */

#define SMMUV3_POLL_LIMIT    (1000000)

struct smmuv3_priv {
    volatile struct smmuv3_hw* hw;

    struct smmuv3_ste* st;
    size_t st_log2size;
    size_t st_entries;

    uint64_t* cmdq;
    uint32_t cmdq_prod; /* raw producer counter, modulo 2*size */

    spinlock_t lock;
};

/* Deliberately a single global instance: this driver assumes one SMMU per SoC.
 * A streamID is only unique within a given instance's stream table, so adding
 * multi-SMMU support later means threading a per-group "which SMMU" selector
 * through struct smmu_group (arch/vm.h) down to here. Kept single for now. */

static struct smmuv3_priv smmu;

/* On a coherent SMMU a barrier is enough for table and queue updates. */
static inline void smmuv3_push(vaddr_t addr, size_t size)
{
    UNUSED_ARG(addr);
    UNUSED_ARG(size);
    fence_sync_write();
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
    uint32_t aidr = smmu.hw->AIDR & SMMUV3_AIDR_ARCHMINOR_MASK;
    if (aidr > 2) {
        WARNING("smmuv3: unexpected arch version AIDR=0x%x\n", aidr);
    }

    if (!(smmu.hw->IDR0 & SMMUV3_IDR0_S2P_BIT)) {
        ERROR("smmuv3 does not support stage-2 translation\n");
    }

    if (!(smmu.hw->IDR0 & SMMUV3_IDR0_COHACC_BIT)) {
        ERROR("smmuv3 requires coherent table walks (COHACC)\n");
    }

    if (!(smmu.hw->IDR0 & SMMUV3_IDR0_BTM_BIT)) {
        ERROR("smmuv3 does not support tlb maintenance broadcast\n");
    }

    if (!(smmu.hw->IDR5 & SMMUV3_IDR5_GRAN4K_BIT)) {
        ERROR("smmuv3 does not support 4kb granule\n");
    }

    size_t oas = bit32_extract(smmu.hw->IDR5, SMMUV3_IDR5_OAS_OFF, SMMUV3_IDR5_OAS_LEN);
    if (oas < parange) {
        ERROR("smmuv3 OAS (%d) smaller than platform parange (%d)\n", oas, parange);
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
    WARNING("smmuv3: CMD_SYNC timed out (CONS=0x%x PROD=0x%x)\n", smmu.hw->CMDQ_CONS,
        smmu.cmdq_prod);
}

static void smmuv3_cmdq_cfgi_ste(streamid_t sid)
{
    smmuv3_cmdq_push(CMD_OP_CFGI_STE | ((uint64_t)sid << CMD_CFGI_SID_OFF), CMD_CFGI_STE_LEAF);
}

/* Smallest linear table that covers StreamIDs 0..max_sid, capped at SIDSIZE.
 * IDs above the table fault with C_BAD_STREAMID. */
static size_t smmuv3_stream_table_log2size(size_t sidsize)
{
    size_t max_sid = 0;

    for (size_t v = 0; v < config.vmlist_size; v++) {
        const struct vm_config* cfg = &config.vmlist[v];

        for (size_t d = 0; d < cfg->platform.dev_num; d++) {
            deviceid_t id = cfg->platform.devs[d].id;
            if ((id != 0) && ((size_t)id > max_sid)) {
                max_sid = id;
            }
        }

        for (size_t g = 0; g < cfg->platform.arch.smmu.group_num; g++) {
            const struct smmu_group* group = &cfg->platform.arch.smmu.groups[g];
            size_t top = (size_t)(group->id | group->mask);
            if (top > max_sid) {
                max_sid = top;
            }
        }
    }

    size_t log2size = 0;
    size_t span = 1;
    while ((span <= max_sid) && (log2size < sidsize)) {
        log2size++;
        span <<= 1;
    }

    if (span <= max_sid) {
        ERROR("smmuv3: stream id 0x%lx exceeds SIDSIZE (%u)\n", (unsigned long)max_sid,
            (unsigned)sidsize);
    }

    return log2size;
}

void smmuv3_init(void)
{
    smmu.lock = SPINLOCK_INITVAL;

    vaddr_t regs = mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA,
        platform.arch.smmu.base, NUM_PAGES(sizeof(struct smmuv3_hw)));
    smmu.hw = (volatile struct smmuv3_hw*)regs;

    smmuv3_check_features();

    size_t sidsize = bit32_extract(smmu.hw->IDR1, SMMUV3_IDR1_SIDSIZE_OFF, SMMUV3_IDR1_SIDSIZE_LEN);
    smmu.st_log2size = smmuv3_stream_table_log2size(sidsize);
    smmu.st_entries = 1UL << smmu.st_log2size;

    size_t st_bytes = smmu.st_entries * sizeof(struct smmuv3_ste);
    smmu.st =
        (struct smmuv3_ste*)mem_alloc_page(NUM_PAGES(st_bytes), SEC_HYP_GLOBAL, MEM_ALIGN_REQ);
    /* V=0 is an invalid STE: the stream aborts. IDs past the table abort too,
     * with C_BAD_STREAMID, so an unbound master is contained either way. */
    memset(smmu.st, 0, st_bytes);
    smmuv3_push((vaddr_t)smmu.st, st_bytes);

    size_t cmdq_bytes = (1UL << SMMUV3_CMDQ_LOG2SIZE) * SMMUV3_CMDQ_ENT_DWORDS * sizeof(uint64_t);
    smmu.cmdq = (uint64_t*)mem_alloc_page(NUM_PAGES(cmdq_bytes), SEC_HYP_GLOBAL, MEM_ALIGN_REQ);
    memset(smmu.cmdq, 0, cmdq_bytes);
    smmu.cmdq_prod = 0;
    smmuv3_push((vaddr_t)smmu.cmdq, cmdq_bytes);

    paddr_t st_pa, cmdq_pa;
    mem_translate(&cpu()->as, (vaddr_t)smmu.st, &st_pa);
    mem_translate(&cpu()->as, (vaddr_t)smmu.cmdq, &cmdq_pa);

    /* Quiesce the SMMU firmware left enabled. GBPA.ABORT terminates transactions
     * while SMMUEN is clear, same policy as an unbound STE. */
    smmu.hw->GBPA = SMMUV3_GBPA_UPDATE | SMMUV3_GBPA_ABORT;
    if (smmuv3_poll(&smmu.hw->GBPA, SMMUV3_GBPA_UPDATE, 0) != 0) {
        ERROR("smmuv3: GBPA update did not complete\n");
    }
    smmu.hw->CR0 = 0;
    if (smmuv3_poll(&smmu.hw->CR0ACK, SMMUV3_CR0_SMMUEN | SMMUV3_CR0_CMDQEN | SMMUV3_CR0_EVENTQEN,
            0) != 0) {
        ERROR("smmuv3: failed to quiesce CR0\n");
    }

    /* Table/queue access attributes: inner-shareable, write-back cacheable.
     * CR2 = 0 clears PTM (so broadcast TLBIs are honoured) and VMW (exact
     * VMID match). PTM is not a reliable reset value. */
    smmu.hw->CR1 = SMMUV3_CR1_DEFAULT;
    smmu.hw->CR2 = 0;

    smmu.hw->STRTAB_BASE = (st_pa & SMMUV3_STRTAB_BASE_ADDR_MASK) | SMMUV3_STRTAB_BASE_RA;
    /* TODO: a 2-level stream table, when SMMU_IDR0.ST_LEVEL allows it, is the
     * proper fix for a large or sparse StreamID space. The linear table below
     * only covers the IDs the config actually uses. */
    smmu.hw->STRTAB_BASE_CFG = SMMUV3_STRTAB_BASE_CFG_FMT_LINEAR | (uint32_t)smmu.st_log2size;

    smmu.hw->CMDQ_BASE =
        (cmdq_pa & SMMUV3_Q_BASE_ADDR_MASK) | SMMUV3_Q_BASE_RA | SMMUV3_CMDQ_LOG2SIZE;
    smmu.hw->CMDQ_PROD = 0;
    smmu.hw->CMDQ_CONS = 0;
    fence_sync_write();

    smmu.hw->CR0 = SMMUV3_CR0_CMDQEN;
    if (smmuv3_poll(&smmu.hw->CR0ACK, SMMUV3_CR0_CMDQEN, SMMUV3_CR0_CMDQEN) != 0) {
        ERROR("smmuv3: CMDQEN not acknowledged\n");
    }

    /* Drop any stale config/TLB the SMMU cached from firmware's stream table. */
    spin_lock(&smmu.lock);
    smmuv3_cmdq_push(CMD_OP_CFGI_STE_RANGE, CMD_CFGI_STE_RANGE_ALL);
    smmuv3_cmdq_push(CMD_OP_TLBI_NSNH_ALL, 0);
    smmuv3_cmdq_sync();
    spin_unlock(&smmu.lock);

    smmu.hw->CR0 = SMMUV3_CR0_CMDQEN | SMMUV3_CR0_SMMUEN;
    if (smmuv3_poll(&smmu.hw->CR0ACK, SMMUV3_CR0_SMMUEN, SMMUV3_CR0_SMMUEN) != 0) {
        ERROR("smmuv3: SMMUEN not acknowledged\n");
    }

    INFO("smmuv3: enabled, %d stream-table entries\n", (int)smmu.st_entries);
}

bool smmuv3_write_ste_s2(streamid_t sid, paddr_t root_pt, uint16_t vmid)
{
    if (sid >= smmu.st_entries) {
        INFO("smmuv3: stream id %d exceeds stream table (%d entries)\n", sid, (int)smmu.st_entries);
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

    uint64_t w0 = STE_W0_V | (STE_W0_CONFIG_S2 << STE_W0_CONFIG_OFF);
    uint64_t w3 = root_pt & STE_W3_S2TTB_MASK;

    spin_lock(&smmu.lock);
    struct smmuv3_ste* e = &smmu.st[sid];

    if ((e->data[0] & STE_W0_V) != 0) {
        if ((e->data[0] == w0) && (e->data[2] == w2) && (e->data[3] == w3)) {
            spin_unlock(&smmu.lock);
            return true;
        }
        ERROR("smmuv3: stream id %d already bound\n", sid);
    }

    /* Clear valid first so the SMMU never sees a half-written translate STE. */
    e->data[0] = 0;
    smmuv3_push((vaddr_t)e, sizeof(*e));
    smmuv3_cmdq_cfgi_ste(sid);
    smmuv3_cmdq_sync();

    e->data[1] = 0;
    e->data[2] = w2;
    e->data[3] = w3;
    e->data[4] = 0;
    e->data[5] = 0;
    e->data[6] = 0;
    e->data[7] = 0;
    smmuv3_push((vaddr_t)e, sizeof(*e));

    e->data[0] = w0;
    smmuv3_push((vaddr_t)e, sizeof(*e));

    /* Config caches are not covered by broadcast TLBI, so the new STE still
     * needs CFGI_STE. Stage-2 TLB invalidation rides on DVM: CR2.PTM is clear
     * and this STE is tagged with the CPU VMID. */
    smmuv3_cmdq_cfgi_ste(sid);
    smmuv3_cmdq_sync();
    spin_unlock(&smmu.lock);

    INFO("smmuv3: stream %d -> stage-2 (vmid %d, s2ttb 0x%lx)\n", sid, vmid, (unsigned long)w3);
    return true;
}
