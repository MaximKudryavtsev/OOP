#include "stdafx.h"
#include "vector_processor.h"

std::vector<double> GetCoefficientsOfEquation(std::istream &strm)
{
    double a, b, c, d, e;

    if ((strm >> a) && (strm >> b) && (strm >> c) && (strm >> d) && (strm >> e))
    {
        return std::vector<double> {a, b, c, d, e};
    }
    else
    {
        throw std::domain_error("Can't get coefficients of equation");
    }
}

void PrintVector(const std::vector<double> &vect, std::ostream &strm)
{
    std::copy(vect.begin(), vect.end(), std::ostream_iterator<double>(strm << std::fixed << std::setprecision(3), " "));
}
