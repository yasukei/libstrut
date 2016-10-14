#include <stdlib.h>

#include "facade.h"

// ------------------------------------------------------------------
// stdlib.h
// ------------------------------------------------------------------
void* Malloc(size_t size)
{
	return malloc(size);
}

// ------------------------------------------------------------------
void Free(void* ptr)
{
	free(ptr);
}

// ------------------------------------------------------------------
void* Calloc(size_t nmemb, size_t size)
{
	return calloc(nmemb, size);
}

// ------------------------------------------------------------------
void* Realloc(void* ptr, size_t size)
{
	return realloc(ptr, size);
}

