#include "facade.h"

// ------------------------------------------------------------------
// MemoryPool
// ------------------------------------------------------------------
typedef struct MemoryPoolMethodTable MemoryPoolMethodTable;
typedef struct MemoryPool
{
	const MemoryPoolMethodTable* methodTable;
}MemoryPool;

// ------------------------------------------------------------------
struct MemoryPoolMethodTable
{
	void	(*destroy)(MemoryPool* self);
	void*	(*allocate)(MemoryPool* self);
	void	(*free)(MemoryPool* self, void* ptr);
};

// ------------------------------------------------------------------
void MemoryPool_setMethodTable(
	MemoryPool* self,
	const MemoryPoolMethodTable* methodTable
	)
{
	self->methodTable = methodTable;
}

// ------------------------------------------------------------------
void MemoryPool_destroy(
	MemoryPool* self
	)
{
	if(self->methodTable->destroy != NULL)
	{
		self->methodTable->destroy(self);
	}
}

// ------------------------------------------------------------------
void* MemoryPool_allocate(
	MemoryPool* self
	)
{
	if(self->methodTable->allocate != NULL)
	{
		return self->methodTable->allocate(self);
	}
	return NULL;
}

// ------------------------------------------------------------------
void MemoryPool_free(
	MemoryPool* self,
	void* ptr
	)
{
	if(self->methodTable->free != NULL)
	{
		self->methodTable->free(self, ptr);
	}
}

// ------------------------------------------------------------------
// FixedPool
// ------------------------------------------------------------------
typedef struct FixedPool
{
	MemoryPool interface;
	void* memory;
	bool* usedFlag;
	void* free;
}FixedPool;

// ------------------------------------------------------------------
static const MemoryPoolMethodTable gFixedPoolMethodTable;

// ------------------------------------------------------------------
static bool __FixedPool_initialize(
	FixedPool* self,
	size_t sizeofMemory,
	size_t numofMemory
	)
{
	MemoryPool_setMethodTable((MemoryPool*)self, &gFixedPoolMethodTable);

	self->memory = Malloc(sizeofMemory * numofMemory);
	if(self->memory == NULL)
	{
		return false;
	}

	return true;
}

// ------------------------------------------------------------------
FixedPool* FixedPool_create(
	size_t sizeofMemory,
	size_t numofMemory
	)
{
	FixedPool* self;

	self = Malloc(sizeof(FixedPool));
	if(self == NULL)
	{
		return NULL;
	}

	if(! __FixedPool_initialize(self, sizeofMemory, numofMemory))
	{
		return NULL;
	}
	return self;
}

// ------------------------------------------------------------------
static void __FixedPool_finalize(
	FixedPool* self
	)
{
	(void)self;
}

// ------------------------------------------------------------------
static void __FixedPool_destroy(
	MemoryPool* interface
	)
{
	FixedPool* self = (FixedPool*)interface;

	__FixedPool_finalize(self);
	Free(self);
}

// ------------------------------------------------------------------
static void* __FixedPool_allocate(
	MemoryPool* interface
	)
{
	FixedPool* self = (FixedPool*)interface;
	(void)self;
	return NULL;
}

// ------------------------------------------------------------------
static void __FixedPool_free(
	MemoryPool* interface,
	void* ptr
	)
{
	FixedPool* self = (FixedPool*)interface;
	(void)self;
	(void)ptr;
}

// ------------------------------------------------------------------
static const MemoryPoolMethodTable gFixedPoolMethodTable =
{
	.destroy	= __FixedPool_destroy,
	.allocate	= __FixedPool_allocate,
	.free		= __FixedPool_free,
};

