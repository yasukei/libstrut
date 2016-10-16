
#include "map.h"

// ------------------------------------------------------------------
// PtrToPtrMap
// ------------------------------------------------------------------
typedef struct PtrToPtrMap
{
	size_t size;
	size_t used;
	void** keys;
	void** values;
}PtrToPtrMap;

// ------------------------------------------------------------------
static bool __PtrToPtrMap_initialize(
	PtrToPtrMap* self,
	size_t mapSize
	)
{
	self->size = mapSize;
	self->used = 0;
	self->keys = Malloc(sizeof(void*) * mapSize);
	self->values = Malloc(sizeof(void*) * mapSize);
	if( (self->keys == NULL) || (self->values == NULL) )
	{
		Free(self->keys);
		Free(self->values);
		return false;
	}
	return true;
}

// ------------------------------------------------------------------
PtrToPtrMap* PtrToPtrMap_create(
	void
	)
{
	PtrToPtrMap* self;
	const size_t defaultMapSize = 64;

	self = Malloc(sizeof(PtrToPtrMap));
	if(self == NULL)
	{
		return NULL;
	}

	if(! __PtrToPtrMap_initialize(self, defaultMapSize))
	{
		return NULL;
	}
	return self;
}

// ------------------------------------------------------------------
static void __PtrToPtrMap_finalize(
	PtrToPtrMap* self
	)
{
	(void)self;
}

// ------------------------------------------------------------------
void PtrToPtrMap_delete(
	PtrToPtrMap* self
	)
{
	__PtrToPtrMap_finalize(self);
	Free(self);
}

// ------------------------------------------------------------------
bool __PtrToPtrMap_resize(
	PtrToPtrMap* self,
	size_t newSize
	)
{
	void** newKeys;
	void** newValues;

	newKeys = Malloc(sizeof(void*) * newSize);
	newValues = Malloc(sizeof(void*) * newSize);
	if( (newKeys == NULL) || (newValues == NULL) )
	{
		Free(newKeys);
		Free(newValues);
		return false;
	}
	Memcpy(newKeys, self->keys, self->size);
	Memcpy(newValues, self->values, self->size);
	self->keys = newKeys;
	self->values = newValues;
	self->size = newSize;
	return true;
}

// ------------------------------------------------------------------
bool PtrToPtrMap_add(
	PtrToPtrMap* self,
	void* key,
	void* value
	)
{
	if(key == NULL)
	{
		return false;
	}

	if(self->used >= self->size)
	{
		if(! __PtrToPtrMap_resize(self, self->size * 2))
		{
			return false;
		}
	}

	self->keys[self->used] = key;
	self->values[self->used] = value;
	self->used += 1;
	return true;
}

// ------------------------------------------------------------------
void* PtrToPtrMap_find(
	PtrToPtrMap* self,
	void* key
	)
{
	size_t index;

	for(index = 0; index < self->used; index++)
	{
		if(self->keys[index] == key)
		{
			return self->values[index];
		}
	}
	return NULL;
}

// ------------------------------------------------------------------
//void PtrToPtrMap_remove(
//	PtrToPtrMap* self,
//	void* key,
//	void* value
//	)
//{
//}

// ------------------------------------------------------------------
void PtrToPtrMap_foreach(
	PtrToPtrMap* self,
	void (*procedure)(void* key, void* value, void* arg),
	void* arg
	)
{
	size_t index;

	for(index = 0; index < self->used; index++)
	{
		procedure(self->keys[index], self->values[index], arg);
	}
}

