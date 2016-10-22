#ifndef _HASH_H_
#define _HASH_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
// ------------------------------------------------------------------


#include "facade.h"

// ------------------------------------------------------------------
// Hash
// ------------------------------------------------------------------
typedef struct Hash Hash;

Hash* Hash_create(
	void
	);
void Hash_destroy(
	Hash* self
	);
bool Hash_add(
	Hash* self,
	void* key,
	void* value
	);
void* Hash_search(
	Hash* self,
	void* key
	);
void Hash_foreach(
	Hash* self,
	void (*procedure)(void* key, void* value, void* arg),
	void* arg
	);


// ------------------------------------------------------------------
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _HASH_H_
