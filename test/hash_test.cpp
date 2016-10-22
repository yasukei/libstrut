#include <hash.h>
#include <gtest/gtest.h>

TEST(Hash, create_destroy)
{
	Hash* hash;

	// precondition

	// target
	hash = Hash_create();

	// postcondition
	EXPECT_NE(nullptr, hash);
	Hash_destroy(hash);
}

TEST(Hash, add_search)
{
	Hash* hash;
	int key;
	int value;

	// precondition
	hash = Hash_create();

	// target
	EXPECT_TRUE(Hash_add(hash, (void*)&key, (void*)&value));

	// postcondition
	EXPECT_EQ(&value, Hash_search(hash, &key));
	Hash_destroy(hash);
}

