#include "stdafx.h"
#include "Parallelepiped.h"

CParallelepiped::CParallelepiped(double density, double width, double height, double depth)
    : CBody("Parallelepiped", density)
    , m_width(width)
    , m_height(height)
    , m_depth(depth)
{
    if ((m_density < 0) || (m_width < 0) || (m_height < 0) || (m_depth < 0))
    {
        throw std::invalid_argument("Density, width, height and depth can't be negative...");
    }
}

CParallelepiped::~CParallelepiped()
{
}

double CParallelepiped::GetWidth() const
{
    return m_width;
}

double CParallelepiped::GetHeight() const
{
    return m_height;
}

double CParallelepiped::GetDepth() const
{
    return m_depth;
}

double CParallelepiped::GetVolume() const
{
    return m_width * m_height * m_depth;
}

void CParallelepiped::AppendProperties(std::ostream &strm) const
{
    strm << "\twidth = " << GetWidth() << '\n'
         << "\theight = " << GetHeight() << '\n'
         << "\tdepth = " << GetDepth() << '\n';
}
