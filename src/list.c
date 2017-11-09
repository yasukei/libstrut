#include "facade.h"
#include "list.h"
#include "memory.h"
#include "MemoryFactory.h"

// ------------------------------------------------------------------
// BidirectionalListNode
// ------------------------------------------------------------------
typedef struct BidirectionalListNode BidirectionalListNode;
struct BidirectionalListNode
{
	void* object;

	BidirectionalListNode* next;	// for BidirectionalList
	BidirectionalListNode* prev;	// for BidirectionalList
};

// ------------------------------------------------------------------
static void __BidirectionalListNode_initialize(
	BidirectionalListNode* self,
	void* object
)
{
	self->object = object;
	self->next = NULL;
	self->prev = NULL;
}

// ------------------------------------------------------------------
BidirectionalListNode* BidirectionalListNode_create(
	Memory* memory,
	void* object
)
{
	BidirectionalListNode* self;

	self = Memory_malloc(memory, sizeof(BidirectionalListNode));
	if(self == NULL)
	{
		return NULL;
	}

	__BidirectionalListNode_initialize(self, object);
	return self;
}

// ------------------------------------------------------------------
void BidirectionalListNode_destroy(
	BidirectionalListNode* self,
	Memory* memory
)
{
	Memory_free(memory, self);
}

// ------------------------------------------------------------------
void* BidirectionalListNode_getObject(
	BidirectionalListNode* self
)
{
	return self->object;
}

// ------------------------------------------------------------------
// BidirectionalList
// ------------------------------------------------------------------
typedef struct BidirectionalList BidirectionalList;
struct BidirectionalList
{
	List super;
	size_t numofNodes;
	BidirectionalListNode* head;
	BidirectionalListNode* tail;
	Memory* memory;
};

// ------------------------------------------------------------------
static bool BidirectionalList_addToHead(
	BidirectionalList* self,
	void* object
)
{
	BidirectionalListNode* node;

	node = BidirectionalListNode_create(self->memory, object);
	if(node == NULL)
	{
		return false;
	}

	if(self->numofNodes == 0)
	{
		self->head = node;
		self->tail = node;
		node->next = NULL;
	}
	else
	{
		self->head->prev = node;
		node->next = self->head;
		self->head = node;
	}
	node->prev = NULL;
	self->numofNodes += 1;

	return true;
}

// ------------------------------------------------------------------
static bool BidirectionalList_addToTail(
	BidirectionalList* self,
	void* object
)
{
	BidirectionalListNode* node;

	node = BidirectionalListNode_create(self->memory, object);
	if(node == NULL)
	{
		return false;
	}

	if(self->numofNodes == 0)
	{
		self->head = node;
		self->tail = node;
		node->prev = NULL;
	}
	else
	{
		self->tail->next = node;
		node->prev = self->tail;
		self->tail = node;
	}
	node->next = NULL;
	self->numofNodes += 1;

	return true;
}

// ------------------------------------------------------------------
bool BidirectionalList_insert(
	List* super,
	void* object,
	size_t index
)
{
	BidirectionalList* self = (BidirectionalList*)super;
	size_t i;
	BidirectionalListNode* node;
	BidirectionalListNode* newNode;
	BidirectionalListNode* prevNode;

	if(index > self->numofNodes)
	{
		return false;
	}

	if(index == 0)
	{
		return BidirectionalList_addToHead(self, object);
	}
	else if(index == self->numofNodes)
	{
		return BidirectionalList_addToTail(self, object);
	}

	newNode = BidirectionalListNode_create(self->memory, object);
	if(newNode == NULL)
	{
		return false;
	}

	node = self->head;
	for(i = 0; i < index; i++)
	{
		node = node->next;
	}
	prevNode = node->prev;

	prevNode->next = newNode;
	newNode->prev = prevNode;
	newNode->next = node;
	node->prev = newNode;
	self->numofNodes += 1;
	return true;
}

// ------------------------------------------------------------------
static void* BidirectionalList_removeFromHead(
	BidirectionalList* self
)
{
	BidirectionalListNode* node;
	void* object;

	if(self->numofNodes == 0)
	{
		return NULL;
	}

	if(self->numofNodes == 1)
	{
		node = self->head;
		self->head = NULL;
		self->tail = NULL;
	}
	else
	{
		node = self->head;
		self->head = node->next;
	}
	object = BidirectionalListNode_getObject(node);
	BidirectionalListNode_destroy(node, self->memory);
	self->numofNodes -= 1;
	return object;
}

