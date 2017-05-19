1// flipbyte.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;

void FlipByte(int input)
{
	int flippedNumber = 0;
	for (int i = 0; i < 8; ++i)
	{
		int mask = (1 << i);
		if ((input & mask) != 0)
		{
			flippedNumber |= (1 << (7 - i));
		}
	}
	cout << "Flipped number is " << flippedNumber << "\n";
}

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count:\n"
			<< "Usage: FlipByte.exe <byte>\n";
		return 1;
	}
	int input = atoi(argv[1]);
	if ((input < 0) || (input > 255))
	{
		cout << "Error: <byte> must be from 0 to 255" << "\n";
		return 1;
	}
	else
	{
		cout << "Input number is " << input << "\n";
	}
	FlipByte(input);
	return 0;
}
