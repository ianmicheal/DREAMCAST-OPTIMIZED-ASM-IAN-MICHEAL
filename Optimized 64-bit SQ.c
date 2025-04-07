/**
 * @file      bit64_sq_cpy.c
 * @author    Ian Micheal
 * @brief     Optimized 64-bit Store Queue function for hardware-accelerated memory operations
 * @date      2025-04-07
 *
 * @details   This function performs an optimized memory copy operation using
 *            the SQ (Store Queue) hardware acceleration features. It copies data
 *            in 64-byte chunks with prefetching and cache operations to maximize
 *            transfer efficiency on SH-4 based hardware.
 *            
 * @param     dest    Destination memory address
 * @param     src     Source memory address  
 * @param     n       Number of bytes to copy (must be multiple of 64)
 * 
 * @note      This function manipulates memory-mapped registers directly and
 *            should only be used in systems with the appropriate hardware
 *            architecture. The memory addresses are manipulated to align with
 *            the SQ memory region (0xE0000000).
 *
 * @warning   The input size 'n' must be a multiple of 64 bytes as the function
 *            operates on 64-byte blocks.
 */
void bit64_sq_cpy(void *dest, void *src, int n)
{
  uint32 *sq;
  uint32 *d, *s;
  // Cast the destination pointer to uint32* and set it to the base address
  // of a specific memory region (0xe0000000) with some bit manipulation.
  d = (uint32 *)(0xe0000000 | (((uint32)dest) & 0x03ffffe0));
 // Cast the source pointer to uint32*.
  s = (uint32 *)(src);
  // Set specific memory-mapped registers to configure memory access.
  *((volatile unsigned int*)0xFF000038) = ((((uint32)dest) >> 26) << 2) & 0x1c;
  *((volatile unsigned int*)0xFF00003C) = ((((uint32)dest) >> 26) << 2) & 0x1c;
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
    __asm__("pref @%0" : : "r" (d));
    __asm__("ocbi @r4" : : "r" (dest));  // Issue a cache operation to write the destination memory region (ocbi = "orderly cache block invalidate"). 
    // Move the destination pointer by 8 uint32 values (64 bytes).
    d += 8;
    // sq1
    sq = d;
    *sq++ = *s++; *sq++ = *s++;
    *sq++ = *s++; *sq++ = *s++;
    *sq++ = *s++; *sq++ = *s++;
    *sq++ = *s++; *sq++ = *s++;
    // Issue a prefetch operation for the next destination memory region.
    __asm__("pref @%0" : : "r" (d));
    // Issue a cache operation to write the next destination memory region.
    __asm__("ocbi @r4" : : "r" (dest));  
    // Move the destination pointer by 8 uint32 values (64 bytes) for the next iteration.
    d += 8;
  }
  // Clear specific memory-mapped registers.
  *((uint32 *)(0xe0000000)) = 0;
  *((uint32 *)(0xe0000020)) = 0;
}
