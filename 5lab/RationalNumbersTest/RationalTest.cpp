#include "stdafx.h"
#include "../RationalNumbers/Rational.h"

BOOST_AUTO_TEST_CASE(GCD_tests)
{
	BOOST_CHECK_EQUAL(GCD(4, 5), 1u);
	BOOST_CHECK_EQUAL(GCD(5, 4), 1u);
	BOOST_CHECK_EQUAL(GCD(0, 0), 1u);
	BOOST_CHECK_EQUAL(GCD(0, 3), 3u);
	BOOST_CHECK_EQUAL(GCD(3, 0), 3u);
	BOOST_CHECK_EQUAL(GCD(12, 8), 4u);
	BOOST_CHECK_EQUAL(GCD(8, 12), 4u);
}

void VerifyRational(const CRational &rationalNumber, const int expectedNumerator, const int expectedDenominator)
{
	BOOST_CHECK_EQUAL(rationalNumber.GetNumerator(), expectedNumerator);
	BOOST_CHECK_EQUAL(rationalNumber.GetDenominator(), expectedDenominator);
}

BOOST_AUTO_TEST_SUITE(Rational_number)

BOOST_AUTO_TEST_CASE(equals_to_zero_by_default)
{
	VerifyRational(CRational(), 0, 1);
}

BOOST_AUTO_TEST_CASE(should_be_constructed_by_one_integer_value)
{
	VerifyRational(CRational(10), 10, 1);
	VerifyRational(CRational(-10), -10, 1);
	VerifyRational(CRational(0), 0, 1);
}

BOOST_AUTO_TEST_CASE(should_be_constructed_with_numerator_and_denominator)
{
	VerifyRational(CRational(5, 2), 5, 2);
	VerifyRational(CRational(-5, 2), -5, 2);
	VerifyRational(CRational(5, -2), -5, 2);
	VerifyRational(CRational(-5, -2), 5, 2);
}

BOOST_AUTO_TEST_CASE(should_be_normalized_after_construction)
{
	VerifyRational(CRational(6, 8), 3, 4);
	VerifyRational(CRational(10, 5), 2, 1);
	VerifyRational(CRational(6, -8), -3, 4);
	VerifyRational(CRational(-6, 8), -3, 4);
	VerifyRational(CRational(-6, -8), 3, 4);
	VerifyRational(CRational(-10, 20), -1, 2);
}

