#include "stdafx.h"
#include "SetProcessor.h"

using namespace std;


set<int> GeneratePrimeNumbersSet(const int upperBound)
{
	set<int> primeNumbersSet;
	vector<bool> primeNumbers;
	primeNumbers = FindPrimeNumbersInRange(upperBound);

	for (int i = 2; i <= upperBound; ++i)
	{
		if (primeNumbers[i])
		{
			primeNumbersSet.emplace(i);
		}
	}
	return primeNumbersSet;
}

vector<bool> FindPrimeNumbersInRange(const int upperBound)
{
	vector<bool> primeNumbers(upperBound + 1, true);

	for (int i = MIN_PRIME_NUMBER; (i*i) < upperBound + 1; ++i)
	{
		if (primeNumbers[i])
		{
			for (int j = (i*i); j <= upperBound; j += i)
			{
				if (primeNumbers[j])
				{
					primeNumbers[j] = false;
				}
			}
		}
	}

	return primeNumbers;
}