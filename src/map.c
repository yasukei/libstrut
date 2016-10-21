
#include "map.h"

// ------------------------------------------------------------------
// Map
// ------------------------------------------------------------------
typedef struct Map
{
	size_t size;
	size_t used;
	void** keys;
	void** values;
}Map;

// ------------------------------------------------------------------
static bool __Map_initialize(
	Map* self,
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
Map* Map_create(
	void
	)
{
	Map* self;
	const size_t defaultMapSize = 64;

	self = Malloc(sizeof(Map));
	if(self == NULL)
	{
		return NULL;
	}

	if(! __Map_initialize(self, defaultMapSize))
	{
		return NULL;
	}
	return self;
}

// ------------------------------------------------------------------
static void __Map_finalize(
	Map* self
	)
{
	(void)self;
}

// ------------------------------------------------------------------
void Map_destroy(
	Map* self
	)
{
	__Map_finalize(self);
	Free(self);
}

// ------------------------------------------------------------------
bool __Map_resize(
	Map* self,
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
bool Map_add(
	Map* self,
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
		if(! __Map_resize(self, self->size * 2))
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
void* Map_find(
	Map* self,
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
//void Map_remove(
//	Map* self,
//	void* key,
//	void* value
//	)
//{
//}

// ------------------------------------------------------------------
void Map_foreach(
	Map* self,
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

