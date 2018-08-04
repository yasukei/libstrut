#ifndef _MAP_H_
#define _MAP_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
// ------------------------------------------------------------------


#include "facade.h"

// ------------------------------------------------------------------
// Map
// ------------------------------------------------------------------
typedef struct Map Map;

// ------------------------------------------------------------------
struct Map
{
	bool	(*add)(Map* self, void* key, void* value);
	void*	(*find)(Map* self, void* key);
	void	(*foreach)(Map* self, void (*procedure)(void* key, void* value, void* arg), void* arg);
	void	(*destroy)(Map* self);
};

// ------------------------------------------------------------------
static inline bool Map_add(
	Map* self,
	void* key,
	void* value
	)
{
	return self->add(self, key, value);
}

// ------------------------------------------------------------------
static inline void* Map_find(
	Map* self,
	void* key
	)
{
	return self->find(self, key);
}

// ------------------------------------------------------------------
static inline void Map_foreach(
	Map* self,
	void (*procedure)(void* key, void* value, void* arg),
	void* arg
	)
{
	return self->foreach(self, procedure, arg);
}

// ------------------------------------------------------------------
static inline void Map_destroy(
	Map* self
	)
{
	return self->destroy(self);
}


// ------------------------------------------------------------------
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _MAP_H_
