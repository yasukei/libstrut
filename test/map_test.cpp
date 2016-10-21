#include "../src/map.h"
#include <gtest/gtest.h>

TEST(PtrToPtrMap, create_destroy)
{
	PtrToPtrMap* map;

	// precondition

	// target
	map = PtrToPtrMap_create();

	// postcondition
	EXPECT_NE(nullptr, map);
	PtrToPtrMap_destroy(map);
}

TEST(PtrToPtrMap, add_find)
{
	PtrToPtrMap* map;
	int key;
	int value;

	// precondition
	map = PtrToPtrMap_create();

	// target
	PtrToPtrMap_add(map, (void*)&key, (void*)&value);

	// postcondition
	EXPECT_EQ(&value, PtrToPtrMap_find(map, &key));
	PtrToPtrMap_destroy(map);
}

TEST(_, _)
{
	// precondition

	// target

	// postcondition
}

