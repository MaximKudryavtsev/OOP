#include "stdafx.h"
#include "../equation.h"

template <typename Ex, typename Fn>
void ExpectException(Fn &&function, const std::string &expectedDescription)
{
    // Проверяем, что вызов function() выбросит исключение типа Ex 
	// с описанием, равным expectedDescription
	BOOST_CHECK_EXCEPTION(function(), Ex, [&](const Ex &error) {
		return error.what() == expectedDescription; 
    });

    try
    {
        function(); // Выполняем действие, от которого ожидаем выброс исключения
              // Если не выбросило, то тест провалился
        BOOST_ERROR("No exception thrown");
    }
    catch (const Ex &error) // Ловим исключение типа Ex (или его подкласс)
    {
        // Проверяем, что исключение будет иметь ожидаемое сообщение
        BOOST_CHECK_EQUAL(expectedDescription, error.what());
    }
    catch (...)
    {
        // Если выбросили иное исключение, то это также ошибка
        BOOST_ERROR("Unexpected exception");
    }
}

BOOST_AUTO_TEST_SUITE(Solve2_function)
    BOOST_AUTO_TEST_CASE(throws_an_exception_when_first_coefficient_of_quadratic_equation_equals_to_zero)
    {
        ExpectException<std::invalid_argument>([]{
            EquationRoot4 roots = Solve2(0, 1, -1);
        }, "\"a\" coefficient can't be zero");
        BOOST_REQUIRE_NO_THROW(Solve2(1, 0, 0));
        BOOST_REQUIRE_NO_THROW(Solve2(-1, 0, 0));
        BOOST_REQUIRE_NO_THROW(Solve2(0.1, 0, 0));
        BOOST_REQUIRE_NO_THROW(Solve2(-0.1, 0, 0));
    }

    BOOST_AUTO_TEST_CASE(returns_one_correct_real_root_when_equation_have_only_one_real_solution)
    {
        EquationRoot4 roots;
        BOOST_REQUIRE_NO_THROW(roots = Solve2(1, -6, 9));
        BOOST_CHECK_EQUAL(roots.numRoots, 2);
        BOOST_CHECK_EQUAL(roots.root[0], 3);
        BOOST_CHECK_EQUAL(roots.root[1], 3);
    }

    BOOST_AUTO_TEST_CASE(returns_two_correct_real_roots_when_equation_have_two_real_solutions)
    {
        EquationRoot4 roots;
        BOOST_REQUIRE_NO_THROW(roots = Solve2(1, -1, -1));
        BOOST_CHECK_EQUAL(roots.numRoots, 2);
        BOOST_CHECK_EQUAL(roots.root[0], (1 + sqrt(5)) / (2 * 1));
        BOOST_CHECK_EQUAL(roots.root[1], (1 - sqrt(5)) / (2 * 1));
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Solve3_function)
    BOOST_AUTO_TEST_CASE(throws_an_exception_when_first_coefficient_of_cubic_equation_equals_to_zero)
    {
        ExpectException<std::invalid_argument>([] {
            EquationRoot4 roots = Solve3(0, 1, -1, 0);
        }, "\"a\" coefficient can't be zero");
        BOOST_REQUIRE_NO_THROW(Solve3(1, 0, 0, 0));
        BOOST_REQUIRE_NO_THROW(Solve3(-1, 0, 0, 0));
        BOOST_REQUIRE_NO_THROW(Solve3(0.1, 0, 0, 0));
        BOOST_REQUIRE_NO_THROW(Solve3(-0.1, 0, 0, 0));
    }

    BOOST_AUTO_TEST_CASE(returns_one_correct_real_root_when_equation_have_only_one_real_solution)
    {
        EquationRoot4 roots = Solve3(1, 1, 1, 1);
        BOOST_CHECK_EQUAL(roots.numRoots, 1);
        BOOST_CHECK_EQUAL(roots.root[0], -1);

        roots = Solve3(2, -4, 2, -1);
        BOOST_CHECK_EQUAL(roots.numRoots, 1);
        BOOST_CHECK_CLOSE_FRACTION(roots.root[0], 1.57, 0.1);

        roots = Solve3(1, 0, 1, 0);
        BOOST_CHECK_EQUAL(roots.numRoots, 1);
        BOOST_CHECK_CLOSE_FRACTION(roots.root[0], 0, 0.01);
    }

    BOOST_AUTO_TEST_CASE(returns_two_correct_real_roots_when_equation_have_two_real_solutions)
    {
        EquationRoot4 roots = Solve3(1, 0, 0, 0);
        BOOST_CHECK_EQUAL(roots.numRoots, 2);
        BOOST_CHECK_EQUAL(roots.root[0], 0);
        BOOST_CHECK_EQUAL(roots.root[1], 0);

        roots = Solve3(1, 1, 0, 0);
        BOOST_CHECK_EQUAL(roots.numRoots, 2);
        BOOST_CHECK_CLOSE_FRACTION(roots.root[0], -1, 0.1);
        BOOST_CHECK_CLOSE_FRACTION(roots.root[1], 0.0036, 0.1);
    }

    BOOST_AUTO_TEST_CASE(returns_three_correct_real_roots_when_equation_have_three_real_solutions)
    {
        EquationRoot4 roots = Solve3(1, -6, 1, 1);
        BOOST_CHECK_EQUAL(roots.numRoots, 3);
        
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Solve4_function)
    BOOST_AUTO_TEST_CASE(throws_an_exception_when_first_coefficient_of_equation4_equals_to_zero)
    {
        ExpectException<std::invalid_argument>([] {
            EquationRoot4 roots = Solve4(0, 1, -1, 0, 1);
        }, "\"a\" coefficient can't be zero");
        BOOST_REQUIRE_NO_THROW(Solve4(1, 0, 0, 0, 0));
        BOOST_REQUIRE_NO_THROW(Solve4(-1, 0, 0, 0, 0));
        BOOST_REQUIRE_NO_THROW(Solve4(0.1, 0, 0, 0, 0));
        BOOST_REQUIRE_NO_THROW(Solve4(-0.1, 0, 0, 0, 0));
    }

    BOOST_AUTO_TEST_CASE(throws_an_exception_when_equation4_have_no_real_roots)
    {
        ExpectException<std::domain_error>([] {
            EquationRoot4 roots = Solve4(11, 5, 9, 6, 4);
        }, "Equation does not have any real roots");
    }

    BOOST_AUTO_TEST_CASE(returns_two_correct_real_roots_when_equation_have_two_real_solutions)
    {
        EquationRoot4 roots = Solve4(-5, 2, 0, 0, 1);
        BOOST_CHECK_EQUAL(roots.numRoots, 2);
        BOOST_CHECK_CLOSE_FRACTION(roots.root[0], 0.796, 0.01);
        BOOST_CHECK_CLOSE_FRACTION(roots.root[1], -0.587, 0.01);

        roots = Solve4(3, -5, 2, 2, 0);
        BOOST_CHECK_EQUAL(roots.numRoots, 2);
        BOOST_CHECK_CLOSE_FRACTION(roots.root[0], 0, 0.01);
        BOOST_CHECK_CLOSE_FRACTION(roots.root[1], -0.427, 0.01);
    }

    BOOST_AUTO_TEST_CASE(returns_four_correct_real_roots_when_equation_have_four_real_solutions)
    {
        EquationRoot4 roots = Solve4(2, 0, 0, 0, 0);
        BOOST_CHECK_EQUAL(roots.numRoots, 4);
        BOOST_CHECK_CLOSE_FRACTION(roots.root[0], 0, 0.01);
        BOOST_CHECK_CLOSE_FRACTION(roots.root[1], 0, 0.01);
        BOOST_CHECK_CLOSE_FRACTION(roots.root[2], 0, 0.01);
        BOOST_CHECK_CLOSE_FRACTION(roots.root[3], 0, 0.01);

        roots = Solve4(-5, -10, 5, 3, -1);
        BOOST_CHECK_EQUAL(roots.numRoots, 4);
        BOOST_CHECK_CLOSE_FRACTION(roots.root[0], -0.542, 0.01);
        BOOST_CHECK_CLOSE_FRACTION(roots.root[1], -2.305, 0.01);
        BOOST_CHECK_CLOSE_FRACTION(roots.root[2], 0.560, 0.01);
        BOOST_CHECK_CLOSE_FRACTION(roots.root[3], 0.286, 0.01);
    }
BOOST_AUTO_TEST_SUITE_END()
