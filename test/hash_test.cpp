#include <hash.h>
#include <gtest/gtest.h>

TEST(Hash, create_destroy)
{
	Hash* hash;

	// precondition

	// target
	hash = Hash_create();

	// postcondition
	EXPECT_NE((void*)NULL, hash);
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

int gTestArg;

void __testHashForeach(
	void* key,
	void* value,
	void* arg
	)
{
	int k = *(int*)key;
	int v = *(int*)value;
	printf("key:   [%d]\n", k);
	printf("value: [%d]\n", v);

	EXPECT_EQ((void*)&gTestArg, arg);
}

TEST(Hash, foreach)
{
	Hash* hash;
	int key1 = 1;
	int key2 = 2;
	int value1 = 10;
	int value2 = 20;

	// precondition
	hash = Hash_create();
	EXPECT_TRUE(Hash_add(hash, (void*)&key1, (void*)&value1));
	EXPECT_TRUE(Hash_add(hash, (void*)&key2, (void*)&value2));

	// target
	Hash_foreach(hash, __testHashForeach, &gTestArg);

	// postcondition
	Hash_destroy(hash);
}

