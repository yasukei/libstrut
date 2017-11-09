#ifndef _MEMORY_H_
#define _MEMORY_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "facade.h"

// ------------------------------------------------------------------
// Memory
// ------------------------------------------------------------------
typedef struct Memory Memory;

// ------------------------------------------------------------------
struct Memory
{
	void*	(*malloc)(Memory* self, size_t size);
	void	(*free)(Memory* self, void* ptr);
};

// ------------------------------------------------------------------
static inline void* Memory_malloc(
	Memory* self,
	size_t size
	)
{
	return self->malloc(self, size);
}

// ------------------------------------------------------------------
static inline void Memory_free(
	Memory* self,
	void* ptr
	)
{
	self->free(self, ptr);
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _MEMORY_H_
