#include "stdafx.h"
#include "vector_processor.h"
#include "equation.h"

int main()
{
    std::string buffer;

    while (!std::cin.eof())
    {
        std::cout << "Enter 5 coefficients of an equation: ";

        if (!std::getline(std::cin, buffer))
        {
            std::cout << "Good bye!" << std::endl;
            break;
        }

        try
        {
            std::istringstream strm(buffer);
            std::vector<double> coefficients = GetCoefficientsOfEquation(strm);
            EquationRoot4 roots = Solve4(coefficients[0], coefficients[1], coefficients[2], coefficients[3],
                                         coefficients[4]);
            PrintRoots(std::cout, roots);
        }
        catch (const std::exception &error)
        {
            std::cerr << error.what() << std::endl;
        }
    }

    return 0;
}
