
#include "stdafx.h"
#include "vectorProcessor.h"

using namespace std;

int main()
{
    cout << "Enter the elements of array with spaces\n";
    vector<double> numbers(istream_iterator<double>(cin), (istream_iterator<double>()));
    ProcessVector(numbers);
    sort(numbers.begin(), numbers.end());
    copy(numbers.begin(), numbers.end(), ostream_iterator<double>(cout, ", "));
    cout << "\nSize of vector: " << numbers.size() << "\n";

    return 0;
}


