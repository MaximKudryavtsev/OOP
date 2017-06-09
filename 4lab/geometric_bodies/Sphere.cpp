#include "stdafx.h"
#include "Sphere.h"

CSphere::CSphere(double density, double radius)
    : CBody("Sphere", density)
    , m_radius(radius)
{
    if ((m_density < 0) || (m_radius < 0))
    {
        throw std::invalid_argument("Density and radius can't be negative...");
    }
}

double CSphere::GetRadius() const
{
    return m_radius;
}

double CSphere::GetVolume() const
{
    return (pow(m_radius, 3) * M_PI) * 4 / 3;
}

void CSphere::AppendProperties(std::ostream &strm) const
{
    strm << "\tradius = " << GetRadius() << '\n';
}
