/***********************************************************************
* Program:
*    Assignment 01, Go Fish
*    Brother Helfrich, CS 235
* Author:
*    <your names here>
* Summary: 
*    This is all the functions necessary to play Go Fish!
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part.
************************************************************************/

#include <iostream>
#include <fstream>
#include "set.h"
#include "card.h"
#include "goFish.h"
using namespace std;

#define ROUNDS 5

/**********************************************************************
 * GO FISH
 * The function which starts it all
 ***********************************************************************/
void goFish()
{
   // custom::set <int> hand;
   // hand.insert(1);
   // hand.insert(2);
   // hand.insert(3);
   // hand.insert(4);
   // hand.insert(5);

   custom::set <Card> hand;
   ifstream fin;
   fin.open("/home/cs235/week05/hand.txt");
   if (fin.fail())
   {
      return;
   }
   Card finCard;
   while (!fin.eof())
   {
      fin >> finCard;
      hand.insert(finCard);
   }

   fin.close();

   cout << "We will play " << ROUNDS << " rounds of Go Fish.  Guess the card in the hand\n";

   Card tempCard;
   int matches = 0;

   custom::set <Card> :: iterator itEmpty;
   custom::set <Card> :: iterator itFind;

   for (int i = 1; i < (ROUNDS+1); i++)
   {
      // get input from user
      cout << "round " << i << ": ";
      cin >> tempCard;
      // get our iterators for comparison
      itEmpty = hand.end();
      itFind = hand.find(tempCard);
      // display results
      if (itFind != itEmpty)
      {
         cout << "\tYou got a match!\n";
         matches++;
         hand.erase(itFind);
      }
      else
      {
         cout << "\tGo Fish!\n";
      }
   }
   
   cout << "You have " << matches << " matches!\n";

   //print remaining cards in hand
   cout << "The remaining cards: ";
   custom::set <Card> :: iterator it = hand.begin();
   while (it != hand.end())
   {
      cout << *it;
      if (++it != hand.end())
      {
         cout << ", ";
      }
      else
      {
         cout << endl;
      }
   }
      
   

   return ;
}
