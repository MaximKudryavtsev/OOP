#include "stdafx.h"
#include "../PrimeNumbers/SetProcessor.h"

BOOST_AUTO_TEST_SUITE(Set_processor)

	BOOST_AUTO_TEST_CASE(empty_set)
	{
		std::set<int> emptySet = {};
		BOOST_CHECK(GeneratePrimeNumbersSet(0) == emptySet);
	}

	BOOST_AUTO_TEST_CASE(upper_bound_equally_10)
	{
		std::set<int> expectedSet = { 2, 3, 5, 7 };
		BOOST_CHECK(GeneratePrimeNumbersSet(10) == expectedSet);
	}

	BOOST_AUTO_TEST_CASE(upper_bound_equally_20)
	{
		std::set<int> expectedSet = { 2, 3, 5, 7, 11, 13, 17, 19 };
		BOOST_CHECK(GeneratePrimeNumbersSet(20) == expectedSet);
	}

BOOST_AUTO_TEST_SUITE_END()