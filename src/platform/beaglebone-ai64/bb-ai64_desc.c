/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

struct platform platform = {
    .cpu_num = 2,
    .region_num = 2,
    .regions =
        (struct mem_region[]){
            {
                .base = 0x80000000,
                .size = 0x80000000,
            },
            {
                .base = 0x880000000,
                .size = 0x80000000,
            },
        },
    .console =
        {
            .base = 0x02800000,
        },
    .arch =
        {
            .gic =
                {
                    .gicd_addr = 0x01800000,
                    .gicr_addr = 0x01900000,
                    .gicc_addr = 0x6f000000,
                    .gich_addr = 0x6f010000,
                    .gicv_addr = 0x6f020000,
                    .maintenance_id = 25,
                },
        },
};

#ifndef GENERATING_DEFS

static mbox_k3_sec_proxy_thread_desc sec_proxy_thread_desc[] = {
    MBOX_K3_SEC_PROXY_THREAD_DESC_ENTRY(J721E_HOST_ID_MAIN_A72_CONTEXT_0_SECURE, 0, 2, 30, 10, 20),
    MBOX_K3_SEC_PROXY_THREAD_DESC_ENTRY(J721E_HOST_ID_MAIN_A72_CONTEXT_1_SECURE, 5, 2, 30, 10, 20),
    MBOX_K3_SEC_PROXY_THREAD_DESC_ENTRY(J721E_HOST_ID_MAIN_A72_CONTEXT_2_NON_SECURE, 10, 2, 22, 2,
        20),
    MBOX_K3_SEC_PROXY_THREAD_DESC_ENTRY(J721E_HOST_ID_MAIN_A72_CONTEXT_3_NON_SECURE, 15, 2, 7, 2, 5),
    MBOX_K3_SEC_PROXY_THREAD_DESC_ENTRY(J721E_HOST_ID_MAIN_A72_CONTEXT_4_NON_SECURE, 20, 2, 7, 2, 5),
    MBOX_K3_SEC_PROXY_THREAD_DESC_ENTRY(J721E_HOST_ID_MAIN_A72_CONTEXT_5_NON_SECURE, 55, 2, 7, 2, 5),
};

static mbox_k3_sec_proxy_desc k3_sec_proxy = {
    .thread_inst =
        {
            .id = 0U,
            .rt_base = 0x0032400000U,
            .rt_size = 0x100000U,
            .scfg_base = 0x0032800000U,
            .scfg_size = 0x100000U,
            .data_base = 0x0032C00000,
            .data_size = 0x100000,
            .max_msg_size = TISCI_MSG_MAX_SIZE,
        },
    .read_timeout_us = TISCI_MSG_TXN_TIMEOUT,
    .sec_proxy_thread_desc = sec_proxy_thread_desc,
    .num_threads = sizeof(sec_proxy_thread_desc) / sizeof(sec_proxy_thread_desc[0]),
};

static int32_t platform_tisci_send(uint8_t chan_id, void* buffer, size_t len)
{
    return mbox_k3_sec_proxy_write(&k3_sec_proxy, chan_id, buffer, len);
}

static int32_t platform_tisci_recv(uint8_t chan_id, void* buffer, size_t len)
{
    return mbox_k3_sec_proxy_read(&k3_sec_proxy, chan_id, buffer, len);
}

static tisci_ctx tisci_context = {
    .ops =
        {
            .send = platform_tisci_send,
            .recv = platform_tisci_recv,
        },
    .seq_id_lock = {0, 0},
    .seq_id = 0U,
};

void platform_default_init(void)
{
    if (cpu_is_master()) {
        cpu_sync_init(&cpu_glb_sync, platform.cpu_num);
    }

    mbox_k3_sec_proxy_init(&k3_sec_proxy);
    cpu_sync_barrier(&cpu_glb_sync);

    uint8_t cur_host_id = cpu_is_master() ? J721E_HOST_ID_MAIN_A72_CONTEXT_2_NON_SECURE :
                                            J721E_HOST_ID_MAIN_A72_CONTEXT_3_NON_SECURE;

    mbox_k3_sec_proxy_thread_desc* host_threads =
        mbox_k3_sec_proxy_get_thread_by_host_func(&k3_sec_proxy, cur_host_id, 0U);
    if (NULL == host_threads) {
        ERROR("platform init failed, no secure proxy threads found");
        return;
    }

    /* probe all secure proxy threads owned by this host */
    for (uint8_t func_iterator = 0U; func_iterator < MBOX_K3_SEC_PROXY_NUM_HOST_FUNCTIONS;
        func_iterator++) {
        int32_t probe_status =
            mbox_k3_sec_proxy_probe(&k3_sec_proxy, host_threads[func_iterator].sec_proxy_thread_id);
        if (MBOX_K3_SEC_PROXY_STATUS_CODE_NO_ERROR != probe_status) {
            ERROR("platform init failed, k3 secure_proxy_thread_%d probe status=%d",
                host_threads[func_iterator].sec_proxy_thread_id, probe_status);
            return;
        }
    }

    /* ping test to ensure that host<->sysfw pipeline is clean */
    tisci_msg_version_rsp ping_rsp = { 0 };
    int32_t ping_status = tisci_get_revision(&tisci_context, cur_host_id,
        host_threads[MBOX_K3_SEC_PROXY_HOST_FUNCTION_LOW_PRIORITY].sec_proxy_thread_id,
        host_threads[MBOX_K3_SEC_PROXY_HOST_FUNCTION_RESPONSE].sec_proxy_thread_id, &ping_rsp);
    if (TISCI_STATUS_CODE_NO_ERROR != ping_status) {
        ERROR("platform init failed, ping to sysfw failed, ping_status=%d", ping_status);
    }
}

#endif /* ifndef GENERATING_DEFS */
