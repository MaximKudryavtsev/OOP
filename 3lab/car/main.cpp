#include "stdafx.h"
#include "Car.h"
#include "CarController.h"

using namespace std;

int main()
{
    CCar car;
    CCarController controller(car, cin, cout);

    while ((!cin.eof()) && (!cin.fail()))
    {
        cout << "> ";
        controller.HandleCommand();
    }

    return 0;
}
