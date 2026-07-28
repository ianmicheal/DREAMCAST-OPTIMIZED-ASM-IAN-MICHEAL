#ifndef DNPC_MEMCPY32_MOVCA_H
#define DNPC_MEMCPY32_MOVCA_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void MemCpy32_movca_safe(void *dst, const void *src, size_t size);
void MemCpy32_movca_pipe(void *dst, const void *src, size_t size);

#ifdef __cplusplus
}
#endif

#endif