BOOST_AUTO_TEST_CASE(shouldnot_have_denominator_that_equals_to_zero)
{
	BOOST_REQUIRE_THROW(CRational(1, 0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(should_be_printed)
{
	CRational number(3, 2);
	std::stringstream strm;
	strm << number << " " << CRational(-1, 3);
	BOOST_CHECK_EQUAL(strm.str(), "3/2 -1/3");
}

BOOST_AUTO_TEST_CASE(should_be_read)
{
	CRational number;
	std::stringstream strm("1/2");
	strm >> number;
	VerifyRational(number, 1, 2);
}

BOOST_AUTO_TEST_CASE(should_be_converted_into_double)
{
	BOOST_CHECK_CLOSE_FRACTION(CRational().ToDouble(), 0.0, DBL_EPSILON);
	BOOST_CHECK_CLOSE_FRACTION(CRational(1).ToDouble(), 1.0, DBL_EPSILON);
	BOOST_CHECK_CLOSE_FRACTION(CRational(-1).ToDouble(), -1.0, DBL_EPSILON);
	BOOST_CHECK_CLOSE_FRACTION(CRational(8, 10).ToDouble(), 0.8, DBL_EPSILON);
	BOOST_CHECK_CLOSE_FRACTION(CRational(-8, 10).ToDouble(), -0.8, DBL_EPSILON);
	BOOST_CHECK_CLOSE_FRACTION(CRational(8, -10).ToDouble(), -0.8, DBL_EPSILON);
	BOOST_CHECK_CLOSE_FRACTION(CRational(-8, -10).ToDouble(), 0.8, DBL_EPSILON);
}

BOOST_AUTO_TEST_CASE(should_be_converted_into_compound_fraction)
{
	BOOST_CHECK_EQUAL(CRational(4, 3).ToCompoundFraction().first, 1);
	BOOST_CHECK_EQUAL(CRational(4, 3).ToCompoundFraction().second, CRational(1, 3));

	BOOST_CHECK_EQUAL(CRational(-1, 4).ToCompoundFraction().first, 0);
	BOOST_CHECK_EQUAL(CRational(-1, 4).ToCompoundFraction().second, CRational(-1, 4));

	BOOST_CHECK_EQUAL(CRational(-5, 4).ToCompoundFraction().first, -1);
	BOOST_CHECK_EQUAL(CRational(-5, 4).ToCompoundFraction().second, CRational(-1, 4));

	BOOST_CHECK_EQUAL(CRational(25, 4).ToCompoundFraction().first, 6);
	BOOST_CHECK_EQUAL(CRational(25, 4).ToCompoundFraction().second, CRational(1, 4));
}

BOOST_AUTO_TEST_CASE(unary_plus_returns_same_number)
{
	VerifyRational(+CRational(), 0, 1);
	VerifyRational(+CRational(1), 1, 1);
	VerifyRational(+CRational(5, 8), 5, 8);
	VerifyRational(+CRational(-5, 8), -5, 8);
	VerifyRational(+CRational(-5, -8), 5, 8);
}

BOOST_AUTO_TEST_CASE(unary_minus_returns_same_number_with_opposite_sign)
{
	VerifyRational(-CRational(), 0, 1);
	VerifyRational(-CRational(1), -1, 1);
	VerifyRational(-CRational(5, 8), -5, 8);
	VerifyRational(-CRational(-5, 8), 5, 8);
	VerifyRational(-CRational(-5, -8), -5, 8);
}

BOOST_AUTO_TEST_SUITE(binary_plus_should_return_sum_of)

BOOST_AUTO_TEST_CASE(two_rational_numbers)
{
	{
		CRational leftValue(1, 4);
		CRational rightValue(3, 4);
		CRational result = leftValue + rightValue;
		VerifyRational(result, 1, 1);
	}

	{
		CRational leftValue(1, -4);
		CRational rightValue(3, 4);
		CRational result = leftValue + rightValue;
		VerifyRational(result, 1, 2);
	}

	{
		CRational leftValue(1, -4);
		CRational rightValue(-3, 4);
		CRational result = leftValue + rightValue;
		VerifyRational(result, -1, 1);
	}
}

BOOST_AUTO_TEST_CASE(rational_number_and_integer)
{
	{
		CRational someRational(1, 2);
		CRational result = someRational + 2;
		VerifyRational(result, 5, 2);
	}

	{
		CRational someRational(-1, 2);
		CRational result = someRational + 1;
		VerifyRational(result, 1, 2);
	}
}

BOOST_AUTO_TEST_CASE(integer_and_rational_number)
{
	{
		CRational someRational(3, 2);
		CRational result = -2 + someRational;
		VerifyRational(result, -1, 2);
	}

	{
		CRational someRational(-4, 2);
		CRational result = 1 + someRational;
		VerifyRational(result, -1, 1);
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(binary_minus_should_return_difference_between)

BOOST_AUTO_TEST_CASE(two_rational_numbers)
{
	{
		CRational leftValue(1, 4);
		CRational rightValue(3, 4);
		CRational result = leftValue - rightValue;
		VerifyRational(result, -1, 2);
	}

	{
		CRational leftValue(1, -4);
		CRational rightValue(3, 4);
		CRational result = leftValue - rightValue;
		VerifyRational(result, -1, 1);
	}

	{
		CRational leftValue(1, -4);
		CRational rightValue(-3, 4);
		CRational result = leftValue - rightValue;
		VerifyRational(result, 1, 2);
	}
}

BOOST_AUTO_TEST_CASE(rational_number_and_integer)
{
	{
		CRational someRational(1, 2);
		CRational result = someRational - 2;
		VerifyRational(result, -3, 2);
	}

	{
		CRational someRational(-1, 2);
		CRational result = someRational - 1;
		VerifyRational(result, -3, 2);
	}
}

BOOST_AUTO_TEST_CASE(integer_and_rational_number)
{
	{
		CRational someRational(3, 2);
		CRational result = -2 - someRational;
		VerifyRational(result, -7, 2);
	}

	{
		CRational someRational(-4, 2);
		CRational result = 1 - someRational;
		VerifyRational(result, 3, 1);
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(should_multiply)

BOOST_AUTO_TEST_CASE(two_rational_numbers)
{
	{
		CRational leftValue(1, 4);
		CRational rightValue(3, 4);
		CRational result = leftValue * rightValue;
		VerifyRational(result, 3, 16);
	}

	{
		CRational leftValue(1, -4);
		CRational rightValue(3, 4);
		CRational result = leftValue * rightValue;
		VerifyRational(result, -3, 16);
	}

	{
		CRational leftValue(1, -4);
		CRational rightValue(-3, 4);
		CRational result = leftValue * rightValue;
		VerifyRational(result, 3, 16);
	}
}

BOOST_AUTO_TEST_CASE(rational_number_and_integer)
{
	{
		CRational someRational(1, 2);
		CRational result = someRational * 2;
		VerifyRational(result, 1, 1);
	}

	{
		CRational someRational(-1, 2);
		CRational result = someRational * 1;
		VerifyRational(result, -1, 2);
	}
}

BOOST_AUTO_TEST_CASE(integer_and_rational_number)
{
	{
		CRational someRational(3, 2);
		CRational result = -2 * someRational;
		VerifyRational(result, -3, 1);
	}

	{
		CRational someRational(-4, 2);
		CRational result = 1 * someRational;
		VerifyRational(result, -2, 1);
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(should_divide)

BOOST_AUTO_TEST_CASE(two_rational_numbers)
{
	{
		CRational leftValue(1, 4);
		CRational rightValue(3, 4);
		CRational result = leftValue / rightValue;
		VerifyRational(result, 1, 3);
	}

	{
		CRational leftValue(1, -4);
		CRational rightValue(3, 4);
		CRational result = leftValue * rightValue;
		VerifyRational(result, -3, 16);
	}

	{
		CRational leftValue(1, -4);
		CRational rightValue(-3, 4);
		CRational result = leftValue * rightValue;
		VerifyRational(result, 3, 16);
	}
}

BOOST_AUTO_TEST_CASE(rational_number_and_integer)
{
	{
		CRational someRational(1, 2);
		CRational result = someRational / 2;
		VerifyRational(result, 1, 4);
	}

	{
		CRational someRational(-1, 2);
		CRational result = someRational / 1;
		VerifyRational(result, -1, 2);
	}
}

BOOST_AUTO_TEST_CASE(integer_and_rational_number)
{
	{
		CRational someRational(3, 2);
		CRational result = -2 / someRational;
		VerifyRational(result, -4, 3);
	}

	{
		CRational someRational(-4, 2);
		CRational result = 1 / someRational;
		VerifyRational(result, -1, 2);
	}
}

BOOST_AUTO_TEST_CASE(and_handle_division_on_zero)
{
	BOOST_REQUIRE_THROW(CRational(1, 2) / 0, std::invalid_argument);
	BOOST_REQUIRE_THROW(CRational(3, 4) / CRational(), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(should_increase_by_addition)

BOOST_AUTO_TEST_CASE(with_another_rational_number)
{
	{
		CRational someRational(1, 2);
		someRational += CRational(3, 2);
		VerifyRational(someRational, 2, 1);
	}

	{
		CRational someRational(1, 3);
		someRational += CRational();
		VerifyRational(someRational, 1, 3);
	}
}

BOOST_AUTO_TEST_CASE(with_some_integer_value)
{
	{
		CRational someRational(-3, 4);
		someRational += 1;
		VerifyRational(someRational, 1, 4);
	}

	{
		CRational someRational;
		someRational += 1;
		VerifyRational(someRational, 1, 1);
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(should_increase_by_multiplication)

BOOST_AUTO_TEST_CASE(with_another_rational_number)
{
	{
		CRational someRational(1, 2);
		someRational *= CRational(3, 2);
		VerifyRational(someRational, 3, 4);
	}

	{
		CRational someRational(1, 3);
		someRational *= CRational();
		VerifyRational(someRational, 0, 1);
	}
}

BOOST_AUTO_TEST_CASE(with_some_integer_value)
{
	{
		CRational someRational(-3, 4);
		someRational *= -1;
		VerifyRational(someRational, 3, 4);
	}

	{
		CRational someRational;
		someRational *= 1;
		VerifyRational(someRational, 0, 1);
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(should_decrease_by_subtraction)

BOOST_AUTO_TEST_CASE(with_another_rational_number)
{
	{
		CRational someRational(1, 2);
		someRational -= CRational(3, 2);
		VerifyRational(someRational, -1, 1);
	}

	{
		CRational someRational(1, 3);
		someRational -= CRational();
		VerifyRational(someRational, 1, 3);
	}
}

BOOST_AUTO_TEST_CASE(with_some_integer_value)
{
	{
		CRational someRational(-3, 4);
		someRational -= -1;
		VerifyRational(someRational, 1, 4);
	}

	{
		CRational someRational;
		someRational -= 1;
		VerifyRational(someRational, -1, 1);
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(should_decrease_by_division)

BOOST_AUTO_TEST_CASE(with_another_rational_number)
{
	{
		CRational someRational(1, 2);
		someRational /= CRational(3, 2);
		VerifyRational(someRational, 1, 3);
	}

	{
		CRational someRational(1, 3);
		someRational /= CRational(-1, 1);
		VerifyRational(someRational, -1, 3);
	}
}

BOOST_AUTO_TEST_CASE(with_some_integer_value)
{
	{
		CRational someRational(-3, 4);
		someRational /= -1;
		VerifyRational(someRational, 3, 4);
	}

	{
		CRational someRational;
		someRational /= 1;
		VerifyRational(someRational, 0, 1);
	}
}

BOOST_AUTO_TEST_CASE(and_handle_division_on_zero)
{
	CRational someRational(1, 2);
	CRational zeroRational;
	BOOST_REQUIRE_THROW(someRational /= zeroRational, std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(should_be_compared_on_equality_of)

BOOST_AUTO_TEST_CASE(two_rational_numbers)
{
	BOOST_CHECK(!(CRational() == CRational(1)));
	BOOST_CHECK(!(CRational(1, 1) == CRational(1, -1)));
	BOOST_CHECK(!(CRational(-5, 4) == CRational(1, 4)));

	BOOST_CHECK(CRational(1, 2) == CRational(2, 4));
	BOOST_CHECK(CRational() == CRational(0, 1));
	BOOST_CHECK(CRational(-1, 2) == CRational(4, -8));
}

BOOST_AUTO_TEST_CASE(rational_and_integer)
{
	BOOST_CHECK(!(CRational() == 1));
	BOOST_CHECK(!(CRational(1, 1) == -1));
	BOOST_CHECK(!(CRational(-5, 4) == -5));

	BOOST_CHECK(CRational() == 0);
	BOOST_CHECK(CRational(3, 3) == 1);
	BOOST_CHECK(CRational(-4, 2) == -2);
}

BOOST_AUTO_TEST_CASE(integer_and_rational)
{
	BOOST_CHECK(!(1 == CRational()));
	BOOST_CHECK(!(1 == CRational(1, -1)));
	BOOST_CHECK(!(-5 == CRational(1, 4)));

	BOOST_CHECK(0 == CRational());
	BOOST_CHECK(1 == CRational(5, 5));
	BOOST_CHECK(-1 == CRational(-3, 3));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(should_be_compared_on_inequality_of)

BOOST_AUTO_TEST_CASE(two_rational_numbers)
{
	BOOST_CHECK(!(CRational() != CRational(0)));
	BOOST_CHECK(!(CRational(1, 1) != CRational(1, 1)));
	BOOST_CHECK(!(CRational(-5, 4) != CRational(-5, 4)));

	BOOST_CHECK(CRational(1, 3) != CRational(2, 4));
	BOOST_CHECK(CRational() != CRational(1, 1));
	BOOST_CHECK(CRational(-1, 2) != CRational(-4, -8));
}

BOOST_AUTO_TEST_CASE(rational_and_integer)
{
	BOOST_CHECK(!(CRational() != 0));
	BOOST_CHECK(!(CRational(1, 1) != 1));
	BOOST_CHECK(!(CRational(-2, 1) != -2));

	BOOST_CHECK(CRational(1, 12) != 0);
	BOOST_CHECK(CRational(3, 4) != 1);
	BOOST_CHECK(CRational(-4, 3) != -2);
}

BOOST_AUTO_TEST_CASE(integer_and_rational)
{
	BOOST_CHECK(!(0 != CRational(0)));
	BOOST_CHECK(!(1 != CRational(1, 1)));
	BOOST_CHECK(!(-2 != CRational(-2, 1)));

	BOOST_CHECK(0 != CRational(1, 3));
	BOOST_CHECK(1 != CRational(5, 2));
	BOOST_CHECK(-1 != CRational(-3, -3));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(should_be_greater_than)

BOOST_AUTO_TEST_CASE(another_rational_number)
{
	BOOST_CHECK(!(CRational(-1, 2) > CRational(0)));
	BOOST_CHECK(!(CRational() > CRational(1)));

	BOOST_CHECK(CRational(1, 2) > CRational(0, 1));
	BOOST_CHECK(CRational(-2, 1) > CRational(-8, 2));
}

BOOST_AUTO_TEST_CASE(some_integer_value)
{
	BOOST_CHECK(!(CRational(-1, 2) > 0));
	BOOST_CHECK(!(CRational() > 1));

	BOOST_CHECK(CRational(4, 2) > 1);
	BOOST_CHECK(CRational(-10, 1) > -11);
	BOOST_CHECK(CRational() > -1);

	BOOST_CHECK(!(1 > CRational(2)));
	BOOST_CHECK(!(-2 > CRational()));

	BOOST_CHECK(1 > CRational());
	BOOST_CHECK(-10 > CRational(-110, 1));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(should_be_less_or_equal_to)

BOOST_AUTO_TEST_CASE(another_rational_number)
{
	BOOST_CHECK(!(CRational() <= CRational(-1, 2)));
	BOOST_CHECK(!(CRational(1) <= CRational(1, 2)));

	BOOST_CHECK(CRational(0, 1) <= CRational(1, 1));
	BOOST_CHECK(CRational(-2, 1) <= CRational());
}

BOOST_AUTO_TEST_CASE(some_integer_value)
{
	BOOST_CHECK(!(CRational() <= -1));
	BOOST_CHECK(!(CRational(1) <= 0));

	BOOST_CHECK(CRational() <= 1);
	BOOST_CHECK(CRational(-10, 1) <= -10);
	BOOST_CHECK(CRational() <= 0);

	BOOST_CHECK(!(1 <= CRational()));
	BOOST_CHECK(!(-2 <= CRational(-10, 2)));

	BOOST_CHECK(1 <= CRational(1));
	BOOST_CHECK(10 <= CRational(110, 1));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(should_be_less_than)

BOOST_AUTO_TEST_CASE(another_rational_number)
{
	BOOST_CHECK(!(CRational() < CRational(-1, 2)));
	BOOST_CHECK(!(CRational(1) < CRational(-1, 1)));

	BOOST_CHECK(CRational(0, 1) < CRational(1, 1));
	BOOST_CHECK(CRational(-2, 1) < CRational());
}

BOOST_AUTO_TEST_CASE(some_integer_value)
{
	BOOST_CHECK(!(CRational() < -1));
	BOOST_CHECK(!(CRational(-1, 1) < -2));

	BOOST_CHECK(CRational() < 1);
	BOOST_CHECK(CRational(-10, 1) < -9);
	BOOST_CHECK(CRational(-2) < -1);

	BOOST_CHECK(!(-1 < CRational(-2)));
	BOOST_CHECK(!(-2 < CRational(-5, 2)));

	BOOST_CHECK(1 < CRational(2));
	BOOST_CHECK(10 < CRational(110, 1));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(should_be_greater_or_equal_to)

BOOST_AUTO_TEST_CASE(another_rational_number)
{
	BOOST_CHECK(!(CRational() >= CRational(1, 2)));
	BOOST_CHECK(!(CRational(1) >= CRational(2, 1)));

	BOOST_CHECK(CRational(1, 1) >= CRational(1, 1));
	BOOST_CHECK(CRational(-2, 1) >= CRational(-3));
}

BOOST_AUTO_TEST_CASE(some_integer_value)
{
	BOOST_CHECK(!(CRational() >= 1));
	BOOST_CHECK(!(CRational(-2) >= 1));

	BOOST_CHECK(CRational(2) >= 1);
	BOOST_CHECK(CRational(-10, -1) >= -9);
	BOOST_CHECK(CRational() >= -1);

	BOOST_CHECK(!(-1 >= CRational()));
	BOOST_CHECK(!(-2 >= CRational(-1, 2)));

	BOOST_CHECK(1 >= CRational());
	BOOST_CHECK(10 >= CRational(-1, 1));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()