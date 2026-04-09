/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <drivers/k3_sec_proxy.h>

/**
 * @brief Reads a 32-bit value from a memory-mapped register.
 *
 * @param addr Base address of the peripheral or register block.
 * @param offset Offset from the base address to the specific register.
 *
 * @return The 32-bit value read from the register.
 */
static inline uint32_t read_reg(paddr_t addr, paddr_t offset)
{
    return *((volatile uint32_t*)((paddr_t)(addr + offset)));
}

/**
 * @brief Writes a 32-bit value to a memory-mapped register.
 *
 * @param addr Base address of the peripheral or register block.
 * @param offset Offset from the base address to the specific register.
 * @param value The 32-bit value to write.
 */
static inline void write_reg(paddr_t addr, paddr_t offset, uint32_t value)
{
    *((volatile uint32_t*)((paddr_t)(addr + offset))) = value;
}

int32_t mbox_k3_sec_proxy_verify_thread(mbox_k3_sec_proxy_desc* sec_proxy_desc, uint8_t thread_id,
    uint8_t msg_drxn)
{
    paddr_t thread_rt_base =
        sec_proxy_desc->thread_inst.rt_base + MBOX_K3_SEC_PROXY_THREAD_OFFSET(thread_id);
    paddr_t thread_scfg_base =
        sec_proxy_desc->thread_inst.scfg_base + MBOX_K3_SEC_PROXY_THREAD_OFFSET(thread_id);

    /* check for existing errors */
    if (read_reg(thread_rt_base, MBOX_K3_SEC_PROXY_RT_THREAD_STATUS_OFFSET) &
        MBOX_K3_SEC_PROXY_RT_STATUS_ERROR_MASK) {
        ERROR("secure_proxy_thread_%d corrupted", thread_id);
        return MBOX_K3_SEC_PROXY_STATUS_CODE_THREAD_CORRUPTED;
    }

    /* validate thread drxn config */
    if ((read_reg(thread_scfg_base, MBOX_K3_SEC_PROXY_SCFG_THREAD_CTRL_OFFSET) &
            MBOX_K3_SEC_PROXY_SCFG_THREAD_CTRL_DIR_MASK) >>
            MBOX_K3_SEC_PROXY_SCFG_THREAD_CTRL_DIR_IDX !=
        msg_drxn) {
        if (MBOX_K3_SEC_PROXY_MSG_DRXN_WRITE == msg_drxn) {
            ERROR("secure_proxy_thread_%d cannot READ on WRITE thread", thread_id);
            return MBOX_K3_SEC_PROXY_STATUS_CODE_INCORRECT_DRXN;
        } else {
            ERROR("secure_proxy_thread_%d cannot WRITE on READ thread", thread_id);
            return MBOX_K3_SEC_PROXY_STATUS_CODE_INCORRECT_DRXN;
        }
    }

    /* check if msg queue has entries before txn attempt */
    if (MBOX_K3_SEC_PROXY_MSG_DRXN_READ == msg_drxn) {
        uint64_t tick_start = sysreg_cntpct_el0_read();
        uint64_t ticks_per_us = sysreg_cntfrq_el0_read() / 1000000U;
        while (0 ==
            (read_reg(thread_rt_base, MBOX_K3_SEC_PROXY_RT_THREAD_STATUS_OFFSET) &
                MBOX_K3_SEC_PROXY_RT_STATUS_CUR_CNT_MASK)) {
            if ((sysreg_cntpct_el0_read() - tick_start) >
                (sec_proxy_desc->read_timeout_us * ticks_per_us)) {
                ERROR("secure_proxy_thread_%d no entries in message queue", thread_id);
                return MBOX_K3_SEC_PROXY_STATUS_CODE_NO_DATA;
            }
        }
    }

    return MBOX_K3_SEC_PROXY_STATUS_CODE_NO_ERROR;
}

