#include "facade.h"
#include "list.h"


// ------------------------------------------------------------------
// ListNode
// ------------------------------------------------------------------
typedef struct ListNode ListNode;
struct ListNode
{
	void* object;

	ListNode* next;	// for List
	ListNode* prev;	// for List
};

// ------------------------------------------------------------------
static bool __ListNode_initialize(
	ListNode* self,
	void* object
	)
{
	self->object = object;
	self->next = NULL;
	self->prev = NULL;
	return true;
}

// ------------------------------------------------------------------
ListNode* ListNode_create(
	void* object
	)
{
	ListNode* self;
   
	self = Malloc(sizeof(ListNode));
	if(self == NULL)
	{
		return NULL;
	}

	if(! __ListNode_initialize(self, object))
	{
		return NULL;
	}
	return self;
}

// ------------------------------------------------------------------
void ListNode_destroy(
	ListNode* self
	)
{
	Free(self);
}

// ------------------------------------------------------------------
void* ListNode_getObject(
	ListNode* self
	)
{
	return self->object;
}

// ------------------------------------------------------------------
// List
// ------------------------------------------------------------------
typedef int (*ListObjectComparator)(const void* lhs, const void* rhs);

typedef struct List List;
struct List
{
	size_t numofNodes;
	ListNode* head;
	ListNode* tail;
	ListObjectComparator comparator;
};

// ------------------------------------------------------------------
List* List_createWithComparator(
	ListObjectComparator comparator
	)
{
	List* self;

	self = Malloc(sizeof(List));

	self->numofNodes = 0;
	self->head = NULL;
	self->tail = NULL;
	self->comparator = comparator;

	return self;
}

// ------------------------------------------------------------------
static int __List_compare(
	const void* lhs,
	const void* rhs
	)
{
	if(lhs > rhs)
	{
		return 1;
	}
	else if(lhs < rhs)
	{
		return -1;
	}
	return 0;
}

// ------------------------------------------------------------------
List* List_create(
	void
	)
{
	return List_createWithComparator(__List_compare);
}

// ------------------------------------------------------------------
void List_destroy(
	List* self
	)
{
	if(self == NULL)
	{
		return;
	}

	Free(self);
}

// ------------------------------------------------------------------
bool List_addToHead(
	List* self,
	void* object
	)
{
	ListNode* node;

	if(self == NULL)
	{
		return false;
	}

	node = ListNode_create(object);
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
bool List_addToTail(
	List* self,
	void* object
	)
{
	ListNode* node;

	if(self == NULL)
	{
		return false;
	}

	node = ListNode_create(object);
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
bool List_insert(
	List* self,
	void* object,
	size_t index
	)
{
	size_t i;
	ListNode* node;
	ListNode* newNode;
	ListNode* prevNode;

	if(index > self->numofNodes)
	{
		return false;
	}

	if(index == 0)
	{
		return List_addToHead(self, object);
	}
	else if(index == self->numofNodes)
	{
		return List_addToTail(self, object);
	}

	newNode = ListNode_create(object);
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
void* List_get(
	List* self,
	size_t index
	)
{
	ListNode* node;
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
	return ListNode_getObject(node);
}

// ------------------------------------------------------------------
size_t List_getNumofObjects(
	List* self
	)
{
	return self->numofNodes;
}

// ------------------------------------------------------------------
static ListNode* __List_find(
	List* self,
	void* object,
	ListNode** prevNode	// out
	)
{
	ListNode* node;

	*prevNode = NULL;
	node = self->head;
	
	do
	{
		if(self->comparator(object, ListNode_getObject(node)) == 0)
		{
			break;
		}
		*prevNode = node;
		node = node->next;
	}
	while(node != NULL);

	return node;
}

// ------------------------------------------------------------------
bool List_remove(
	List* self,
	void* object
	)
{
	ListNode* node;
	ListNode* prevNode;

	if(self == NULL)
	{
		return NULL;
	}

	node = __List_find(self, object, &prevNode);
	if(node == NULL)
	{
		return false;
	}

	if(node == self->head)
	{
		self->head = NULL;
		self->tail = NULL;
	}
	ListNode_destroy(node);
	return true;
}

// ------------------------------------------------------------------
void* List_removeFromHead(
	List* self
	)
{
	ListNode* node;
	void* object;

	if(self == NULL)
	{
		return NULL;
	}
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
	object = ListNode_getObject(node);
	ListNode_destroy(node);
	return object;
}

// ------------------------------------------------------------------
void* List_removeFromTail(
	List* self
	)
{
	ListNode* node;
	void* object;

	if(self == NULL)
	{
		return NULL;
	}
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
	object = ListNode_getObject(node);
	ListNode_destroy(node);
	return object;
}

