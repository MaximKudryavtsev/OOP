#include "stdafx.h"
#include "Cone.h"

CCone::CCone(double density, double baseRadius, double height)
    : CBody("Cone", density)
    , m_baseRadius(baseRadius)
    , m_height(height)
{
    if ((m_density < 0) || (m_baseRadius < 0) || (m_height < 0))
    {
        throw std::invalid_argument("Density, base radius and height can't be negative...");
    }
}

double CCone::GetBaseRadius() const
{
    return m_baseRadius;
}

double CCone::GetHeight() const
{
    return m_height;
}

double CCone::GetVolume() const
{
    return M_PI * pow(m_baseRadius, 2) * m_height / 3;
}

void CCone::AppendProperties(std::ostream &strm) const
{
    strm << "\tbase radius = " << GetBaseRadius() << '\n'
         << "\theight = " << GetHeight() << '\n';
}
