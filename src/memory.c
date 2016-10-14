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
// FixedPool
// ------------------------------------------------------------------
typedef struct FixedPool
{
	MemoryPool interface;
}FixedPool;

// ------------------------------------------------------------------
static const MemoryPoolMethodTable gFixedPoolMethodTable;

// ------------------------------------------------------------------
static bool __FixedPool_initialize(
	FixedPool* self
	)
{
	MemoryPool_setMethodTable((MemoryPool*)self, &gFixedPoolMethodTable);
	return true;
}

// ------------------------------------------------------------------
FixedPool* FixedPool_create(
	void
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
static const MemoryPoolMethodTable gFixedPoolMethodTable =
{
	.delete = __FixedPool_delete,
};

