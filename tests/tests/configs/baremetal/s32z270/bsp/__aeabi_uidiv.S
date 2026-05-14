/* __aeabi_uidiv.S
 *
 * Unsigned 32-bit divide helper for ARM EABI:
 *   (uint32_t)q = n / d
 *
 * Input:
 *   r0 = n (numerator)
 *   r1 = d (denominator)
 * Output:
 *   r0 = q (quotient)
 *
 * Uses __aeabi_uldivmod by promoting to 64-bit division
 */

    .syntax unified
    .text
    .global __aeabi_uidiv
    .type   __aeabi_uidiv, %function

__aeabi_uidiv:
    /* Save lr */
    push    {lr}

    /* Promote r0:r1 to 64-bit:
     * r0:r1 = n (low:high) - already in position
     * r2:r3 = d (low:high)
     */
    mov     r2, r1          /* r2 = d */
    mov     r3, #0          /* r3 = 0 (high word of d) */
    mov     r1, #0          /* r1 = 0 (high word of n) */

    /* Call __aeabi_uldivmod(n_lo:n_hi, d_lo:d_hi) -> q_lo:q_hi, r_lo:r_hi */
    bl      __aeabi_uldivmod

    /* Result quotient is in r0:r1, we only need r0 (low 32 bits) */
    /* r0 already has the quotient, just return */

    pop     {pc}

    .size __aeabi_uidiv, .-__aeabi_uidiv
