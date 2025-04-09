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
       __asm__ __volatile__(
           "movca.l %[data], @%[out]\n"
           : // no outputs
           : [data] "z" (lv), [out] "r" (pdst)
           : "memory"
       );
       
       // Unrolled inner loop with pre-decrements
       for(int i=7; i>0; i--) *--dst = lv;
   }
}

//void *dst_void to accept any pointer type
void MemSet32_any(void *dst_void, long value, size_t size)
{
   // Cast to unsigned char for byte-level operations
   unsigned char *dst_char = (unsigned char*)dst_void;
   
   // Prepare the value by duplicating it across all bytes
   long lv = (unsigned char)value;
   lv |= lv<<8;
   lv |= lv<<16;
   
   // Make sure we're operating on correct alignment
   long *dst = (long*)(((unsigned long)dst_char + 3) & ~3);
   
   // Calculate size in longs (32-bit units)
   size_t size_in_longs = size >> 2;
   
   // Pre-increment destination pointer by size_in_longs
   dst += size_in_longs;
   
   // Process in 32-byte chunks (8 longs per chunk)
   for(size_t chunks = size_in_longs >> 3; chunks; chunks--) {
       // Use movca.l for the first write with pre-decrement
       void *pdst = --dst;
       __asm__ __volatile__(
           "movca.l %[data], @%[out]\n"
           : // no outputs
           : [data] "z" (lv), [out] "r" (pdst)
           : "memory"
       );
       
       // Unrolled inner loop with pre-decrements
       for(int i=7; i>0; i--) *--dst = lv;
   }
   
   // Handle remaining longs (less than 8)
   for(size_t remain = size_in_longs & 7; remain; remain--) {
       *--dst = lv;
   }
}
