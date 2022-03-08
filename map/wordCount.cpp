/***********************************************************************
 * Module:
 *    Week 10, WORD COUNT
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    This program will implement the wordCount() function
 ************************************************************************/
#include <string>
#include <fstream>
#include "map.h"       // for MAP
#include "wordCount.h" // for wordCount() prototype

using namespace std;

/****************************************************
 * get filename gets the filename from the user
 *************************************************/
string getFileName()
{
    string str;
    cout << "What is the filename to be counted? ";
    cin >> str;
    return str;
}


/*****************************************************
 * WORD COUNT
 * Prompt the user for a file to read, then prompt the
 * user for words to get the count from
 *****************************************************/
void wordCount()
    {
    string fileName = getFileName();
    map <string, int> wordMap; // I edited the pair class to use second in comparison -Braden

    // read in a word
    ifstream fin;
    fin.open(fileName);

    if (fin.fail())
    {
        // handle error here
        return;
    }

    string tempStr;
    while (fin >> tempStr)
    {
        wordMap[tempStr] = wordMap[tempStr] + 1;
    }

    cout << "What word whose frequency is to be found. Type ! when done\n";
    cout << "> ";
    cin  >> tempStr;
    while (tempStr != "!")
    {
        cout << "\t" << tempStr << " : " << wordMap[tempStr] << endl;
        cout << "> ";
        cin >> tempStr;
    }

    fin.close();

    
}
