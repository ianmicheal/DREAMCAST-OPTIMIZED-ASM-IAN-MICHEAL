/*
 * Optimized MemCpy32 movca.l based function
 * By Ian Micheal - 3.31.2025
 * Update fastest -5.19.2025
 * This function efficiently copies memory using SH4-specific 
 * optimizations for the Dreamcast:
 * 
 * 1. Uses prefetch instruction for the source data
 * 2. Employs movca.l instruction for optimized cache handling
 * 3. Processes memory in aligned 32-byte blocks
 * 4. Uses a 1-cycle pitch optimization pattern
 * 5. Features an unrolled inner loop to reduce branch penalties
 * 6. IMPORTANT: Uses prefetch only ONCE per cache line!
 * 7. By loading all values upfront, it created independent operations that the processor can potentially execute in parallel.
 * 8. Loading all values at once helps the prefetch mechanism work more efficiently by creating a predictable access pattern
 * 9. By eliminating the inner loop and replacing it with direct assignments, we avoid branch prediction overhead and potential pipeline stalls when the processor has to evaluate loop conditions.
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
        
        // Load all values into registers first
        uint32_t v0 = src[0];
        uint32_t v1 = src[1];
        uint32_t v2 = src[2];
        uint32_t v3 = src[3];
        uint32_t v4 = src[4];
        uint32_t v5 = src[5];
        uint32_t v6 = src[6];
        uint32_t v7 = src[7];
        
        // Use movca.l for the first write with the correct "z" constraint
        __asm__ __volatile__ (
            "movca.l %[data], @%[out]\n"
            : // no outputs
            : [data] "z" (v0), [out] "r" (dst)
            : "memory"
        );
        
        // Store remaining values - using pointer indexing as in your original
        *(dst+1) = v1;
        *(dst+2) = v2;
        *(dst+3) = v3;
        *(dst+4) = v4;
        *(dst+5) = v5;
        *(dst+6) = v6;
        *(dst+7) = v7;
        
        // Move to next block
        src += 8;
        dst += 8;
    }
}
