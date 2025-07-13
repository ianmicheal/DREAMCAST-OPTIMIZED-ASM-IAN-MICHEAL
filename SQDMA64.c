//bit64_sq_cpy() - Your optimized 64-byte block copy routine with:

//Direct SQ register manipulation
//Efficient 64-byte chunked transfers
//Optimal prefetch and cache invalidation (ocbi)
//Hardware-level optimizations


//sq_cpy_pvr_fast() - My high-level wrapper that:

//Sets PVR DMA mode (64-bit or 32-bit)
//Converts pointers to DMA-optimized area
//Calls your optimized copy routine

//following timings for copying a frame buffer from main RAM to video RAM for a 640x480 16-bit frame buffer:
//memcpy: 20.80 ms
//KOS sq_cpy: 8.24 ms
//sq_cpy_pvr_fast: 3.89 ms
//DMA (includes optimized cache flush, waits for DMA to complete): 1.98 ms
//DMA (includes optimized cache flush, DMA works in background): 0.08 m

// Ian Micheal optimized SQ function - much faster than original
void bit64_sq_cpy(void *dest, void *src, int n)
{
  uint32_t *sq;
  uint32_t *d, *s;
  // Cast the destination pointer to uint32* and set it to the base address
  // of a specific memory region (0xe0000000) with some bit manipulation.
  d = (uint32_t *)(0xe0000000 | (((uint32_t)dest) & 0x03ffffe0));
 // Cast the source pointer to uint32*.
  s = (uint32_t *)(src);
  // Set specific memory-mapped registers to configure memory access.
  *((volatile unsigned int*)0xFF000038) = ((((uint32_t)dest) >> 26) << 2) & 0x1c;
  *((volatile unsigned int*)0xFF00003C) = ((((uint32_t)dest) >> 26) << 2) & 0x1c;
  // Right shift 'n' by 6 (equivalent to dividing by 64) to determine the number of 64-byte blocks to copy.
  n >>= 6;
  while (n--) 
  {
    // Copy 64 bytes (8 uint32 values) from source to destination.
    // sq0
    sq = d;
    *sq++ = *s++; *sq++ = *s++;
    *sq++ = *s++; *sq++ = *s++;
    *sq++ = *s++; *sq++ = *s++;
    *sq++ = *s++; *sq++ = *s++;
    // Issue a prefetch operation for the destination memory region.
    asm("pref @%0" : : "r" (d));
    asm("ocbi @r4" : : "r" (dest));  // Issue a cache operation to write the destination memory region (ocbi = "orderly cache block invalidate"). 
    // Move the destination pointer by 8 uint32 values (64 bytes).
    d += 8;
    // sq1
    sq = d;
    *sq++ = *s++; *sq++ = *s++;
    *sq++ = *s++; *sq++ = *s++;
    *sq++ = *s++; *sq++ = *s++;
    *sq++ = *s++; *sq++ = *s++;
    // Issue a prefetch operation for the next destination memory region.
    asm("pref @%0" : : "r" (d));
    // Issue a cache operation to write the next destination memory region.
    asm("ocbi @r4" : : "r" (dest));  
    // Move the destination pointer by 8 uint32 values (64 bytes) for the next iteration.
    d += 8;
  }
  // Clear specific memory-mapped registers.
  *((uint32_t *)(0xe0000000)) = 0;
  *((uint32_t *)(0xe0000020)) = 0;
}

#define MEM_MODE_VRAM64	0
#define MEM_MODE_VRAM32	1

void sq_cpy_pvr_fast(void *dst, void *src, size_t len, unsigned mem_mode) {
   //Set PVR DMA register
   *(volatile int *)0xA05F6884 = mem_mode;
   
   //Convert read/write area pointer to DMA write only area pointer
   uint32_t dmaareaptr = ((uintptr_t)dst & 0xffffff) | 0x11000000;
   
   bit64_sq_cpy((void *)dmaareaptr, src, len);
}
