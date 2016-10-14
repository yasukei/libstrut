#ifndef _LIST_H_
#define _LIST_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>
#include <stdbool.h>

// ------------------------------------------------------------------
// stdlib.h
// ------------------------------------------------------------------
void* Malloc(size_t size);
void Free(void* ptr);
void* Calloc(size_t nmemb, size_t size);
void* Realloc(void* ptr, size_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _LIST_H_
