#include "stdafx.h"
#include "../FindMaxEx/FindMaxEx.h"

struct Athlete
{
	std::string name;
	double height;
	double weight;
};

bool IsHeightLess(const Athlete &left, const Athlete &right)
{
	return (left.height < right.height);
}

bool IsWeightLess(const Athlete &left, const Athlete &right)
{
	return (left.weight < right.weight);
}

bool AthletesAreEqual(const Athlete &left, const Athlete &right)
{
	return (left.name == right.name) && (left.height == right.height) && (left.weight == right.weight);
}

const Athlete Itachi = { "Itachi", 188.3, 105 };
const Athlete Kisame = { "Kisame", 188, 93 };
const Athlete Deidara = { "Deidara", 180, 95 };
const Athlete Tobi = { "Tobi", 178, 80 };
const Athlete Kakuzu = { "Kakuzu", 188.4, 90 };
const Athlete Hidan = { "Hidan", 185.7, 94 };

const std::vector<Athlete> athletes = { Itachi, Kisame, Deidara, Tobi, Kakuzu, Hidan };

BOOST_AUTO_TEST_SUITE(FindMaxEx_function)

BOOST_AUTO_TEST_CASE(returns_false_when_vector_is_empty)
{
	// int
	{
		std::vector<int> vect;
		int max = 0;
		BOOST_CHECK(!FindMaxEx(vect, max));
		BOOST_CHECK(max == 0);
	}

	// string
	{
		std::vector<std::string> vect;
		std::string max;
		BOOST_CHECK(!FindMaxEx(vect, max));
		BOOST_CHECK_EQUAL(max, "");
	}

	// custom type
	{
		std::vector<Athlete> vect;
		Athlete athlete = Tobi;
		BOOST_CHECK(!FindMaxEx(vect, athlete, IsHeightLess));
		BOOST_CHECK(!FindMaxEx(vect, athlete, IsWeightLess));
		BOOST_CHECK(AthletesAreEqual(athlete, Tobi));
	}
}

BOOST_AUTO_TEST_CASE(returns_true_when_correct_max_element_of_non_empty_vector_was_found)
{
	// int
	{
		std::vector<int> vect = { -27, 0, 0, 27, 28, 27, 28 };
		int max = 0;
		BOOST_CHECK(FindMaxEx(vect, max, [](int a, int b) {return a < b; }));
		BOOST_CHECK_EQUAL(max, 28);
	}

	// string
	{
		std::vector<std::string> vect = { "123", "space", "digit", "z", "xcx", "zxc" };
		std::string max;
		BOOST_CHECK(FindMaxEx(vect, max));
		BOOST_CHECK_EQUAL(max, "zxc");
	}

	// const char
	{
		std::vector<const char*> vect = { "123", "space", "digit", "z", "xcx", "zxc" };
		const char *str = "";

		auto IsConstCharLess = [](const char *a, const char *b)
		{
			return (strcmp(a, b) < 0);
		};

		BOOST_CHECK(FindMaxEx(vect, str, IsConstCharLess));
		BOOST_CHECK_EQUAL(str, "zxc");
	}

	// custom type
	{
		Athlete athlete = Tobi;

		// with max height (Kakuzu)
		BOOST_CHECK(FindMaxEx(athletes, athlete, IsHeightLess));
		BOOST_CHECK(AthletesAreEqual(athlete, Kakuzu));

		// with max weight (Itachi)
		BOOST_CHECK(FindMaxEx(athletes, athlete, IsWeightLess));
		BOOST_CHECK(AthletesAreEqual(athlete, Itachi));
	}
}

BOOST_AUTO_TEST_SUITE_END()