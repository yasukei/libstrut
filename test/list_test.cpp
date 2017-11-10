#include <list.h>
#include <ListFactory.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::IsNull;
using ::testing::Eq;

// --------------------------------------------------------
TEST(List, create_destroy)
{
	List* list = ListFactory_createBidirectionalList();

	EXPECT_NE((void*)NULL, list);
	ListFactory_destroyList(list);
}

// --------------------------------------------------------
class List_test : public ::testing::TestWithParam<List*>
//std::tuple< BYTE*, size_t >
{
	protected:
		List* list;
		int object1;
		int object2;
		int object3;
		int object4;

		virtual void SetUp()
		{
			list = GetParam();
		}
		virtual void TearDown()
		{
			ListFactory_destroyList(list);
		}
};

// --------------------------------------------------------
TEST_P(List_test, initial_state)
{
	EXPECT_THAT(List_getObject(list, 0), IsNull());
	EXPECT_THAT(List_getNumofObjects(list), Eq(0));
}

// --------------------------------------------------------
TEST_P(List_test, insert_in_empty)
{
	ASSERT_TRUE(List_insert(list, &object1, 0));

	EXPECT_THAT(List_getObject(list, 0), Eq(&object1));
	EXPECT_THAT(List_getObject(list, 1), IsNull());
	EXPECT_THAT(List_getNumofObjects(list), Eq(1));
}

// --------------------------------------------------------
TEST_P(List_test, insert_in_front)
{
	ASSERT_TRUE(List_insert(list, &object1, 0));
	ASSERT_TRUE(List_insert(list, &object2, 0));

	EXPECT_THAT(List_getObject(list, 0), Eq(&object2));
	EXPECT_THAT(List_getObject(list, 1), Eq(&object1));
	EXPECT_THAT(List_getObject(list, 2), IsNull());
	EXPECT_THAT(List_getNumofObjects(list), Eq(2));
}

// --------------------------------------------------------
TEST_P(List_test, insert_in_behind)
{
	ASSERT_TRUE(List_insert(list, &object1, 0));
	ASSERT_TRUE(List_insert(list, &object2, 0));

	EXPECT_THAT(List_getObject(list, 0), Eq(&object2));
	EXPECT_THAT(List_getObject(list, 1), Eq(&object1));
	EXPECT_THAT(List_getObject(list, 2), IsNull());
	EXPECT_THAT(List_getNumofObjects(list), Eq(2));
}

// --------------------------------------------------------
TEST_P(List_test, insert_in_between)
{
	ASSERT_TRUE(List_insert(list, &object1, 0));
	ASSERT_TRUE(List_insert(list, &object2, 1));
	ASSERT_TRUE(List_insert(list, &object3, 1));

	EXPECT_THAT(List_getObject(list, 0), Eq(&object1));
	EXPECT_THAT(List_getObject(list, 1), Eq(&object3));
	EXPECT_THAT(List_getObject(list, 2), Eq(&object2));
	EXPECT_THAT(List_getObject(list, 3), IsNull());
	EXPECT_THAT(List_getNumofObjects(list), Eq(3));
}

// --------------------------------------------------------
TEST_P(List_test, remove_empty)
{
	EXPECT_THAT(List_getObject(list, 0), IsNull());
	ASSERT_THAT(List_remove(list, 0), IsNull());

	EXPECT_THAT(List_getObject(list, 0), IsNull());
	EXPECT_THAT(List_getNumofObjects(list), Eq(0));
}

// --------------------------------------------------------
TEST_P(List_test, remove_last_one)
{
	ASSERT_TRUE(List_insert(list, &object1, 0));
	ASSERT_THAT(List_remove(list, 0), Eq(&object1));

	EXPECT_THAT(List_getObject(list, 0), IsNull());
	EXPECT_THAT(List_getNumofObjects(list), Eq(0));
}

// --------------------------------------------------------
TEST_P(List_test, remove_the_front)
{
	ASSERT_TRUE(List_insert(list, &object1, 0));
	ASSERT_TRUE(List_insert(list, &object2, 1));
	ASSERT_THAT(List_remove(list, 0), Eq(&object1));

	EXPECT_THAT(List_getObject(list, 0), Eq(&object2));
	EXPECT_THAT(List_getObject(list, 1), IsNull());
	EXPECT_THAT(List_getNumofObjects(list), Eq(1));
}

// --------------------------------------------------------
TEST_P(List_test, remove_the_back)
{
	ASSERT_TRUE(List_insert(list, &object1, 0));
	ASSERT_TRUE(List_insert(list, &object2, 1));
	ASSERT_THAT(List_remove(list, 1), Eq(&object2));

	EXPECT_THAT(List_getObject(list, 0), Eq(&object1));
	EXPECT_THAT(List_getObject(list, 1), IsNull());
	EXPECT_THAT(List_getNumofObjects(list), Eq(1));
}

