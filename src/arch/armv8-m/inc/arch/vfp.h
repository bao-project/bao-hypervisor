#ifndef ARCH_VFP_H
#define ARCH_VFP_H

#include <bao.h>

#define VFP_NUM_REGS (32)

#ifndef __ASSEMBLER__

#define SPVFPREG_GEN_ACCESSORS(name, reg)                             \
    static inline unsigned long vfp_##name##_read(void)               \
    {                                                                 \
        unsigned long _temp;                                          \
        __asm__ volatile("vmrs %0, " XSTR(reg) "\n\r" : "=r"(_temp)); \
        return _temp;                                                 \
    }                                                                 \
    static inline void vfp_##name##_write(unsigned long val)          \
    {                                                                 \
        __asm__ volatile("vmsr " XSTR(reg) ", %0\n\r" : : "r"(val));  \
    }

SPVFPREG_GEN_ACCESSORS(fpscr, fpscr)

#endif /* |__ASSEMBLER__ */

struct vfp {
    uint32_t s[VFP_NUM_REGS];
    uint32_t fpscr;
};

void vfp_reset(struct vfp* vfp);
void vfp_save_state(struct vfp* vfp);
void vfp_restore_state(struct vfp* vfp);

#endif /* ARCH_VFP_H */
