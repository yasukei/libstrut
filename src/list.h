#ifndef _LIST_H_
#define _LIST_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "facade.h"

typedef struct List List;

List* List_create(
	void
	);
void List_destroy(
	List* self
	);
bool List_addToHead(
	List* self,
	void* object
	);
bool List_addToTail(
	List* self,
	void* object
	);
void* List_removeFromHead(
	List* self
	);
void* List_removeFromTail(
	List* self
	);
bool List_insert(
	List* self,
	void* object,
	size_t index
	);
void* List_get(
	List* self,
	size_t index
	);
size_t List_getNumofObjects(
	List* self
	);
bool List_remove(
	List* self,
	void* object
	);
void List_foreach(
	List* self,
	void (*procedure)(void* object, void* arg),
	void* arg
	);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _LIST_H_
