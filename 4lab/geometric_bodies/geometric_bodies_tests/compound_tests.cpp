#include "stdafx.h"

#define _USE_MATH_DEFINES
#include "../Compound.h"
#include <math.h>

struct Compound_
{
    const double expectedDensity = 0;
    const double expectedVolume = 0;
    const CCompound compound;
    Compound_()
        : compound()
    {}
};

// Составное тело
BOOST_FIXTURE_TEST_SUITE(Compound, Compound_)
    // является объемным телом
    BOOST_AUTO_TEST_CASE(is_a_body)
    {
        BOOST_CHECK(static_cast<const CBody*>(&compound));
    }

    // имеет объем
    BOOST_AUTO_TEST_CASE(has_a_volume)
    {
        BOOST_CHECK_CLOSE_FRACTION(compound.GetVolume(), expectedVolume, 1e-7);
    }

    // имеет массу
    BOOST_AUTO_TEST_CASE(has_a_mass)
    {
        BOOST_CHECK_CLOSE_FRACTION(compound.GetMass(), expectedVolume * expectedDensity, 1e-7);
    }
BOOST_AUTO_TEST_SUITE_END()
