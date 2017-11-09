#include <list.h>
#include <ListFactory.h>
#include <gtest/gtest.h>

// --------------------------------------------------------
TEST(List, create_destroy)
{
	List* list;

	// precondition

	// target
	list = ListFactory_createBidirectionalList();

	// postcondition
	EXPECT_NE((void*)NULL, list);
	ListFactory_destroyList(list);
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
			list = ListFactory_createBidirectionalList();
			num = GetParam();
			objects = (int*)malloc(sizeof(int) * num);
		}
		virtual void TearDown()
		{
			free(objects);
			ListFactory_destroyList(list);
		}
};

// --------------------------------------------------------
TEST_P(List_test, insert_remove)
{

	// precondition

	// target
	for(size_t i = 0; i < num; i++)
	{
		EXPECT_TRUE(List_insert(list, &objects[i], i));
	}

	// postcondition
	for(size_t i = 0; i < num; i++)
	{
		EXPECT_EQ(&objects[i], List_remove(list, 0));
	}
}

// --------------------------------------------------------
TEST_P(List_test, getNumofObjects)
{

	// precondition
	for(size_t i = 0; i < num; i++)
	{
		EXPECT_TRUE(List_insert(list, &objects[i], i));
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
//	list = ListFactory_createBidirectionalList();
//	EXPECT_TRUE(List_add(list, (void*)&key1, (void*)&value1));
//	EXPECT_TRUE(List_add(list, (void*)&key2, (void*)&value2));
//
//	// target
//	List_foreach(list, __testListForeach, &gTestArg);
//
//	// postcondition
//	ListFactory_destroy(list);
//}

