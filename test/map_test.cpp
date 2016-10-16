#include "../src/map.h"
#include <gtest/gtest.h>

TEST(testMultiplication, 1)
{
	PtrToPtrMap* map;
	
	map = PtrToPtrMap_create();

	EXPECT_NE(nullptr, map);
}

