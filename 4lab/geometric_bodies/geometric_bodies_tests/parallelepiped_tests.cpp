#include "stdafx.h"

#define _USE_MATH_DEFINES
#include "../Parallelepiped.h"
#include <math.h>

struct Parallelepiped_
{
    const double expectedWidth = 30.2;
    const double expectedDepth = 23.8;
    const double expectedHeight = 21.9;
    const double expectedDensity = 8.8;
    const double expectedVolume = expectedWidth * expectedHeight * expectedDepth;
    const CParallelepiped parallelepiped;
    Parallelepiped_()
        : parallelepiped(expectedDensity, expectedWidth, expectedHeight, expectedDepth)
    {}
};

// Параллелепипед
BOOST_FIXTURE_TEST_SUITE(parallelepiped, Parallelepiped_)
    // является объёмным телом
    BOOST_AUTO_TEST_CASE(is_a_body)
    {
        BOOST_CHECK(static_cast<const CBody*>(&parallelepiped));
    }

    // имеет ширину
    BOOST_AUTO_TEST_CASE(has_a_width)
    {
        BOOST_CHECK_EQUAL(parallelepiped.GetWidth(), expectedWidth);
    }

    // имеет толщину
    BOOST_AUTO_TEST_CASE(has_a_depth)
    {
        BOOST_CHECK_EQUAL(parallelepiped.GetDepth(), expectedDepth);
    }

    // имеет высоту
    BOOST_AUTO_TEST_CASE(has_a_height)
    {
        BOOST_CHECK_EQUAL(parallelepiped.GetHeight(), expectedHeight);
    }

    // имеет плотность
    BOOST_AUTO_TEST_CASE(has_a_density)
    {
        BOOST_CHECK_EQUAL(parallelepiped.GetDensity(), expectedDensity);
    }

    // имеет объём
    BOOST_AUTO_TEST_CASE(has_a_volume)
    {
        BOOST_CHECK_CLOSE_FRACTION(parallelepiped.GetVolume(), expectedVolume, 1e-7);
    }

    // имеет массу
    BOOST_AUTO_TEST_CASE(has_a_mass)
    {
        BOOST_CHECK_CLOSE_FRACTION(parallelepiped.GetMass(), expectedDensity * expectedVolume, 1e-7);
    }

    // имеет строковое представление
    BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
    {
        const auto expectedString = R"(Parallelepiped:
	density = 8.8
	volume = 15740.844
	mass = 138519.4272
	width = 30.2
	height = 21.9
	depth = 23.8
)";
        BOOST_CHECK_EQUAL(parallelepiped.ToString(), expectedString);
    }
BOOST_AUTO_TEST_SUITE_END()
