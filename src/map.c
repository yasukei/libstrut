
#include <string.h>
#include "map.h"
#include "memory.h"
#include "MemoryFactory.h"

// ------------------------------------------------------------------
// SimpleMap
// ------------------------------------------------------------------
typedef struct SimpleMap
{
	Map super;
	size_t size;
	size_t used;
	void** keys;
	void** values;
	Memory* memory;
} SimpleMap;

// ------------------------------------------------------------------
bool __SimpleMap_resize(
	SimpleMap* self,
	size_t newSize
)
{
	void** newKeys;
	void** newValues;

	newKeys = Memory_malloc(self->memory, sizeof(void*) * newSize);
	newValues = Memory_malloc(self->memory, sizeof(void*) * newSize);
	if((newKeys == NULL) || (newValues == NULL))
	{
		Memory_free(self->memory, newKeys);
		Memory_free(self->memory, newValues);
		return false;
	}
	memcpy(newKeys, self->keys, self->size);
	memcpy(newValues, self->values, self->size);
	self->keys = newKeys;
	self->values = newValues;
	self->size = newSize;
	return true;
}

// ------------------------------------------------------------------
bool SimpleMap_add(
	Map* super,
	void* key,
	void* value
)
{
	SimpleMap* self = (SimpleMap*)super;

	if(key == NULL)
	{
		return false;
	}

	if(self->used >= self->size)
	{
		if(! __SimpleMap_resize(self, self->size * 2))
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
void* SimpleMap_find(
	Map* super,
	void* key
)
{
	SimpleMap* self = (SimpleMap*)super;
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
//void SimpleMap_remove(
//	Map* super,
//	void* key,
//	void* value
//	)
//{
//}

// ------------------------------------------------------------------
void SimpleMap_foreach(
	Map* super,
	void (*procedure)(void* key, void* value, void* arg),
	void* arg
)
{
	SimpleMap* self = (SimpleMap*)super;
	size_t index;

	for(index = 0; index < self->used; index++)
	{
		procedure(self->keys[index], self->values[index], arg);
	}
}

// ------------------------------------------------------------------
static void __SimpleMap_finalize(
	SimpleMap* self
)
{
	Memory_free(self->memory, self->keys);
	Memory_free(self->memory, self->values);
}

// ------------------------------------------------------------------
void SimpleMap_destroy(
	Map* super
)
{
	SimpleMap* self = (SimpleMap*)super;

	Memory* memory = self->memory;
	__SimpleMap_finalize(self);
	Memory_free(memory, self);
	MemoryFactory_destroyMemory(memory);
}

// ------------------------------------------------------------------
static bool __SimpleMap_initialize(
	SimpleMap* self,
	size_t mapSize,
	Memory* memory
)
{
	self->size = mapSize;
	self->used = 0;
	self->keys = Memory_malloc(memory, sizeof(void*) * mapSize);
	self->values = Memory_malloc(memory, sizeof(void*) * mapSize);
	if((self->keys == NULL) || (self->values == NULL))
	{
		Memory_free(memory, self->keys);
		Memory_free(memory, self->values);
		return false;
	}
	self->memory = memory;
	self->super.add = SimpleMap_add;
	self->super.find = SimpleMap_find;
	self->super.foreach = SimpleMap_foreach;
	self->super.destroy = SimpleMap_destroy;
	return true;
}

// ------------------------------------------------------------------
SimpleMap* SimpleMap_create(
	void
)
{
	Memory* memory = MemoryFactory_createOSMemory();
	SimpleMap* self;
	const size_t defaultSimpleMapSize = 64;

	self = Memory_malloc(memory, sizeof(SimpleMap));
	if(self == NULL)
	{
		return NULL;
	}

	if(! __SimpleMap_initialize(self, defaultSimpleMapSize, memory))
	{
		return NULL;
	}
	return self;
}

// ------------------------------------------------------------------
// MapFactory
// ------------------------------------------------------------------
Map* MapFactory_createSimpleMap(
	void
	)
{
	return (Map*)SimpleMap_create();
}

// ------------------------------------------------------------------
void MapFactory_destroyMap(
	Map* map
	)
{
	Map_destroy(map);
}

