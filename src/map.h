#ifndef _MAP_H_
#define _MAP_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
// ------------------------------------------------------------------


#include "facade.h"

// ------------------------------------------------------------------
// PtrToPtrMap
// ------------------------------------------------------------------
typedef struct PtrToPtrMap PtrToPtrMap;

PtrToPtrMap* PtrToPtrMap_create(
	void
	);
void PtrToPtrMap_destroy(
	PtrToPtrMap* self
	);
bool PtrToPtrMap_add(
	PtrToPtrMap* self,
	void* key,
	void* value
	);
void* PtrToPtrMap_find(
	PtrToPtrMap* self,
	void* key
	);
void PtrToPtrMap_foreach(
	PtrToPtrMap* self,
	void (*procedure)(void* key, void* value, void* arg),
	void* arg
	);


// ------------------------------------------------------------------
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _MAP_H_
