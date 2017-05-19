#include "stdafx.h"
#include "..\miniDictionary\dictionaryProcessor.h"
#include <string>
#include <sstream>

BOOST_AUTO_TEST_SUITE(get_dictionary_from_file_function)

	BOOST_AUTO_TEST_CASE(should_load_dictionary_map_from_file)
	{
		ifstream in("testIn.txt");
		Dictionary dictionary;
		Dictionary expectedDictionary = { { "cat", "кошка" }, { "dog", "собака" }, { "house", "дом" } };
		GetDictionaryFromFile(in, dictionary);
		BOOST_CHECK(dictionary == expectedDictionary);
	}

	BOOST_AUTO_TEST_CASE(should_be_empty_dictionary_if_input_file_is_empty)
	{
		ifstream in("testEmptyIn.txt");
		Dictionary dictionary;
		Dictionary expectedDictionary = {  };
		GetDictionaryFromFile(in, dictionary);
		BOOST_CHECK(dictionary == expectedDictionary);
	}

BOOST_AUTO_TEST_SUITE_END()

struct Dictionary_
{
	Dictionary_()
	{
		ifstream input(dictionaryFileName);
		GetDictionaryFromFile(input, dictionary);
	}
	Dictionary dictionary;
	string dictionaryFileName = "testIn.txt";
};

BOOST_FIXTURE_TEST_SUITE(process_dictionary_function, Dictionary_)

	BOOST_AUTO_TEST_CASE(can_find_translation)
	{
		stringstream inputStrm("cat");
		stringstream outputStrm;
		string expectedOutput(">>кошка");
		WorkWithDictionary(inputStrm, outputStrm, dictionary, dictionaryFileName);
		string output;
		getline(outputStrm, output);
		BOOST_CHECK_EQUAL(output, expectedOutput);
	}

	BOOST_AUTO_TEST_CASE(can_print_error_mesage)
	{
		stringstream inputStrm("work");
		stringstream outputStrm;
		string expectedOutput(">Неизвестное слово \"work\" Введите перевод или пустую строку для отказа.");
		WorkWithDictionary(inputStrm, outputStrm, dictionary, dictionaryFileName);
		string output;
		getline(outputStrm, output);
		BOOST_CHECK_EQUAL(output, expectedOutput);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(add_new_word_function, Dictionary_)

	BOOST_AUTO_TEST_CASE(can_add_new_word_to_dictionary)
	{
		map<string, string> expectedDictionary = { { "bird", "птица" },{ "cat", "кошка" },{ "dog", "собака" },{ "house", "дом" } };
		AddNewWordToDictionary(dictionary, "bird", "птица");
		BOOST_CHECK(dictionary == expectedDictionary);
	}

BOOST_AUTO_TEST_SUITE_END()

