
#include <arch/vfp.h>
#include <string.h>

void vfp_reset(struct vfp* vfp)
{
    memset(vfp->s, 0, sizeof(vfp->s));
    vfp->fpscr = 0;
}

void vfp_save_state(struct vfp* vfp)
{
    __asm__ volatile("vstm %0, {s0-s31}\n\t" : : "r"(vfp->s));

    vfp->fpscr = vfp_fpscr_read();
}

void vfp_restore_state(struct vfp* vfp)
{
    __asm__ volatile("vldm %0, {s0-s31}\n\t" : : "r"(vfp->s));

    vfp_fpscr_write(vfp->fpscr);
}