// ------------------------------------------------------------------
static void* BidirectionalList_removeFromTail(
	BidirectionalList* self
)
{
	BidirectionalListNode* node;
	void* object;

	if(self->numofNodes == 0)
	{
		return NULL;
	}

	if(self->numofNodes == 1)
	{
		node = self->tail;
		self->head = NULL;
		self->tail = NULL;
	}
	else
	{
		node = self->tail;
		self->tail = node->prev;
	}
	object = BidirectionalListNode_getObject(node);
	BidirectionalListNode_destroy(node, self->memory);
	self->numofNodes -= 1;
	return object;
}

// ------------------------------------------------------------------
void* BidirectionalList_remove(
	List* super,
	size_t index
)
{
	BidirectionalList* self = (BidirectionalList*)super;
	void* object;
	BidirectionalListNode* node;
	BidirectionalListNode* prevNode;
	BidirectionalListNode* nextNode;
	size_t i;

	if(index >= self->numofNodes)
	{
		return NULL;
	}

	if(index == 0)
	{
		return BidirectionalList_removeFromHead(self);
	}
	else if(index == (self->numofNodes - 1))
	{
		return BidirectionalList_removeFromTail(self);
	}

	node = self->head;
	for(i = 0; i < index; i++)
	{
		node = node->next;
	}
	prevNode = node->prev;
	nextNode = node->next;

	prevNode->next = nextNode;
	nextNode->prev = prevNode;
	object = BidirectionalListNode_getObject(node);
	BidirectionalListNode_destroy(node, self->memory);
	self->numofNodes -= 1;
	return object;
}

// ------------------------------------------------------------------
void* BidirectionalList_getObject(
	List* super,
	size_t index
)
{
	BidirectionalList* self = (BidirectionalList*)super;
	BidirectionalListNode* node;
	size_t i;

	if(index >= self->numofNodes)
	{
		return NULL;
	}

	node = self->head;
	for(i = 0; i < index; i++)
	{
		node = node->next;
	}
	return BidirectionalListNode_getObject(node);
}

// ------------------------------------------------------------------
size_t BidirectionalList_getNumofObjects(
	List* super
)
{
	BidirectionalList* self = (BidirectionalList*)super;
	return self->numofNodes;
}

// ------------------------------------------------------------------
void BidirectionalList_foreach(
	List* super,
	void (*procedure)(void* object, void* arg),
	void* arg
)
{
	BidirectionalList* self = (BidirectionalList*)super;
	BidirectionalListNode* node;

	for(node = self->head; node != NULL; node = node->next)
	{
		procedure(BidirectionalListNode_getObject(node), arg);
	}
}

// ------------------------------------------------------------------
void BidirectionalList_destroy(
	List* super
)
{
	BidirectionalList* self = (BidirectionalList*)super;
	Memory* memory = self->memory;

	Memory_free(memory, self);
	MemoryFactory_destroyMemory(self->memory);
}

// ------------------------------------------------------------------
BidirectionalList* BidirectionalList_create(
	void
)
{
	Memory* memory = MemoryFactory_createOSMemory();
	BidirectionalList* self;

	self = Memory_malloc(memory, sizeof(BidirectionalList));

	self->numofNodes = 0;
	self->head = NULL;
	self->tail = NULL;
	self->memory = memory;
	self->super.insert = BidirectionalList_insert;
	self->super.remove = BidirectionalList_remove;
	self->super.getObject = BidirectionalList_getObject;
	self->super.getNumofObjects = BidirectionalList_getNumofObjects;
	self->super.foreach = BidirectionalList_foreach;
	self->super.destroy = BidirectionalList_destroy;

	return self;
}

// ------------------------------------------------------------------
// ListFactory
// ------------------------------------------------------------------
List* ListFactory_createBidirectionalList(
	void
	)
{
	return (List*)BidirectionalList_create();
}

// ------------------------------------------------------------------
void ListFactory_destroyList(
	List* list
	)
{
	List_destroy(list);
}

