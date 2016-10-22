#include "facade.h"
#include "list.h"


// ------------------------------------------------------------------
// ListNode
// ------------------------------------------------------------------
typedef struct ListNode ListNode;
struct ListNode
{
	void* valuePtr;
	ListNode* next;
};

// ------------------------------------------------------------------
ListNode* ListNode_create(
	void* valuePtr
	)
{
	ListNode* self;
   
	self = Malloc(sizeof(ListNode));
	if(self == NULL)
	{
		return NULL;
	}

	self->valuePtr = valuePtr;
	self->next = NULL;
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
void* ListNode_getValuePtr(
	ListNode* self
	)
{
	if(self == NULL)
	{
		return NULL;
	}

	return self->valuePtr;
}

// ------------------------------------------------------------------
// List
// ------------------------------------------------------------------
typedef int (*ListValueComparator)(const void* lhs, const void* rhs);

typedef struct List List;
struct List
{
	int numofNodes;
	ListNode* head;
	ListNode* tail;
	ListValueComparator comparator;
};


// ------------------------------------------------------------------
List* List_createWithComparator(
	ListValueComparator comparator
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
bool List_add(
	List* self,
	void* valuePtr
	)
{
	ListNode* node;
	
	node = ListNode_create(valuePtr);
	if(node == NULL)
	{
		return false;
	}

	if(self->numofNodes == 0)
	{
		self->head = node;
		self->tail = node;
	}
	else
	{
		self->tail->next = node;
		self->tail = node;
	}
	node->next = NULL;
	self->numofNodes += 1;

	return false;
}

// ------------------------------------------------------------------
static ListNode* __List_find(
	List* self,
	void* valuePtr,
	ListNode** prevNode	// out
	)
{
	ListNode* node;

	*prevNode = NULL;
	node = self->head;
	
	do
	{
		if(self->comparator(valuePtr, ListNode_getValuePtr(node)) == 0)
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
	void* valuePtr
	)
{
	ListNode* node;
	ListNode* prevNode;

	if(self == NULL)
	{
		return NULL;
	}

	node = __List_find(self, valuePtr, &prevNode);
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
void* List_get(
	List* self,
	int index
	)
{
	ListNode* node;
	int i;

	if(self == NULL)
	{
		return NULL;
	}
	if(self->numofNodes <= index)
	{
		return NULL;
	}

	node = self->head;
	for(i = 0; i < index; i++)
	{
		node = node->next;
	}
	return ListNode_getValuePtr(node);
}



