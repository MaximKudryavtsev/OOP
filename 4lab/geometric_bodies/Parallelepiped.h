#pragma once

#include "Body.h"

class CParallelepiped final : public CBody
{
public:
    CParallelepiped(double density, double width, double height, double depth);
    ~CParallelepiped();

    double GetWidth() const;
    double GetHeight() const;
    double GetDepth() const;
    double GetVolume() const override;

protected:
    void AppendProperties(std::ostream &strm) const override;

private:
    double m_width;
    double m_height;
    double m_depth;
};

