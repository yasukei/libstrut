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
	void	(*delete)(MemoryPool* self);
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
void MemoryPool_delete(
	MemoryPool* self
	)
{
	if(self->methodTable->delete != NULL)
	{
		self->methodTable->delete(self);
	}
}

// ------------------------------------------------------------------
void* MemoryPool_allocate(
	MemoryPool* self
	)
{
	if(self->methodTable->allocate != NULL)
	{
		self->methodTable->allocate(self);
	}
}

// ------------------------------------------------------------------
void MemoryPool_free(
	MemoryPool* self,
	void* ptr
	)
{
	if(self->methodTable->free != NULL)
	{
		self->methodTable->free(self);
	}
}

// ------------------------------------------------------------------
// FixedPool
// ------------------------------------------------------------------
typedef struct FixedPool
{
	MemoryPool interface;
	void* memory;
	void** used;
	void** free;
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

	if(! __FixedPool_initialize(self))
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
static void __FixedPool_delete(
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

}

// ------------------------------------------------------------------
static void __FixedPool_free(
	MemoryPool* interface,
	void* ptr
	)
{
	FixedPool* self = (FixedPool*)interface;

}

// ------------------------------------------------------------------
static const MemoryPoolMethodTable gFixedPoolMethodTable =
{
	.delete		= __FixedPool_delete,
	.allocate	= __FixedPool_allocate,
	.free		= __FixedPool_free,
};

