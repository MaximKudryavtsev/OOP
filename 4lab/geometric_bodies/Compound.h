#pragma once

#include "Body.h"

class CCompound final : public CBody
{
public:
    CCompound();

    bool AddChildBody(const std::shared_ptr<CBody> &body);
    double GetVolume() const override;
    double GetMass() const override;

protected:
    void AppendProperties(std::ostream &strm) const override;

private:
    std::vector<std::shared_ptr<CBody>> m_elements;
};
