#include "stdafx.h"

#define _USE_MATH_DEFINES
#include "../Cone.h"
#include <math.h>

struct Cone_
{
    const double expectedRadius = 5.8;
    const double expectedHeight = 11.1;
    const double expectedDensity = 21.3;
    const double expectedVolume = M_PI * pow(expectedRadius, 2) * expectedHeight / 3;
    const CCone cone;
    Cone_()
        : cone(expectedDensity, expectedRadius, expectedHeight)
    {}
};

// Конус
BOOST_FIXTURE_TEST_SUITE(Cone, Cone_)
    // является объемным телом
    BOOST_AUTO_TEST_CASE(is_a_body)
    {
        BOOST_CHECK(static_cast<const CBody*>(&cone));
    }

    // имеет радиус
    BOOST_AUTO_TEST_CASE(has_a_base_radius)
    {
        BOOST_CHECK_EQUAL(cone.GetBaseRadius(), expectedRadius);
    }

    // имеет высоту
    BOOST_AUTO_TEST_CASE(has_a_height)
    {
        BOOST_CHECK_EQUAL(cone.GetHeight(), expectedHeight);
    }

    // имеет плотность
    BOOST_AUTO_TEST_CASE(has_a_density)
    {
        BOOST_CHECK_EQUAL(cone.GetDensity(), expectedDensity);
    }

    // имеет объем
    BOOST_AUTO_TEST_CASE(has_a_volume)
    {
        BOOST_CHECK_CLOSE_FRACTION(cone.GetVolume(), expectedVolume, 1e-7);
    }

    // имеет массу
    BOOST_AUTO_TEST_CASE(has_a_mass)
    {
        BOOST_CHECK_CLOSE_FRACTION(cone.GetMass(), expectedVolume * expectedDensity, 1e-7);
    }

    // имеет строковое представление
    BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
    {
        const auto expectedString = R"(Cone:
	density = 21.3
	volume = 391.0277544
	mass = 8328.891169
	base radius = 5.8
	height = 11.1
)";

        BOOST_CHECK_EQUAL(cone.ToString(), expectedString);
    }
BOOST_AUTO_TEST_SUITE_END()
