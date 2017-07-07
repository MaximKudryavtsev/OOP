#include "stdafx.h"
#include "StringStack.h"

int main()
{
    try
    {
        CStringStack stack;

        std::cout << stack.GetLastElement() << std::endl;
    }
    catch (const std::exception &error)
    {
        std::cerr << error.what() << std::endl;
    }

    return 0;
}
