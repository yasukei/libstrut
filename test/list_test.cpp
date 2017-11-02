#include <list.h>
#include <gtest/gtest.h>

// --------------------------------------------------------
TEST(List, create_destroy)
{
	List* list;

	// precondition

	// target
	list = List_create();

	// postcondition
	EXPECT_NE((void*)NULL, list);
	List_destroy(list);
}

// --------------------------------------------------------
TEST(List, self_is_null)
{
	List* list;
	int dummy;

	// precondition
	list = NULL;

	// target
	List_destroy(list);
	EXPECT_FALSE(List_addToHead(list, &dummy));
	EXPECT_FALSE(List_addToTail(list, &dummy));
	EXPECT_EQ((void*)NULL, List_removeFromHead(list));
	EXPECT_EQ((void*)NULL, List_removeFromTail(list));

	// postcondition
}

// --------------------------------------------------------
class List_test : public ::testing::TestWithParam<size_t>
			//std::tuple< BYTE*, size_t >
{ 
protected:
	List* list;
	size_t num;
	int* objects;

	virtual void SetUp()
	{
		list = List_create();
		num = GetParam();
		objects = (int*)malloc(sizeof(int) * num);
	}
	virtual void TearDown()
	{
		free(objects);
		List_destroy(list);
	}
};

// --------------------------------------------------------
TEST_P(List_test, addToHead_removeFromTail)
{

	// precondition

	// target
	for(size_t i = 0; i < num; i++)
	{
		EXPECT_TRUE(List_addToHead(list, &objects[i]));
	}

	// postcondition
	for(size_t i = 0; i < num; i++)
	{
		EXPECT_EQ(&objects[i], List_removeFromTail(list));
	}
}

// --------------------------------------------------------
TEST_P(List_test, addToHead_removeFromHead)
{

	// precondition

	// target
	for(size_t i = 0; i < num; i++)
	{
		EXPECT_TRUE(List_addToHead(list, &objects[i]));
	}

	// postcondition
	for(size_t i = num; i > 0; i--)
	{
		EXPECT_EQ(&objects[i-1], List_removeFromHead(list));
	}
}

// --------------------------------------------------------
TEST_P(List_test, addToTail_removeFromHead)
{

	// precondition

	// target
	for(size_t i = 0; i < num; i++)
	{
		EXPECT_TRUE(List_addToTail(list, &objects[i]));
	}

	// postcondition
	for(size_t i = 0; i < num; i++)
	{
		EXPECT_EQ(&objects[i], List_removeFromHead(list));
	}
}

// --------------------------------------------------------
TEST_P(List_test, addToTail_removeFromTail)
{

	// precondition

	// target
	for(size_t i = 0; i < num; i++)
	{
		EXPECT_TRUE(List_addToTail(list, &objects[i]));
	}

	// postcondition
	for(size_t i = num; i > 0; i--)
	{
		EXPECT_EQ(&objects[i-1], List_removeFromTail(list));
	}
}

// --------------------------------------------------------
TEST_P(List_test, getNumofObjects_afterAddToHead)
{

	// precondition
	for(size_t i = 0; i < num; i++)
	{
		EXPECT_TRUE(List_addToHead(list, &objects[i]));
	}

	// target
	EXPECT_EQ(num, List_getNumofObjects(list));

	// postcondition
}

// --------------------------------------------------------
TEST_P(List_test, getNumofObjects_afterAddToTail)
{

	// precondition
	for(size_t i = 0; i < num; i++)
	{
		EXPECT_TRUE(List_addToTail(list, &objects[i]));
	}

	// target
	EXPECT_EQ(num, List_getNumofObjects(list));

	// postcondition
}

// --------------------------------------------------------
TEST_P(List_test, getNumofObjects_afterRemoveFromHead)
{

	// precondition
	for(size_t i = 0; i < num; i++)
	{
		EXPECT_TRUE(List_addToTail(list, &objects[i]));
	}

	// target
	EXPECT_EQ(num, List_getNumofObjects(list));

	// postcondition
}

// --------------------------------------------------------
INSTANTIATE_TEST_CASE_P(
	parameterized_instance,
	List_test,
	testing::Values(1, 2, 3, 10)
);

//int gTestArg;
//
//void __testListForeach(
//	void* key,
//	void* value,
//	void* arg
//	)
//{
//	int k = *(int*)key;
//	int v = *(int*)value;
//	printf("key:   [%d]\n", k);
//	printf("value: [%d]\n", v);
//
//	EXPECT_EQ((void*)&gTestArg, arg);
//}
//
//TEST(List, foreach)
//{
//	List* list;
//	int key1 = 1;
//	int key2 = 2;
//	int value1 = 10;
//	int value2 = 20;
//
//	// precondition
//	list = List_create();
//	EXPECT_TRUE(List_add(list, (void*)&key1, (void*)&value1));
//	EXPECT_TRUE(List_add(list, (void*)&key2, (void*)&value2));
//
//	// target
//	List_foreach(list, __testListForeach, &gTestArg);
//
//	// postcondition
//	List_destroy(list);
//}

