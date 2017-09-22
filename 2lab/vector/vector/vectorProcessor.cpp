#include "stdafx.h"
#include "VectorProcessor.h"
#include <algorithm>
#include <numeric>
#include <functional>
#include <boost/range/algorithm/transform.hpp>
#pragma warning (push, 3)
#include <boost/phoenix.hpp>
#pragma warning (pop)

using namespace std;
using namespace std::placeholders;
using namespace boost::phoenix::placeholders;
using namespace boost::phoenix;
using boost::transform;

double GetMinElement(vector<double> & numbers)
{
    return *min_element(numbers.begin(), numbers.end());
}

double GetMaxElement(vector<double> & numbers)
{
	return *max_element(numbers.begin(), numbers.end());
}

void ProcessVector(std::vector<double> & numbers)
{
	double maxElement = GetMaxElement(numbers);
	double minElement = GetMinElement(numbers);
	if (GetMinElement(numbers) == 0)
	{
		cout << "can't devide on zero \n";
	}
	 else if (numbers.size() != 0)
	{
		 boost::transform(numbers, numbers.begin(), [maxElement, minElement](double number) {return (number * maxElement / minElement); });
	}
}