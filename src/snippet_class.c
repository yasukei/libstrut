
#include "facade.h"

// ------------------------------------------------------------------
// Class
// ------------------------------------------------------------------
typedef struct Class
{
}Class;

// ------------------------------------------------------------------
static bool __Class_initialize(
	Class* self
	)
{
	return true;
}

// ------------------------------------------------------------------
Class* Class_create(
	void
	)
{
	Class* self;

	self = Malloc(sizeof(Class));
	if(self == NULL)
	{
		return NULL;
	}

	if(! __Class_initialize(self))
	{
		return NULL;
	}
	return self;
}

// ------------------------------------------------------------------
static void __Class_finalize(
	Class* self
	)
{
}

// ------------------------------------------------------------------
void Class_delete(
	Class* self
	)
{
	__Class_finalize(self);
	Free(self);
}

