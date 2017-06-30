#include "stdafx.h"
#include "equation.h"

using namespace std;

namespace
{

int GetSign(double value)
{
    return (value < 0) ? -1 : (value == 0) ? 0 : 1;
}

double GetSqrt(double x)
{
    if (x < 0)
    {
        throw invalid_argument("Can't calculate square root of negative value...");
    }

    return sqrt(x);
}

double GetVieteCoefficientQ(double a, double b)
{
    return (pow(a, 2) - 3 * b) / 9;
}

double GetVieteCoefficientR(double a, double b, double c)
{
    return (2 * pow(a, 3) - 9 * a * b + 27 * c) / 54;
}

double GetVieteCoefficientS(double q, double r)
{
    return pow(q, 3) - pow(r, 2);
}

void ProcessCaseWhenCoefficientSMoreThanZero(EquationRoot4 &roots, double a, double r, double q)
{
    double t = acos(r / GetSqrt(pow(abs(q), 3))) / 3;
    roots.numRoots = 3;
    roots.root[0] = -2 * GetSqrt(abs(q)) * cos(t) - (a / 3);
    roots.root[1] = -2 * GetSqrt(abs(q)) * cos(t + (2 * M_PI) / 3) - (a / 3);
    roots.root[2] = -2 * GetSqrt(abs(q)) * cos(t - (2 * M_PI) / 3) - (a / 3);
}

void ProcessCaseWhenCoefficientSEqualsToZero(EquationRoot4 &roots, double a, double r)
{
    roots.numRoots = 2;
    roots.root[0] = -2 * pow(r, 0.33) - (a / 3);
    roots.root[1] = pow(r, 0.33) - (a / 3);
}

void ProcessCaseWhenCoefficientSLessThanZero(EquationRoot4 &roots, double q, double r, double a)
{
    if (q > 0)
    {
        double t = acosh(abs(r) / GetSqrt(pow(abs(q), 3))) / 3;
        roots.numRoots = 1;
        roots.root[0] = -2.0 * GetSign(r) * GetSqrt(abs(q)) * cosh(t) - a / 3.0;
    }
    else
    {
        double t = asinh(abs(r) / GetSqrt(pow(abs(q), 3))) / 3;
        roots.numRoots = 1;
        roots.root[0] = -2.0 * GetSign(r) * GetSqrt(abs(q)) * sinh(t) - a / 3.0;
    }
}

EquationRoot4 GetRootsOfProvidedCubicEquation(double a, double b, double c)
{
    EquationRoot4 roots;

    double q = GetVieteCoefficientQ(a, b);
    double r = GetVieteCoefficientR(a, b, c);
    double s = GetVieteCoefficientS(q, r);

    if (s > 0)
    {
        ProcessCaseWhenCoefficientSMoreThanZero(roots, a, r, q);
    }
    else if (abs(s) < DBL_EPSILON)
    {
        ProcessCaseWhenCoefficientSEqualsToZero(roots, a, r);
    }
    else
    {
        ProcessCaseWhenCoefficientSLessThanZero(roots, q, r, a);
    }

    return roots;
}

EquationRoot4 MergeResolventRoots(const EquationRoot4 &resolvent1, const EquationRoot4 &resolvent2)
{
    EquationRoot4 result;

    result.numRoots = resolvent1.numRoots + resolvent2.numRoots;

    for (int i = 0; i < resolvent1.numRoots; ++i)
    {
        result.root[i] = resolvent1.root[i];
    }

    for (int i = 0; i < resolvent2.numRoots; ++i)
    {
        result.root[i + resolvent1.numRoots] = resolvent2.root[i];
    }

    return result;
}

double GetResolventCoefficientP(const EquationRoot4 &resolvent)
{
    return *max_element(begin(resolvent.root), end(resolvent.root));
}

double GetResolventCoefficientQ(double a, double b, double p)
{
    return GetSqrt((a * a / 4) - (b - p));
}

double GetResolventCoefficientR(double a, double c, double d, double p)
{
    double r = GetSqrt(abs(p * p / 4 - d));

    if ((a * p / 2 - c) < 0)
    {
        r *= -1;
    }

    return r;
}

EquationRoot4 GetRootsOfProvidedEquation4(double a, double b, double c, double d)
{
    double p = -b;
    double q = (a * c) - (4 * d);
    double r = 4 * (b * d) - (a * a * d) - (c * c);

    EquationRoot4 resolvent = GetRootsOfProvidedCubicEquation(p, q, r);

    p = GetResolventCoefficientP(resolvent);
    q = GetResolventCoefficientQ(a, b, p);
    r = GetResolventCoefficientR(a, c, d, p);

    EquationRoot4 resolvent1 = Solve2(1, a / 2 + q, p / 2 + r);
    EquationRoot4 resolvent2 = Solve2(1, a / 2 - q, p / 2 - r);

    if ((resolvent1.numRoots == 0) && (resolvent2.numRoots == 0))
    {
        throw domain_error("Equation does not have any real roots");
    }

    resolvent = MergeResolventRoots(resolvent1, resolvent2);

    return resolvent;
}

}

