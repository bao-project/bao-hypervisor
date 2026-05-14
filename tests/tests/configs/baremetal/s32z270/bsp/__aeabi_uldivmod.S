/* __aeabi_uldivmod.S
 *
 * Unsigned 64-bit divide+mod helper for ARM EABI:
 *   (uint64_t)q = n / d
 *   (uint64_t)r = n % d
 *
 * Input:
 *   r0:r1 = n (low:high)
 *   r2:r3 = d (low:high)
 * Output:
 *   r0:r1 = q
 *   r2:r3 = r
 *
 * Clobbers:
 *   r4-r9, flags
 *
 * Notes:
 * - Division by zero is architecturally undefined. Here we return:
 *     q = 0, r = n
 *   (You can replace that path with a BKPT/UDFF if you prefer trapping.)
 */

    .syntax unified
    .text
    .global __aeabi_uldivmod
    .type   __aeabi_uldivmod, %function

__aeabi_uldivmod:
    /* Preserve callee-saved regs we use */
    push    {r4-r9, lr}

    /* Check d == 0 */
    orrs    r4, r2, r3
    beq     .L_div_by_zero

    /* If n < d: q=0, r=n */
    /* Compare high first, then low */
    cmp     r1, r3
    blo     .L_n_lt_d
    bhi     .L_do_div
    cmp     r0, r2
    blo     .L_n_lt_d

.L_do_div:
    /* q = 0, r = 0 */
    movs    r4, #0          /* q_lo */
    movs    r5, #0          /* q_hi */
    movs    r6, #0          /* r_lo */
    movs    r7, #0          /* r_hi */

    movs    r8, #64         /* loop counter */

    /* Long division, 64 iterations:
     * Each step:
     *   bit = msb(n)
     *   n <<= 1
     *   r = (r<<1) | bit
     *   q <<= 1
     *   if (r >= d) { r -= d; q |= 1; }
     */
.L_loop:
    /* bit = (n_hi >> 31) */
    lsrs    r9, r1, #31     /* r9 = 0/1 */

    /* n <<= 1 (r0:r1) */
    adds    r0, r0, r0
    adcs    r1, r1, r1

    /* r <<= 1 (r6:r7) */
    adds    r6, r6, r6
    adcs    r7, r7, r7

    /* r |= bit (into r_lo LSB) */
    orrs    r6, r6, r9

    /* q <<= 1 (r4:r5) */
    adds    r4, r4, r4
    adcs    r5, r5, r5

    /* if (r >= d) */
    cmp     r7, r3
    blo     .L_skip_sub
    bhi     .L_take_sub
    cmp     r6, r2
    blo     .L_skip_sub

.L_take_sub:
    /* r -= d */
    subs    r6, r6, r2
    sbcs    r7, r7, r3

    /* q |= 1 */
    orr     r4, r4, #1

.L_skip_sub:
    subs    r8, r8, #1
    bne     .L_loop

    /* Return: r0:r1 = q, r2:r3 = r */
    mov     r0, r4
    mov     r1, r5
    mov     r2, r6
    mov     r3, r7

    pop     {r4-r9, pc}

.L_n_lt_d:
    /* q = 0, r = n */
    movs    r2, r0
    movs    r3, r1
    movs    r0, #0
    movs    r1, #0
    pop     {r4-r9, pc}

.L_div_by_zero:
    /* Undefined by ABI; choose a deterministic behavior:
     * q = 0, r = n
     */
    b       .L_div_by_zero

    .size __aeabi_uldivmod, .-__aeabi_uldivmod
