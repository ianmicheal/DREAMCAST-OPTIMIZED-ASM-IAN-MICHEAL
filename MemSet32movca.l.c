/*
* Optimized MemSet32 function
* By Ian Micheal - 3.31.2025
* 
* This function efficiently fills memory with a repeated value using
* SH4-specific optimizations for the Dreamcast:
* 
* 1. Uses pre-decrement addressing mode which is faster on SH4
* 2. Employs movca.l instruction for optimized cache handling
* 3. Processes memory in aligned 32-byte blocks
* 4. Replicates the value across all bytes using bit operations
* 5. Features an unrolled inner loop to reduce branch penalties
*/
void MemSet32(long *dst, long value, size_t size)
{
   // Prepare the value by duplicating it across all bytes
   long lv = (unsigned char)value;
   lv |= lv<<8;
   lv |= lv<<16;
   
   // Pre-increment destination pointer by (size>>2)
   dst += (size>>2);
   
   // Process in 32-byte chunks (8 longs per chunk)
   for(size>>=5; size; size--) {
       // Use movca.l for the first write with pre-decrement
       void *pdst = --dst;
       __asm__ __volatile __(
           "movca.l %[data], @%[out]\n"
           : // no outputs
           : [data] "z" (lv), [out] "r" (pdst)
           : "memory"
       );
       
       // Unrolled inner loop with pre-decrements
       for(int i=7; i>0; i--) *--dst = lv;
   }
}