/*
 * read transaction:
 *
 * +-------------------------+
 * | 1. verify thread status |
 * +-----------+-------------+
 *             |
 *             v
 * +-----------+-------------+       +------------------------------------+
 * | 2. read whole words     | <---- | regs: base + DATA_START_OFFSET ... |
 * +-----------+-------------+       +------------------------------------+
 *             |
 *             v
 * +-----------+-------------+       +------------------------------------+
 * | 3. read & unpack trail  | <---- | reg: base + N                      |
 * |    bytes (little endian)|       | (extract from LSB)                 |
 * +-----------+-------------+       +------------------------------------+
 *             |
 *             v
 * +-----------+-------------+       +------------------------------------+
 * | 4. read trigger reg if  | <---- | trigger: base + DATA_END_OFFSET    |
 * |    not reached yet      |       +------------------------------------+
 * +-------------------------+
 */
int32_t mbox_k3_sec_proxy_read(mbox_k3_sec_proxy_desc* sec_proxy_desc, uint8_t thread_id,
    void* buffer, size_t len)
{
    /* verify thread status */
    int32_t read_status =
        mbox_k3_sec_proxy_verify_thread(sec_proxy_desc, thread_id, MBOX_K3_SEC_PROXY_MSG_DRXN_READ);
    if (MBOX_K3_SEC_PROXY_STATUS_CODE_NO_ERROR != read_status) {
        ERROR("secure_proxy_thread_%d thread verif failed", thread_id);
        return read_status;
    }

    /* perform read transaction */
    paddr_t data_reg = sec_proxy_desc->thread_inst.data_base +
        MBOX_K3_SEC_PROXY_THREAD_OFFSET(thread_id) + MBOX_K3_SEC_PROXY_DATA_START_OFFSET;

    /* read whole words first */
    uint32_t word_iterator;
    size_t num_words = len / sizeof(uint32_t);
    for (word_iterator = 0; word_iterator < num_words; word_iterator++) {
        ((uint32_t*)buffer)[word_iterator] = read_reg(data_reg, word_iterator * sizeof(uint32_t));
    }

    /* read remaining bytes */
    uint32_t trail_bytes = len % sizeof(uint32_t);
    if (0 != trail_bytes) {
        uint32_t data_trail = read_reg(data_reg, word_iterator++ * sizeof(uint32_t));

        size_t trail_iterator = len - trail_bytes;
        while (trail_bytes--) {
            ((uint8_t*)buffer)[trail_iterator++] = (uint8_t)(data_trail & 0xFFU);
            data_trail >>= 8;
        }
    }

    /* in case the completion trigger register is not accessed during the read,
     * the following access is performed, to mark the completion of the
     * transaction. */
    if ((MBOX_K3_SEC_PROXY_DATA_START_OFFSET + (word_iterator * sizeof(uint32_t))) <=
        MBOX_K3_SEC_PROXY_DATA_END_OFFSET) {
        read_reg(data_reg, MBOX_K3_SEC_PROXY_DATA_END_OFFSET - MBOX_K3_SEC_PROXY_DATA_START_OFFSET);
    }

    INFO("secure_proxy_thread_%d data READ success", thread_id);

    return read_status;
}

/*
 * write transaction:
 *
 * +-------------------------+
 * | 1. verify thread status |
 * +-----------+-------------+
 *             |
 *             v
 * +-----------+-------------+
 * | 2. check message length |
 * +-----------+-------------+
 *             |
 *             v
 * +-----------+-------------+       +------------------------------------+
 * | 3. write whole words    | ----> | regs: base + DATA_START_OFFSET ... |
 * +-----------+-------------+       +------------------------------------+
 *             |
 *             v
 * +-----------+-------------+       +------------------------------------+
 * | 4. pack & write trail   | ----> | reg: base + N                      |
 * |    bytes (little endian)|       | (right-aligned/LSB)                |
 * +-----------+-------------+       +------------------------------------+
 *             |
 *             v
 * +-----------+-------------+       +------------------------------------+
 * | 5. pad with zeros until | ----> | trigger: base + DATA_END_OFFSET    |
 * |    end offset (trigger) |       +------------------------------------+
 * +-------------------------+
 */
