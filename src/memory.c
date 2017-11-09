#include "memory.h"

// ------------------------------------------------------------------
// OSMemory
// ------------------------------------------------------------------
typedef struct OSMemory OSMemory;
typedef struct OSMemory
{
	Memory super;
} OSMemory;

// ------------------------------------------------------------------
void* OSMemory_malloc(
	Memory* super,
	size_t size
)
{
	UNUSED(super);

	return Malloc(size);
}

// ------------------------------------------------------------------
void OSMemory_free(
	Memory* super,
	void* ptr
)
{
	UNUSED(super);

	return Free(ptr);
}

// ------------------------------------------------------------------
static const OSMemory gOSMemory =
{
	.super =
	{
		.malloc = OSMemory_malloc,
		.free = OSMemory_free,
	},
};

// ------------------------------------------------------------------
OSMemory* OSMemory_create(
	void
)
{
	return (OSMemory*)&gOSMemory;
}

// ------------------------------------------------------------------
void OSMemory_destroy(
	OSMemory* self
)
{
	UNUSED(self);
}

