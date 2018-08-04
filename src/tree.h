#ifndef _TREE_H_
#define _TREE_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
// ------------------------------------------------------------------


#include "facade.h"

// ------------------------------------------------------------------
// Tree
// ------------------------------------------------------------------
typedef struct Tree Tree;

Tree* Tree_create(
	void
	);
void Tree_destroy(
	Tree* self
	);
void Tree_add(
	Tree* self,
	void* object
	);


// ------------------------------------------------------------------
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _TREE_H_
