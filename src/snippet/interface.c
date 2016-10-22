
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
	void	(*destroy)(Interface* self);
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
void Interface_destroy(
	Interface* self
	)
{
	if(self->methodTable->destroy != NULL)
	{
		self->methodTable->destroy(self);
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
	return true;
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
	(void)self;
}

// ------------------------------------------------------------------
static void __Implement_destroy(
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
	.destroy = __Implement_destroy,
};