int32_t mbox_k3_sec_proxy_write(mbox_k3_sec_proxy_desc* sec_proxy_desc, uint8_t thread_id,
    void* buffer, size_t len)
{
    /* verify thread status */
    int32_t write_status = mbox_k3_sec_proxy_verify_thread(sec_proxy_desc, thread_id,
        MBOX_K3_SEC_PROXY_MSG_DRXN_WRITE);
    if (MBOX_K3_SEC_PROXY_STATUS_CODE_NO_ERROR != write_status) {
        ERROR("secure_proxy_thread_%d thread verif failed", thread_id);
        return write_status;
    }

    /* msg len check */
    if (len > sec_proxy_desc->thread_inst.max_msg_size) {
        ERROR("secure_proxy_thread_%d msg len exceeds limit", thread_id);
        return MBOX_K3_SEC_PROXY_STATUS_CODE_INVALID_MSG_LEN;
    }

    /* perform write transaction */
    paddr_t data_reg = sec_proxy_desc->thread_inst.data_base +
        MBOX_K3_SEC_PROXY_THREAD_OFFSET(thread_id) + MBOX_K3_SEC_PROXY_DATA_START_OFFSET;

    /* write whole words first */
    uint32_t word_iterator;
    size_t num_words = len / sizeof(uint32_t);
    for (word_iterator = 0; word_iterator < num_words; word_iterator++) {
        write_reg(data_reg, word_iterator * sizeof(uint32_t), ((uint32_t*)buffer)[word_iterator]);
    }

    /* write remaining bytes */
    uint32_t trail_bytes = len % sizeof(uint32_t);
    if (0 != trail_bytes) {
        uint32_t data_trail = 0;

        size_t trail_iterator = len - trail_bytes;
        for (uint32_t i = 0; i < trail_bytes; i++) {
            data_trail |= (uint32_t)((uint8_t*)buffer)[trail_iterator++] << (i * 8);
        }

        write_reg(data_reg, word_iterator++ * sizeof(uint32_t), data_trail);
    }

    /*
     * Pad the remaining registers with zeros up to the completion trigger offset.
     * The Secure Proxy hardware triggers the message transmission ONLY when
     * the last register at MBOX_K3_SEC_PROXY_DATA_END_OFFSET is written.
     */
    while ((MBOX_K3_SEC_PROXY_DATA_START_OFFSET + (word_iterator * sizeof(uint32_t))) <=
        MBOX_K3_SEC_PROXY_DATA_END_OFFSET) {
        write_reg(data_reg, word_iterator++ * sizeof(uint32_t), 0U);
    }

    INFO("secure_proxy_thread_%d data WRITE success", thread_id);

    return write_status;
}

int32_t mbox_k3_sec_proxy_clear(mbox_k3_sec_proxy_desc* sec_proxy_desc, uint8_t thread_id)
{
    int32_t clear_status =
        mbox_k3_sec_proxy_verify_thread(sec_proxy_desc, thread_id, MBOX_K3_SEC_PROXY_MSG_DRXN_READ);
    if (MBOX_K3_SEC_PROXY_STATUS_CODE_NO_ERROR != clear_status) {
        ERROR("secure_proxy_thread_%d thread verif failed", thread_id);
        return clear_status;
    }

    paddr_t thread_rt_base =
        sec_proxy_desc->thread_inst.rt_base + MBOX_K3_SEC_PROXY_THREAD_OFFSET(thread_id);
    paddr_t data_reg =
        sec_proxy_desc->thread_inst.data_base + MBOX_K3_SEC_PROXY_THREAD_OFFSET(thread_id);

    uint32_t try_count = 10;
    while (0 !=
        (read_reg(thread_rt_base, MBOX_K3_SEC_PROXY_RT_THREAD_STATUS_OFFSET) &
            MBOX_K3_SEC_PROXY_RT_STATUS_CUR_CNT_MASK)) {
        if (0 == (try_count--)) {
            ERROR("secure_proxy_thread_%d mailbox clear failed", thread_id);
            return MBOX_K3_SEC_PROXY_STATUS_CODE_THREAD_CLEAR_FAILED;
        }

        WARNING("secure_proxy_thread_%d mailbox clear in progress", thread_id);
        read_reg(data_reg, MBOX_K3_SEC_PROXY_DATA_END_OFFSET);
    }

    return MBOX_K3_SEC_PROXY_STATUS_CODE_NO_ERROR;
}

