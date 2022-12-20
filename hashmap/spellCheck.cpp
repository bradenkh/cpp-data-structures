/***********************************************************************
 * Module:
 *    Assignment 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    Braden Hansen
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "spellCheck.h"
#include "hash.h"
using namespace std;

/*****************************************
 * read in dictionary
 *****************************************/
void readInDictionary(StrHash & d)
{

   cout << "check 2\n";
   string tempStr = "/home/cs235/week12/dictionary.txt";
   ifstream fin;
   fin.open(tempStr.c_str());  
 
   cout << "check 2.1\n";
   if (fin.fail())
   {
      cout << "ERROR reading dictionary\n";
   }
   cout << "check 2.2\n";
   while (fin >> tempStr)
   { 
      d.insert(tempStr);
   }

   cout << "check 2.3\n";
   cout << "check 2.4\n";
   return;
}

/*****************************************
 * SPELL CHECK
 * Prompt the user for a file to spell-check
 * TODO:
 * write a readfile and put the dictionary into a hash
 * read the file to check and look for each word
 * to check words:
 *    use find on the word and loop through
 *    the list to see if it is there
 * put bad words into a list
 ****************************************/
void spellCheck()
{
   cout << "check 1\n";
   StrHash dictionary(676);
   readInDictionary(dictionary);

   string fileName;
   cout << "What file do you want to check? ";
   cin >> fileName;

   ifstream checkFile;
   cout << "check 3.1\n";
   checkFile.open(fileName.c_str());
   cout << "check 3.2\n";
   if (checkFile.fail())
   {
      cout << "error finding file: " << fileName << endl;
      return;
   }
   
   cout << "check 4\n";
   string checkWord;
   custom::list <string> badWords;
   while(checkFile >> checkWord)
   {
      checkWord[0] = tolower(checkWord[0]);
      if (!dictionary.find(checkWord))
      {
         badWords.push_back(checkWord);
      }
      
   }
   cout << "check 5\n";
   if (badWords.size() > 0)
   {
      cout << "Misspelled: ";
      custom :: list <string> :: iterator it;
      for (it = badWords.begin(); it != badWords.end(); ++it)
         cout << *it << ", ";
   }
   else
   {
      cout << "File contains no spelling errors\n";
   }
   
   cout << "check 6\n";
   checkFile.close();
   return;
}
