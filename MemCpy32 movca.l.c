/*
 * Optimized MemCpy32 movca.l based function
 * By Ian Micheal - 3.31.2025
 * 
 * This function efficiently copies memory using SH4-specific 
 * optimizations for the Dreamcast:
 * 
 * 1. Uses prefetch instruction for the source data
 * 2. Employs movca.l instruction for optimized cache handling
 * 3. Processes memory in aligned 32-byte blocks
 * 4. Uses a 1-cycle pitch optimization pattern
 * 5. Features an unrolled inner loop to reduce branch penalties
 * 6. IMPORTANT: Uses prefetch only ONCE per cache line!
 */
void MemCpy32(uint32_t *dst, uint32_t *src, size_t size)
{
    // Create a second source pointer offset by 8 items
    uint32_t *src2;
    src2 = src+8;
    
    // Process in 32-byte chunks (8 longs per chunk)
    for(size>>=5; size; size--) {
        // Prefetch the next source data (only ONCE per cache line)
        __asm__ __volatile__ (
            "pref @%[addr]\n"
            : // no outputs
            : [addr] "r" (src2)
            : "memory"
        );
        
        // Update the prefetch pointer
        src2 += 8;
        
        // Use movca.l for the first write
        __asm__ __volatile__ (
            "movca.l %[data], @%[out]\n"
            : // no outputs
            : [data] "z" (*src), [out] "r" (dst)
            : "memory"
        );
        
        // Move to next positions
        dst++;
        src++;
        
        // Unrolled inner loop - copy 7 more longs (28 bytes)
        for(int i=7; i>0; i--) *dst++ = *src++;
    }
}
