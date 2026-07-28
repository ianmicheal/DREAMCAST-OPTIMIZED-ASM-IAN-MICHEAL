/*
 * Dreamcast SH-4 MOVCA.L 32-byte copy — pipeline-scheduled candidate.
 *
 * ABI:
 *   r4 = dst
 *   r5 = src
 *   r6 = size in bytes
 *
 * Requirements:
 *   - dst is 32-byte aligned
 *   - src is at least 4-byte aligned
 *   - size is a multiple of 32
 *   - source and destination do not overlap
 *   - destination is cacheable write-back system RAM
 *
 * Scheduling:
 *   - two-register ping-pong keeps every load two issue cycles ahead
 *     of its dependent store
 *   - r8-r11 are not touched, so no callee-save traffic
 *   - DT is placed beside an independent LS operation
 *   - the delayed branch slot prefetches the following source line
 *
 * This is the candidate to A/B against _MemCpy32_movca_safe on hardware.
 */

    .text
    .align 2
    .global _MemCpy32_movca_pipe
    .type _MemCpy32_movca_pipe,@function

_MemCpy32_movca_pipe:
    shlr2  r6
    shlr2  r6
    shlr   r6
    tst    r6,r6
    bt     .Lpipe_done

    mov    r5,r7
    add    #32,r7
    pref   @r7

    .align 2
.Lpipe_loop:
    mov.l  @r5+,r0
    add    #32,r7
    mov.l  @r5+,r1
    movca.l r0,@r4
    mov.l  r1,@(4,r4)

    mov.l  @r5+,r0
    mov.l  @r5+,r1
    mov.l  r0,@(8,r4)
    mov.l  r1,@(12,r4)

    mov.l  @r5+,r0
    mov.l  @r5+,r1
    mov.l  r0,@(16,r4)
    mov.l  r1,@(20,r4)

    mov.l  @r5+,r0
    mov.l  @r5+,r1
    mov.l  r0,@(24,r4)
    dt     r6
    mov.l  r1,@(28,r4)

    /*
     * MOV.L reads the old r4 while ADD publishes the next-line base.
     * The simulator candidate expects this LS/EX pair to issue without
     * an integer anti-flow stall.
     */
    add    #32,r4
    bf/s   .Lpipe_loop
    pref   @r7

.Lpipe_done:
    rts
    nop

    .size _MemCpy32_movca_pipe,.-_MemCpy32_movca_pipe
