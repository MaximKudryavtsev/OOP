#include "stdafx.h"
#include "SetProcessor.h"

using namespace std;

int main(int argc, char *argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	if (argc != 2)
	{
		cout << "Invalid count of arguments\n"
			<< "Usage: PrimeNumbers.exe <UpperBound>\n";
		return 1;
	}

	int upperBound = atoi(argv[1]);
	if ((upperBound < 0) || (upperBound > MAX_UPPER_BOUND))
	{
		cout << "Upper bound should be from 0 to " << MAX_UPPER_BOUND << "\n";
		return 1;
	}

	set<int> primeNumbers = GeneratePrimeNumbersSet(upperBound);
	cout << "количество простых чисел от 1 до " << upperBound << " = " << primeNumbers.size() << "\n";
	copy(primeNumbers.begin(), primeNumbers.end(), ostream_iterator<int>(cout, " "));
    return 0;
}
