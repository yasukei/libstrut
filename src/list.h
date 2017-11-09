#ifndef _LIST_H_
#define _LIST_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "facade.h"

// ------------------------------------------------------------------
// List
// ------------------------------------------------------------------
typedef struct List List;

// ------------------------------------------------------------------
struct List
{
	bool	(*insert)(List* self, void* object, size_t index);
	void*	(*remove)(List* self, size_t index);
	void*	(*getObject)(List* self, size_t index);
	size_t	(*getNumofObjects)(List* self);
	void	(*foreach)(List* self, void (*procedure)(void* object, void* arg), void* arg);
	void	(*destroy)(List* self);
};

// ------------------------------------------------------------------
static inline bool List_insert(
	List* self,
	void* object,
	size_t index
	)
{
	return self->insert(self, object, index);
}

// ------------------------------------------------------------------
static inline void* List_remove(
	List* self,
	size_t index
	)
{
	return self->remove(self, index);
}

// ------------------------------------------------------------------
static inline void* List_getObject(
	List* self,
	size_t index
	)
{
	return self->getObject(self, index);
}

// ------------------------------------------------------------------
static inline size_t List_getNumofObjects(
	List* self
	)
{
	return self->getNumofObjects(self);
}

// ------------------------------------------------------------------
static inline void List_foreach(
	List* self,
	void (*procedure)(void* object, void* arg),
	void* arg
	)
{
	self->foreach(self, procedure, arg);
}

// ------------------------------------------------------------------
static inline void List_destroy(
	List* self
	)
{
	self->destroy(self);
}


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _LIST_H_
