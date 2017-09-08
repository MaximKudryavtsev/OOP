#include "stdafx.h"
#include "../CMyStack/MyStack.h"

BOOST_AUTO_TEST_SUITE(CMyStack_)

	struct StackOfInt
	{
		CMyStack<int> stack;
	};
	BOOST_FIXTURE_TEST_SUITE(of_integer, StackOfInt)

		BOOST_AUTO_TEST_CASE(is_empty_by_default)
		{
			BOOST_CHECK(stack.IsEmpty());
		}

		BOOST_AUTO_TEST_CASE(should_be_constructed_from_other_stack)
		{
			stack.Push(1);
			stack.Push(2);
			CMyStack<int> stack2(stack);
			BOOST_CHECK_EQUAL(stack2.GetElement(), stack.GetElement());
		}

		BOOST_AUTO_TEST_CASE(first_stack_is_independent_of_its_copies)
		{
			stack.Push(1);
			stack.Push(2);
			CMyStack<int> stack2(stack);
			stack2.Pop();
			BOOST_CHECK_EQUAL(stack2.GetElement(), 1);
			BOOST_CHECK_EQUAL(stack.GetElement(), 2);
		}

		BOOST_AUTO_TEST_CASE(should_be_moved)
		{
			stack.Push(1);
			stack.Push(2);
			CMyStack<int> stack2 = std::move(stack);
			BOOST_CHECK(stack.IsEmpty());
			BOOST_CHECK_EQUAL(stack2.GetElement(), 2);
		}

		BOOST_AUTO_TEST_CASE(should_be_assigned)
		{
			stack.Push(1);
			stack.Push(2);
			CMyStack<int> stack2;
			stack2 = stack;
			BOOST_CHECK_EQUAL(stack2.GetElement(), stack.GetElement());
			stack2.Pop();
			BOOST_CHECK(stack2.GetElement() != stack.GetElement());
		}

		BOOST_AUTO_TEST_CASE(should_be_assigned_with_move)
		{
			CMyStack<int> oldStack;
			oldStack.Push(1);
			oldStack.Push(2);
			oldStack.Push(3);
			CMyStack<int> stack2;
			stack2 = CMyStack<int>(oldStack);
			BOOST_CHECK_EQUAL(stack2.GetElement(), oldStack.GetElement());
		}

		BOOST_AUTO_TEST_SUITE(throw_exception_if)

			BOOST_AUTO_TEST_CASE(Pop_from_empty_stack)
			{
				BOOST_REQUIRE_THROW(stack.Pop(), std::logic_error);
			}
			BOOST_AUTO_TEST_CASE(GetElement_from_empty_stack)
			{
				BOOST_REQUIRE_THROW(stack.GetElement(), std::logic_error);
			}

		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_CASE(should_add_element)
		{
			stack.Push(10);
			BOOST_CHECK(!stack.IsEmpty());
			BOOST_CHECK_EQUAL(stack.GetElement(), 10);
		}

		struct WithElements : StackOfInt
		{
			WithElements()
			{
				stack.Push(10);
				stack.Push(20);
				stack.Push(30);
				stack.Push(40);
				stack.Push(50);
			}
		};
		BOOST_FIXTURE_TEST_SUITE(with_elements, WithElements)

			BOOST_AUTO_TEST_CASE(should_contain_any_elements)
			{

				BOOST_CHECK(!stack.IsEmpty());
			}

			BOOST_AUTO_TEST_CASE(should_return_last_element)
			{
				BOOST_CHECK_EQUAL(stack.GetElement(), 50);
			}

			BOOST_AUTO_TEST_CASE(should_delete_last_element)
			{
				stack.Pop();
				BOOST_CHECK(!stack.IsEmpty());
				BOOST_CHECK_EQUAL(stack.GetElement(), 40);
			}

			BOOST_AUTO_TEST_CASE(should_be_cleaned)
			{
				stack.Clear();
				BOOST_CHECK(stack.IsEmpty());
			}

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

	struct StackOfString
	{
		CMyStack<std::string> stack;
	};
	BOOST_FIXTURE_TEST_SUITE(of_string, StackOfString)

		BOOST_AUTO_TEST_CASE(is_empty_by_default)
		{
			BOOST_CHECK(stack.IsEmpty());
		}

		BOOST_AUTO_TEST_CASE(should_be_constructed_from_other_stack)
		{
			stack.Push("abc");
			stack.Push("qwerty");
			CMyStack<std::string> stack2(stack);
			BOOST_CHECK_EQUAL(stack2.GetElement(), stack.GetElement());
		}

		BOOST_AUTO_TEST_CASE(first_stack_is_independent_of_its_copies)
		{
			stack.Push("abc");
			stack.Push("qwerty");
			CMyStack<std::string> stack2(stack);
			stack2.Pop();
			BOOST_CHECK_EQUAL(stack.GetElement(), "qwerty");
		}

		BOOST_AUTO_TEST_CASE(should_be_moved)
		{
			stack.Push("abc");
			stack.Push("qwerty");
			CMyStack<std::string> stack2 = std::move(stack);
			BOOST_CHECK(stack.IsEmpty());
			BOOST_CHECK_EQUAL(stack2.GetElement(), "qwerty");
		}

		BOOST_AUTO_TEST_CASE(should_be_assigned)
		{
			stack.Push("abc");
			stack.Push("qwerty");
			CMyStack<std::string> stack2;
			stack2 = stack;
			BOOST_CHECK_EQUAL(stack2.GetElement(), stack.GetElement());
			stack2.Pop();
			BOOST_CHECK_EQUAL(stack2.GetElement(), "abc");
		}

		BOOST_AUTO_TEST_CASE(should_be_assigned_with_move)
		{
			CMyStack<std::string> stack2;
			stack2 = CMyStack<std::string>();
			BOOST_CHECK(stack.IsEmpty());
		}

		BOOST_AUTO_TEST_SUITE(throw_exception_if)

			BOOST_AUTO_TEST_CASE(Pop_from_empty_stack)
			{
				BOOST_REQUIRE_THROW(stack.Pop(), std::logic_error);
			}

			BOOST_AUTO_TEST_CASE(GetElement_from_empty_stack)
			{
				BOOST_REQUIRE_THROW(stack.GetElement(), std::logic_error);
			}

		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_CASE(should_add_element)
		{
			stack.Push("abc");
			BOOST_CHECK(!stack.IsEmpty());
			BOOST_CHECK_EQUAL(stack.GetElement(), "abc");
		}

		struct WithElements : StackOfString
		{
			WithElements()
			{
				stack.Push("abc");
				stack.Push("");
				stack.Push("qwerty");
				stack.Push("q");
				stack.Push("my stack");
			}
		};

		BOOST_FIXTURE_TEST_SUITE(with_elements, WithElements)

			BOOST_AUTO_TEST_CASE(should_contain_any_elements)
			{
				BOOST_CHECK(!stack.IsEmpty());
			}

			BOOST_AUTO_TEST_CASE(should_return_last_element)
			{
				BOOST_CHECK_EQUAL(stack.GetElement(), "my stack");
			}

			BOOST_AUTO_TEST_CASE(should_delete_last_element)
			{
				stack.Pop();
				BOOST_CHECK(!stack.IsEmpty());
				BOOST_CHECK_EQUAL(stack.GetElement(), "q");
			}

			BOOST_AUTO_TEST_CASE(should_be_cleaned)
			{
				stack.Clear();
				BOOST_CHECK(stack.IsEmpty());
			}

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
