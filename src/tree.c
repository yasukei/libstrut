
#include "tree.h"

// ------------------------------------------------------------------
// Tree
// ------------------------------------------------------------------
typedef struct Tree
{
}Tree;

// ------------------------------------------------------------------
static bool __Tree_initialize(
	Tree* self
	)
{
	(void)self;
	return true;
}

// ------------------------------------------------------------------
Tree* Tree_create(
	void
	)
{
	Tree* self;

	self = Malloc(sizeof(Tree));
	if(self == NULL)
	{
		return NULL;
	}

	if(! __Tree_initialize(self))
	{
		return NULL;
	}
	return self;
}

// ------------------------------------------------------------------
static void __Tree_finalize(
	Tree* self
	)
{
	(void)self;
}

// ------------------------------------------------------------------
void Tree_destroy(
	Tree* self
	)
{
	__Tree_finalize(self);
	Free(self);
}

