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

Map* Map_create(
	void
	);
void Map_destroy(
	Map* self
	);
bool Map_add(
	Map* self,
	void* key,
	void* value
	);
void* Map_find(
	Map* self,
	void* key
	);
void Map_foreach(
	Map* self,
	void (*procedure)(void* key, void* value, void* arg),
	void* arg
	);


// ------------------------------------------------------------------
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _MAP_H_
