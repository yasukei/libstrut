#include <stddef.h>
#include <stdint.h>

typedef struct List List;
typedef struct ListFactory ListFactory;

List* ListFactory_createList(
	void
	);

List* ListFactory_createFixedSizeList(
	size_t maxNumofElems
	);

List* ListFactory_createFixedSizeList(
	uint8_t memoryToBeUsedByFixedSizeList
	);
size_t ListFactory_getSizeofFixedSizeList(
	size_t maxNumofElems
	);
	
