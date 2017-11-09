#ifndef _LIST_FACTORY_H_
#define _LIST_FACTORY_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "facade.h"
#include "list.h"

// ------------------------------------------------------------------
// ListFactory
// ------------------------------------------------------------------
List* ListFactory_createBidirectionalList(
	void
	);
void ListFactory_destroyList(
	List* list
	);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _LIST_FACTORY_H_