EquationRoot4 Solve2(double a, double b, double c)
{
    if (abs(a) < DBL_EPSILON)
    {
        throw invalid_argument("\"a\" coefficient can't be zero");
    }

    double discriminant = b * b - 4 * a * c;

    EquationRoot4 roots;

    if (discriminant == 0)
    {
        roots.numRoots = 2;
        roots.root[0] = -b / (2 * a);
        roots.root[1] = -b / (2 * a);
    }
    else if (discriminant > 0)
    {
        roots.numRoots = 2;
        roots.root[0] = (-b + sqrt(discriminant)) / (2 * a);
        roots.root[1] = (-b - sqrt(discriminant)) / (2 * a);
    }
    else
    {
        roots.numRoots = 0;
        // throw domain_error("Equation does not have any real roots");
    }

    return roots;
}

EquationRoot4 Solve3(double a, double b, double c, double d)
{
    if (abs(a) < DBL_EPSILON)
    {
        throw invalid_argument("\"a\" coefficient can't be zero");
    }

    b /= a;
    c /= a;
    d /= a;

    // Решаем приведённое кубическое уравнение
    return GetRootsOfProvidedCubicEquation(b, c, d);
}

EquationRoot4 Solve4(double a, double b, double c, double d, double e)
{
    if (abs(a) < DBL_EPSILON)
    {
        throw invalid_argument("\"a\" coefficient can't be zero");
    }

    b /= a;
    c /= a;
    d /= a;
    e /= a;

    // Решаем приведённое уравнение 4-ой степени
    return GetRootsOfProvidedEquation4(b, c, d, e);
}

void PrintRoots(ostream &strm, const EquationRoot4 &roots)
{
    switch (roots.numRoots)
    {
    case 0:
        strm << "Equation does not have any real roots..." << endl;
        break;
    case 1:
        strm << fixed << setprecision(3) << "Equation have only one real root:\nx = "
             << roots.root[0] << '.' << endl;
        break;
    case 2:
        strm << fixed << setprecision(3) << "Equation have two real roots:\nx1 = "
             << roots.root[0] << ";\nx2 = " << roots.root[1] << '.' << endl;
        break;
    case 3:
        strm << fixed << setprecision(3) << "Equation have three real roots:\nx1 = "
            << roots.root[0] << ";\nx2 = " << roots.root[1] << ";\nx3 = "
            << roots.root[2] << endl;
        break;
    case 4:
        strm << fixed << setprecision(3) << "Equation have four real roots:\nx1 = "
            << roots.root[0] << ";\nx2 = " << roots.root[1] << ";\nx3 = "
            << roots.root[2] << ";\nx4 = " << roots.root[3] << "." << endl;
        break;
    default:
        strm << "Some error occurred, can't print roots" << endl;
        break;
    }
}
