#ifndef _MEMORY_FACTORY_H_
#define _MEMORY_FACTORY_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "facade.h"
#include "memory.h"

// ------------------------------------------------------------------
// MemoryFactory
// ------------------------------------------------------------------
Memory* MemoryFactory_createOSMemory(
	void
	);
void MemoryFactory_destroyMemory(
	Memory* memory
	);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _MEMORY_FACTORY_H_

