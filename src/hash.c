
#include "hash.h"

// ------------------------------------------------------------------
// HashNode
// ------------------------------------------------------------------
typedef struct HashNode HashNode;
struct HashNode
{
	void* key;
	void* value;
	HashNode* next;
};

// ------------------------------------------------------------------
static bool __HashNode_initialize(
	HashNode* self,
	void* key,
	void* value
	)
{
	self->key = key;
	self->value = value;
	return true;
}

// ------------------------------------------------------------------
HashNode* HashNode_create(
	void* key,
	void* value
	)
{
	HashNode* self;

	self = Malloc(sizeof(HashNode));
	if(self == NULL)
	{
		return NULL;
	}

	if(! __HashNode_initialize(self, key, value))
	{
		return NULL;
	}
	return self;
}

// ------------------------------------------------------------------
static void __HashNode_finalize(
	HashNode* self
	)
{
	(void)self;
}

// ------------------------------------------------------------------
void HashNode_destroy(
	HashNode* self
	)
{
	__HashNode_finalize(self);
	Free(self);
}

// ------------------------------------------------------------------
void* HashNode_getKey(
	HashNode* self
	)
{
	return self->key;
}

// ------------------------------------------------------------------
void* HashNode_getValue(
	HashNode* self
	)
{
	return self->value;
}

// ------------------------------------------------------------------
// Hash
// ------------------------------------------------------------------
struct Hash
{
	size_t size;
	HashNode** hash;
};

// ------------------------------------------------------------------
static bool __Hash_initialize(
	Hash* self,
	size_t hashSize
	)
{
	size_t i;

	self->size = hashSize;
	self->hash = Malloc(sizeof(HashNode*) * self->size);
	if(self->hash == NULL)
	{
		return false;
	}

	for(i = 0; i < self->size; i++)
	{
		self->hash[i] = NULL;
	}

	return true;
}

// ------------------------------------------------------------------
Hash* Hash_create(
	void
	)
{
	Hash* self;
	const size_t defaultHashSize = 64;

	self = Malloc(sizeof(Hash));
	if(self == NULL)
	{
		return NULL;
	}

	if(! __Hash_initialize(self, defaultHashSize))
	{
		return NULL;
	}
	return self;
}

// ------------------------------------------------------------------
static void __Hash_finalize(
	Hash* self
	)
{
	Free(self->hash);
}

// ------------------------------------------------------------------
void Hash_destroy(
	Hash* self
	)
{
	__Hash_finalize(self);
	Free(self);
}

// ------------------------------------------------------------------
static size_t __Hash_calculateHashValue(
	Hash* self,
	void* key
	)
{
	return (size_t)(key) % self->size;
}

// ------------------------------------------------------------------
void __Hash_add(
	Hash* self,
	HashNode* node
	)
{
	size_t hashValue;

	hashValue = __Hash_calculateHashValue(self, HashNode_getKey(node));

	node->next = self->hash[hashValue];
	self->hash[hashValue] = node;
}

// ------------------------------------------------------------------
bool Hash_add(
	Hash* self,
	void* key,
	void* value
	)
{
	HashNode* node;

	if(key == NULL)
	{
		return false;
	}

	node = HashNode_create(key, value);
	if(node == NULL)
	{
		return false;
	}

	__Hash_add(self, node);
	return true;
}

// ------------------------------------------------------------------
void* Hash_search(
	Hash* self,
	void* key
	)
{
	size_t hashValue;
	HashNode* node;

	hashValue = __Hash_calculateHashValue(self, key);

	for(node = self->hash[hashValue];
		node != NULL;
		node = node->next)
	{
		if(HashNode_getKey(node) == key)
		{
			return HashNode_getValue(node);
		}
	}
	return NULL;
}

// ------------------------------------------------------------------
//void Hash_remove(
//	Hash* self,
//	void* key,
//	void* value
//	)
//{
//}

// ------------------------------------------------------------------
void Hash_foreach(
	Hash* self,
	void (*procedure)(void* key, void* value, void* arg),
	void* arg
	)
{
	size_t i;
	HashNode* node;

	for(i = 0; i < self->size; i++)
	{
		for(node = self->hash[i];
			node != NULL;
			node = node->next)
		{
			procedure(
				HashNode_getKey(node),
				HashNode_getValue(node),
				arg
				);
		}
	}
}

