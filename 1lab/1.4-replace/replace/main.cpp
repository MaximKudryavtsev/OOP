#include "stdafx.h"

using namespace std;

bool IsFilesOpened(ifstream &inputFile, const ofstream &outputFile)
{
    if (!inputFile.is_open())
    {
        return false;
    }
    if (!outputFile.is_open())
    {
        return false;
    }
    return true;
}

bool IsFileEmpty(ifstream &inputFile)
{
    return inputFile.peek() == ifstream::traits_type::eof();
}

void Replace(ifstream &inputFile, ofstream &outputFile, string searchString, string replaceString)
{
    string line;
    size_t pos = 0;
    while (getline(inputFile, line))
    {
        pos = 0;
        while (pos = line.find(searchString, pos), pos != string::npos)
        {
            line.replace(pos, searchString.size(), replaceString);
            pos += replaceString.size();
        }
        outputFile << line << "\n";
    }
}

int main(int argc, char* argv[])
{
    if (argc != 5)
    {
        cout << "Invalid amount of arguments\n"
            << "Usage: replace.exe <input> <output> <search> <replace>" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);
    ofstream outputFile(argv[2]);
    string searchString = argv[3];
    string replaceString = argv[4];


    if (IsFileEmpty(inputFile))
    {
        outputFile << "File " << argv[1] << " is empty";
        cout << "File " << argv[1] << " is empty \n";
    }


    Replace(inputFile, outputFile, searchString, replaceString);

    return 0;
}