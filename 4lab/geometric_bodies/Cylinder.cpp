#include "stdafx.h"
#include "Cylinder.h"

CCylinder::CCylinder(double density, double baseRadius, double height)
    : CBody("Cylinder", density)
    , m_baseRadius(baseRadius)
    , m_height(height)
{
    if ((m_density < 0) || (m_baseRadius < 0) || (m_height < 0))
    {
        throw std::invalid_argument("Density, base radius and height can't be negative...");
    }
}

double CCylinder::GetBaseRadius() const
{
    return m_baseRadius;
}

double CCylinder::GetHeight() const
{
    return m_height;
}

double CCylinder::GetVolume() const
{
    return M_PI * pow(m_baseRadius, 2) * m_height;
}

void CCylinder::AppendProperties(std::ostream &strm) const
{
    strm << "\tbase radius = " << GetBaseRadius() << '\n'
         << "\theight = " << GetHeight() << '\n';
}
