
#include "facade.h"

// ------------------------------------------------------------------
// Interface
// ------------------------------------------------------------------
typedef struct InterfaceMethodTable InterfaceMethodTable;
typedef struct Interface
{
	const InterfaceMethodTable* methodTable;
}Interface;

// ------------------------------------------------------------------
struct InterfaceMethodTable
{
	void	(*delete)(Interface* self);
};

// ------------------------------------------------------------------
void Interface_setMethodTable(
	Interface* self,
	const InterfaceMethodTable* methodTable
	)
{
	self->methodTable = methodTable;
}

// ------------------------------------------------------------------
void Interface_delete(
	Interface* self
	)
{
	if(self->methodTable->delete != NULL)
	{
		self->methodTable->delete(self);
	}
}

// ------------------------------------------------------------------
// Implement
// ------------------------------------------------------------------
typedef struct Implement
{
	Interface interface;
}Implement;

// ------------------------------------------------------------------
static const InterfaceMethodTable gImplementMethodTable;

// ------------------------------------------------------------------
static bool __Implement_initialize(
	Implement* self
	)
{
	Interface_setMethodTable((Interface*)self, &gImplementMethodTable);
}

// ------------------------------------------------------------------
Implement* Implement_create(
	void
	)
{
	Implement* self;

	self = Malloc(sizeof(Implement));
	if(self == NULL)
	{
		return NULL;
	}

	if(! __Implement_initialize(self))
	{
		return NULL;
	}
	return self;
}

// ------------------------------------------------------------------
static void __Implement_finalize(
	Implement* self
	)
{
}

// ------------------------------------------------------------------
static void __Implement_delete(
	Interface* interface
	)
{
	Implement* self = (Implement*)interface;

	__Implement_finalize(self);
	Free(self);
}

// ------------------------------------------------------------------
static const InterfaceMethodTable gImplementMethodTable =
{
	.delete = __Implement_delete,
};

