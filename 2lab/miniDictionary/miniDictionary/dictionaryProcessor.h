#pragma once
#include "stdafx.h"

using namespace std;

#define Dictionary map<string, string>

void GetDictionaryFromFile(istream &dictionaryFile, Dictionary &dictionary);
void WorkWithDictionary(istream &input, ostream &output, Dictionary &dictionary, string &dictionaryFileName);
string PrintTranslation(Dictionary &dictionary, string &inputWord);
string ProcessNewWord(Dictionary &dictionary, istream &input, string &inputWord, bool &haveNewWords);

void AddNewWordToDictionary(Dictionary &dictionary, string const &inputWord, string const &translation);
void UpdateDictionary(istream &input, Dictionary &dictionary, string const &dictionaryFileName);
void SaveDictionaryToFile(ofstream &dictionaryFileOut, Dictionary &dictionary);