int32_t mbox_k3_sec_proxy_probe(mbox_k3_sec_proxy_desc* sec_proxy_desc, uint8_t thread_id)
{
    paddr_t thread_scfg_base =
        sec_proxy_desc->thread_inst.scfg_base + MBOX_K3_SEC_PROXY_THREAD_OFFSET(thread_id);
    uint32_t config = read_reg(thread_scfg_base, MBOX_K3_SEC_PROXY_SCFG_THREAD_CTRL_OFFSET);

    uint8_t hw_host = (config >> 8) & 0xFF;
    uint8_t expected_host = sec_proxy_desc->sec_proxy_thread_desc[thread_id].host_id;

    /* [step-1] verify thread access/host ownership */
    if (hw_host != expected_host) {
        ERROR("sec_proxy_thread_%d probe failed (hw_host=%d, expected=%d)", thread_id, hw_host,
            expected_host);
        return MBOX_K3_SEC_PROXY_STATUS_CODE_THREAD_CORRUPTED;
    }

    /* [step-2] verify if thread is clean */
    int32_t probe_status = mbox_k3_sec_proxy_verify_thread(sec_proxy_desc, thread_id,
        sec_proxy_desc->sec_proxy_thread_desc[thread_id].msg_drxn);

    if (MBOX_K3_SEC_PROXY_MSG_DRXN_READ ==
            sec_proxy_desc->sec_proxy_thread_desc[thread_id].msg_drxn &&
        MBOX_K3_SEC_PROXY_STATUS_CODE_NO_ERROR == probe_status) {
        ERROR("secure_proxy_thread_%d probe failed (message queue not clean)", thread_id);
        return MBOX_K3_SEC_PROXY_STATUS_CODE_DIRTY_HANDOFF;
    }

    if (MBOX_K3_SEC_PROXY_MSG_DRXN_READ ==
            sec_proxy_desc->sec_proxy_thread_desc[thread_id].msg_drxn &&
        MBOX_K3_SEC_PROXY_STATUS_CODE_NO_DATA == probe_status) {
        probe_status = MBOX_K3_SEC_PROXY_STATUS_CODE_NO_ERROR;
    }

    if (MBOX_K3_SEC_PROXY_STATUS_CODE_NO_ERROR != probe_status) {
        INFO("sec_proxy_thread_%d probe failed (error_id=%d)", thread_id, probe_status);
        return probe_status;
    }

    INFO("sec_proxy_thread_%d probe success", thread_id);
    return probe_status;
}

mbox_k3_sec_proxy_thread_desc*
mbox_k3_sec_proxy_get_thread_by_host_func(mbox_k3_sec_proxy_desc* sec_proxy_desc, uint8_t host_id,
    MBOX_K3_SEC_PROXY_HOST_FUNCTION host_function)
{
    for (size_t thread_iterator = 0; thread_iterator < sec_proxy_desc->num_threads;
        thread_iterator++) {
        if (sec_proxy_desc->sec_proxy_thread_desc[thread_iterator].host_id == host_id &&
            sec_proxy_desc->sec_proxy_thread_desc[thread_iterator].host_function == host_function) {
            return &sec_proxy_desc->sec_proxy_thread_desc[thread_iterator];
        }
    }
    return NULL;
}

void mbox_k3_sec_proxy_init(mbox_k3_sec_proxy_desc* sec_proxy_desc)
{
    if (cpu_is_master()) {
        sec_proxy_desc->thread_inst.rt_base = (vaddr_t)mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL,
            INVALID_VA, sec_proxy_desc->thread_inst.rt_base,
            NUM_PAGES(sec_proxy_desc->thread_inst.rt_size));

        sec_proxy_desc->thread_inst.scfg_base = (vaddr_t)mem_alloc_map_dev(&cpu()->as,
            SEC_HYP_GLOBAL, INVALID_VA, sec_proxy_desc->thread_inst.scfg_base,
            NUM_PAGES(sec_proxy_desc->thread_inst.scfg_size));

        sec_proxy_desc->thread_inst.data_base = (vaddr_t)mem_alloc_map_dev(&cpu()->as,
            SEC_HYP_GLOBAL, INVALID_VA, sec_proxy_desc->thread_inst.data_base,
            NUM_PAGES(sec_proxy_desc->thread_inst.data_size));
    }
}
