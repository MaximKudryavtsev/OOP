#include "stdafx.h"
#include "dictionaryProcessor.h"

using namespace std;

int main(int argc, char *argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	if (argc != 2)
	{
		cout << "Invalid count of arguments\n"
			<< "Usage: miniDictionary.exe <dictionary file name>\n";
		return EXIT_FAILURE;
	}

	Dictionary dictionary;
	string dictionaryFileName = argv[1];
	ifstream dictionaryFile(dictionaryFileName);
	if (!dictionaryFile.is_open())
	{
		cout << "Ошибка открытия файла \"" << dictionaryFileName << "\" для чтения словаря\n";
	}
	else
	{
		GetDictionaryFromFile(dictionaryFile, dictionary);
		dictionaryFile.close();
	}

	WorkWithDictionary(cin, cout, dictionary, dictionaryFileName);
	
	return EXIT_SUCCESS;
}