#include <map.h>
#include <MapFactory.h>
#include <gtest/gtest.h>

TEST(Map, create_destroy)
{
	Map* map;

	// precondition

	// target
	map = MapFactory_createSimpleMap();

	// postcondition
	EXPECT_NE((void*)NULL, map);
	Map_destroy(map);
}

TEST(Map, add_find)
{
	Map* map;
	int key;
	int value;

	// precondition
	map = MapFactory_createSimpleMap();

	// target
	Map_add(map, (void*)&key, (void*)&value);

	// postcondition
	EXPECT_EQ(&value, Map_find(map, &key));
	Map_destroy(map);
}

TEST(Map, _)
{
	// precondition

	// target

	// postcondition
}

