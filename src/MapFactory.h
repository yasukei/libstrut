#ifndef _MAP_FACTORY_H_
#define _MAP_FACTORY_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "facade.h"
#include "map.h"

// ------------------------------------------------------------------
// MapFactory
// ------------------------------------------------------------------
Map* MapFactory_createSimpleMap(
	void
	);
void MapFactory_destroyMap(
	Map* map
	);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _MAP_FACTORY_H_

