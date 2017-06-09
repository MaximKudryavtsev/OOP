#include "stdafx.h"
#include "Body.h"

CBody::CBody(const std::string &type, double density)
    : m_density(density)
    , m_type(type)
{
}

CBody::~CBody() = default;

double CBody::GetDensity() const
{
    return m_density;
}

double CBody::GetMass() const
{
    return GetDensity() * GetVolume();
}

std::string CBody::ToString() const
{
    std::ostringstream strm;

    strm << m_type << ":" << std::endl << std::setprecision(10)
         << "\tdensity = " << GetDensity() << '\n'
         << "\tvolume = " << GetVolume() << '\n'
         << "\tmass = " << GetMass() << '\n';
    AppendProperties(strm);

    return strm.str();
}
