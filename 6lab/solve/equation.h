#pragma once

struct EquationRoot4
{
    int numRoots;
    double root[4];
};

EquationRoot4 Solve2(double a, double b, double c);
EquationRoot4 Solve3(double a, double b, double c, double d);
EquationRoot4 Solve4(double a, double b, double c, double d, double e);

void PrintRoots(std::ostream &strm, const EquationRoot4 &roots);
