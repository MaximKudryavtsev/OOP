#include "stdafx.h"
#include "../StringStack.h"

struct EmptyStack
{
    CStringStack stack;
};

class CMockString
    : public std::string
{
public:
    CMockString(std::string const& str)
    : std::string(str)
    {}

    template <typename T>
    T& operator=(T const& val)
    {
        throw std::exception("cannot assign this object");
    }
};

BOOST_FIXTURE_TEST_SUITE(String_stack, EmptyStack)
    BOOST_AUTO_TEST_SUITE(when_created)
        BOOST_AUTO_TEST_CASE(is_empty)
        {
            BOOST_CHECK_EQUAL(stack.GetSize(), 0u);
        }

        BOOST_AUTO_TEST_CASE(pop_method_throws_an_exception_because_stack_is_empty)
        {
            BOOST_REQUIRE_THROW(stack.Pop(), std::domain_error);
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(after_string_push)
        BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
        {
            size_t oldSize = stack.GetSize();
            stack.Push("Hello");
            BOOST_CHECK_EQUAL(stack.GetSize(), oldSize + 1);
            stack.Push("World");
            BOOST_CHECK_EQUAL(stack.GetSize(), oldSize + 2);

            CMockString str("hello");

            std::string* arg = &str;
            stack.Push(*arg);
        }

        BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetBackElement_method)
        {
            stack.Push("hello");
            BOOST_CHECK_EQUAL(stack.GetLastElement(), "hello");
            stack.Push("goodbye");
            BOOST_CHECK_EQUAL(stack.GetLastElement(), "goodbye");
        }

        BOOST_AUTO_TEST_CASE(string_can_be_popped)
        {
            size_t oldSize = stack.GetSize();
            stack.Push("string");
            BOOST_CHECK_EQUAL(stack.GetSize(), oldSize + 1);
            stack.Pop();
            BOOST_CHECK_EQUAL(stack.GetSize(), oldSize);
        }
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
