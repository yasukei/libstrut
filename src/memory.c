#include "facade.h"
#include "memory.h"
#include "MemoryFactory.h"

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
void OSMemory_destroy(
	Memory* super
)
{
	UNUSED(super);
}

// ------------------------------------------------------------------
static const OSMemory gOSMemory =
{
	.super =
	{
		.malloc		= OSMemory_malloc,
		.free		= OSMemory_free,
		.destroy	= OSMemory_destroy,
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
// MemoryFactory
// ------------------------------------------------------------------
Memory* MemoryFactory_createOSMemory(
	void
)
{
	return (Memory*)OSMemory_create();
}

// ------------------------------------------------------------------
void MemoryFactory_destroyMemory(
	Memory* memory
)
{
	return Memory_destroy(memory);
}

