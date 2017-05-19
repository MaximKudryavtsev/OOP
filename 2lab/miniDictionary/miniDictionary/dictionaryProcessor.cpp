#include "stdafx.h"
#include "dictionaryProcessor.h"

void GetDictionaryFromFile(istream &dictionaryFile, Dictionary &dictionary)
{
	string key;
	string value;
	while (getline(dictionaryFile, key))
	{
		getline(dictionaryFile, value);
		dictionary.insert(make_pair(key, value));
	}
}


void WorkWithDictionary(istream &input, ostream &output, Dictionary &dictionary, string &dictionaryFileName)
{
	const string EXIT_STRING = "...";
	string inputWord;
	bool haveNewWords = false;

	output << ">";
	while (getline(input, inputWord) && (inputWord != EXIT_STRING))
	{
		if (!inputWord.empty())
		{
			bool haveTranslation = (dictionary.find(inputWord) != dictionary.end());
			if (haveTranslation)
			{
				output << ">" << PrintTranslation(dictionary, inputWord) << "\n";
			}
			else
			{
				output << "Неизвестное слово \"" + inputWord + "\" Введите перевод или пустую строку для отказа.\n>";
				output << ProcessNewWord(dictionary, input, inputWord, haveNewWords);
			}
		}
		output << ">";
	}

	if (haveNewWords)
	{
		output << "В словарь были внесены изменения.Введите Y или y для сохранения перед выходом.\n>";
		UpdateDictionary(input, dictionary, dictionaryFileName);
	}
}

string PrintTranslation(Dictionary &dictionary, string &inputWord)
{
	return dictionary.find(inputWord)->second;
}

string ProcessNewWord(Dictionary &dictionary, istream &input, string &inputWord, bool &haveNewWords)
{
	string output;
	output += ">";
	string translation;
	getline(input, translation);
	if (translation != "")
	{
		output += ("Слово \"" + inputWord + "\" сохранено в словаре как \"" + translation + "\"\n");
		AddNewWordToDictionary(dictionary, inputWord, translation);
		haveNewWords = true;
	}
	else
	{
		output += ("Слово \"" + inputWord + "\" проигнорировано\n");
	}
	return output;
}

void AddNewWordToDictionary(Dictionary &dictionary, string const &inputWord, string const &translation)
{
	dictionary.insert(make_pair(inputWord, translation));
}

void UpdateDictionary(istream &input, Dictionary &dictionary, string const &dictionaryFileName)
{
	string userAnswer;
	input >> userAnswer;
	if (userAnswer == "Y" || userAnswer == "y")
	{
		ofstream dictionaryFileOut(dictionaryFileName);
		SaveDictionaryToFile(dictionaryFileOut, dictionary);
	}
}

void SaveDictionaryToFile(ofstream &dictionaryFileOut, Dictionary &dictionary)
{
	for (auto it = dictionary.begin(); it != dictionary.end(); ++it)
	{
		dictionaryFileOut << (*it).first << "\n" << (*it).second << "\n";
	}
	dictionaryFileOut.close();
}
