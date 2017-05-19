#include "stdafx.h"
#include "..\vector\VectorProcessor.h"

using namespace std;

bool VectorsAreEqual(vector<double> const& x, vector<double> const& y)
{
    return x == y;
}

// Функция GetMinElement
BOOST_AUTO_TEST_SUITE(GetMinElement_function)

	BOOST_AUTO_TEST_CASE(get_min_element)
	{
		vector<double> Vector = {0, 1, 2, 3};
		GetMinElement(Vector);
		BOOST_CHECK(GetMinElement(Vector) == 0);
	}

	BOOST_AUTO_TEST_CASE(get_negative_min_element)
	{
		vector<double> Vector = {-1, 0, 1, 2, 3};
		GetMinElement(Vector);
		BOOST_CHECK(GetMinElement(Vector) == -1);
	}

BOOST_AUTO_TEST_SUITE_END()

// Функция GetMaxElement
BOOST_AUTO_TEST_SUITE(GetMaxElement_function)

BOOST_AUTO_TEST_CASE(get_max_element)
{
	vector<double> Vector = { 0, 1, 2, 3 };
	GetMaxElement(Vector);
	BOOST_CHECK(GetMaxElement(Vector) == 3);
}

BOOST_AUTO_TEST_CASE(get_max_element_from_negative_numbers)
{
	vector<double> Vector = { -10, -1, -2, -33 };
	GetMaxElement(Vector);
	BOOST_CHECK(GetMaxElement(Vector) == -1);
}

BOOST_AUTO_TEST_SUITE_END()


// Функция ProcessVector
BOOST_AUTO_TEST_SUITE(ProcessVector_function)
	//умнажает все элементы вектора на максимальный элемент и делит на минимальный элемент
	BOOST_AUTO_TEST_CASE(mult_all_elements_at_max_element_and_divide_at_min_element)
	{
		vector<double> Vector = {1, 2, 3, 4};
		ProcessVector(Vector);
		BOOST_CHECK(VectorsAreEqual(Vector, {4, 8, 12, 16}));
	}
	
	

BOOST_AUTO_TEST_SUITE_END()

