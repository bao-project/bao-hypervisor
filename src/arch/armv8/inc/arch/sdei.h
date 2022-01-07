#ifndef SDEI_H
#define SDEI_H

#include <bao.h>
#include <arch/smc.h>

#define SDEI_VERSION        (0xC4000020)
#define SDEI_EVENT_REGISTER (0xC4000021)
#define SDEI_EVENT_ENABLE   (0xC4000022)
#define SDEI_EVENT_COMPLETE (0xC4000025)
#define SDEI_PE_UNMASK      (0xC400002C)
#define SDEI_EVENT_SIGNAL   (0xC400002F)

#define SDEI_SUCCESS            (0)
#define SDEI_NOT_SUPPORTED      (-1)
#define SDEI_INVALID_PARAMETERS (-2)
#define SDEI_DENIED             (-3)
#define SDEI_PENDING            (-5)
#define SDEI_OUT_OF_RESOURCE    (-10)

#define SDEI_F_EP_ABS       (0)
#define SDEI_F_EP_VBAR_REL  (1ULL << 1)
#define SDEI_F_RM_ANY       (0)
#define SDEI_F_RM_PE        (1ULL << 0)

#define SDEI_EV_HANDLED (0)
#define SDEI_EV_FAILED  (1)


static inline int64_t sdei_version() {
    return (int64_t) smc_call(SDEI_VERSION, 0, 0, 0, 0, 0, NULL);
}

static inline int64_t sdei_event_register(int32_t evt, uint64_t ep_addr, uint64_t ep_arg,
                    uint64_t flags, uint64_t aff)
{
    return (int64_t)
        smc_call(SDEI_EVENT_REGISTER, evt, ep_addr, ep_arg, flags, aff, NULL);
}

static inline int64_t sdei_event_enable(size_t evt)
{
    return (int64_t) smc_call(SDEI_EVENT_ENABLE, evt, 0, 0, 0, 0, NULL);
}

static inline int64_t sdei_event_complete(uint32_t status_code)
{
    return (int64_t) smc_call(SDEI_EVENT_COMPLETE, status_code, 0, 0, 0, 0, NULL);
}

static inline int64_t sdei_pe_unmask()
{
    return (int64_t) smc_call(SDEI_PE_UNMASK, 0, 0, 0, 0, 0, NULL);
}

static inline int64_t sdei_event_signal(int32_t evt, uint64_t target_pe)
{
    return (int64_t) smc_call(SDEI_EVENT_SIGNAL, evt, target_pe, 0, 0, 0, NULL);
}


#endif /* SDEI_H */
