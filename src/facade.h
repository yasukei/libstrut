#ifndef _FACADE_H_
#define _FACADE_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
// ------------------------------------------------------------------


#include <stddef.h>
#include <stdbool.h>

#define UNUSED(variable)	(void)(variable)

// ------------------------------------------------------------------
// stdlib.h
// ------------------------------------------------------------------
void* Malloc(size_t size);
void Free(void* ptr);
void* Calloc(size_t nmemb, size_t size);
void* Realloc(void* ptr, size_t size);

// ------------------------------------------------------------------
// string.h
// ------------------------------------------------------------------
void* Memcpy(void* dest, const void* src, size_t n);


// ------------------------------------------------------------------
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _FACADE_H_