// --------------------------------------------------------
TEST_P(List_test, remove_the_between)
{
	ASSERT_TRUE(List_insert(list, &object1, 0));
	ASSERT_TRUE(List_insert(list, &object2, 1));
	ASSERT_TRUE(List_insert(list, &object3, 2));
	ASSERT_THAT(List_remove(list, 1), Eq(&object2));

	EXPECT_THAT(List_getObject(list, 0), Eq(&object1));
	EXPECT_THAT(List_getObject(list, 1), Eq(&object3));
	EXPECT_THAT(List_getObject(list, 2), IsNull());
	EXPECT_THAT(List_getNumofObjects(list), Eq(2));
}

// --------------------------------------------------------
TEST_P(List_test, getObject)
{
	//List_getObject() is tested by insert/remove tests
	SUCCEED();
}

// --------------------------------------------------------
TEST_P(List_test, getNumofObjects)
{
	//List_getObject() is tested by insert/remove tests
	SUCCEED();
}

// --------------------------------------------------------
TEST_P(List_test, foreach_empty)
{
	ASSERT_THAT(List_getObject(list, 0), IsNull());

	void (*procedure)(void* object, void* arg) = [](void* object, void* arg)
	{
		(void)object; (void)arg;
		FAIL();
	};
	List_foreach(list, procedure, NULL);
}

// --------------------------------------------------------
TEST_P(List_test, foreach_one)
{
	ASSERT_TRUE(List_insert(list, &object1, 0));

	struct context
	{
		int index;
		int* objects[1];
	} cntxt =
	{
		0,
		{ &object1, },
	};
	void (*procedure)(void* object, void* arg) = [](void* object, void* arg)
	{
		struct context* c = (struct context*)arg;
		EXPECT_THAT(object, Eq(c->objects[c->index]));
		c->index++;
	};
	List_foreach(list, procedure, &cntxt);
	EXPECT_THAT(cntxt.index, Eq(1));
}

// --------------------------------------------------------
TEST_P(List_test, foreach_two)
{
	ASSERT_TRUE(List_insert(list, &object1, 0));
	ASSERT_TRUE(List_insert(list, &object2, 1));

	struct context
	{
		int index;
		int* objects[2];
	} cntxt =
	{
		0,
		{ &object1, &object2, },
	};
	void (*procedure)(void* object, void* arg) = [](void* object, void* arg)
	{
		struct context* c = (struct context*)arg;
		EXPECT_THAT(object, Eq(c->objects[c->index]));
		c->index++;
	};
	List_foreach(list, procedure, &cntxt);
	EXPECT_THAT(cntxt.index, Eq(2));
}

// --------------------------------------------------------
TEST_P(List_test, foreach_three)
{
	ASSERT_TRUE(List_insert(list, &object1, 0));
	ASSERT_TRUE(List_insert(list, &object2, 1));
	ASSERT_TRUE(List_insert(list, &object3, 2));

	struct context
	{
		int index;
		int* objects[3];
	} cntxt =
	{
		0,
		{ &object1, &object2, &object3, },
	};
	void (*procedure)(void* object, void* arg) = [](void* object, void* arg)
	{
		struct context* c = (struct context*)arg;
		EXPECT_THAT(object, Eq(c->objects[c->index]));
		c->index++;
	};
	List_foreach(list, procedure, &cntxt);
	EXPECT_THAT(cntxt.index, Eq(3));
}

// --------------------------------------------------------
TEST_P(List_test, out_of_boundary_0)
{
	EXPECT_FALSE(List_insert(list, &object1, 1));
	EXPECT_THAT(List_remove(list, 0), IsNull());
	EXPECT_THAT(List_getObject(list, 0), IsNull());
}

// --------------------------------------------------------
TEST_P(List_test, out_of_boundary_1)
{
	ASSERT_TRUE(List_insert(list, &object1, 0));

	EXPECT_FALSE(List_insert(list, &object2, 2));
	EXPECT_THAT(List_remove(list, 1), IsNull());
	EXPECT_THAT(List_getObject(list, 1), IsNull());
}

// --------------------------------------------------------
TEST_P(List_test, out_of_boundary_2)
{
	ASSERT_TRUE(List_insert(list, &object1, 0));
	ASSERT_TRUE(List_insert(list, &object2, 1));

	EXPECT_FALSE(List_insert(list, &object3, 3));
	EXPECT_THAT(List_remove(list, 2), IsNull());
	EXPECT_THAT(List_getObject(list, 2), IsNull());
}

// --------------------------------------------------------
TEST_P(List_test, out_of_boundary_3)
{
	ASSERT_TRUE(List_insert(list, &object1, 0));
	ASSERT_TRUE(List_insert(list, &object2, 1));
	ASSERT_TRUE(List_insert(list, &object3, 2));

	EXPECT_FALSE(List_insert(list, &object4, 4));
	EXPECT_THAT(List_remove(list, 3), IsNull());
	EXPECT_THAT(List_getObject(list, 3), IsNull());
}

// --------------------------------------------------------
INSTANTIATE_TEST_CASE_P(
	parameterized_instance,
	List_test,
	//testing::Values(1, 2, 3, 10)
	testing::Values(ListFactory_createBidirectionalList())
);

