/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Kirby, CS 235
 * Author:
 *    Braden Hansen, Isabel Ding
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions 
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "ctype.h"     // for ISDIGIT
#include "stack.h"     // for STACK
#include <sstream>
#include <cctype>
#include <vector>
using namespace std;



/*****************************************************
 * Check if the string is an operator
 * 
 *****************************************************/
bool isOperator(const char infix)
{
    char operators[] = "+-*/()^";
    for (int i = 0; i < 8; i++)
    {
        if (infix == operators[i])
            return true;

    }
    return false;
}

/*****************************************************
 * Check the order of the operator
 *****************************************************/
int orderOfOperator(const char infix)
{
   switch (infix)
   {
      case '+':
         return 1;
         break;
      case '-':
         return 1;
         break;
      case '*':
         return 2;
         break;
      case '/':
         return 2;
         break;
      case '(':
         return 3;
         break;
      case '^':
         return 3;
         break;
      default:
         return 0;
   }
            
}

/*****************************************************
 * handle string will add a space where needed
 *****************************************************/
string handleString(const string oldString)
{
   string newString;
   for (int i = 0; i < oldString.length(); i++)
   {
      if (!isOperator(oldString[i]) && !isOperator(oldString[i + 1]))
      {
         newString += oldString[i];
      }
      else if ((isOperator(oldString[i]) == true) && (isOperator(oldString[i + 1]) == true))
      {
         newString = newString + oldString[i] + ' ';
      }
      else if (isOperator(oldString[i]) && oldString[i+1] != ' ')
      {
         newString = newString + oldString[i] + ' ';
      }   
      else
      {
         newString = newString + oldString[i] + ' ';
      }
   }
   return newString;
}

/****************************************************
 * this function will return true if the char is a
 * space or parentheses
 ****************************************************/
bool isSpaceOrParentheses(const char n)
{
   switch (n)
   {
   case ' ':
      return true;
      break;

   case ')':
      return true;
      break;

   case '(':
      return true;
      break;
   
   default:
      return false;
      break;
   }
}
/*****************************************************
 * fix string will remove extra spaces and ( )
 *****************************************************/
string fixString(const string oldString)
{
   string newString;
   int i = 0;
   while(oldString[i] != '\0')
   {
      newString += oldString[i];

      if(isSpaceOrParentheses(oldString[i]))
      {
         while(isSpaceOrParentheses(oldString[i + 1]))
         {
               i++;
         }
      }

      i++;
   }
   if (newString[newString.length() - 1] == ' ')
   {
      newString[newString.length() - 1] = '\n';
   }
   
   return newString;
}
/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 * do one stack and use the order of operations to swap the item on
 * top with the item you are looking at
 *****************************************************/
string convertInfixToPostfix(const string & oldInfix)
{
   string infix = handleString(oldInfix);
   custom::stack <string> postStack;
   string postfix = " ";
   for (int i = 0; i < infix.length(); i++)
   {
      if (!isOperator(infix[i]))
      {
         postfix += infix[i];
      }
      else if (isOperator(infix[i]))
      {
         while (!postStack.empty() && orderOfOperator(infix[i]) <= orderOfOperator(postStack.top()[0]) && postStack.top()[0] != '(')
         {
            postfix = postfix + postStack.top() + ' ';
            postStack.pop();
         }
         string tempString;
         tempString = tempString + infix[i] + ' ';
         postStack.push(tempString);
      }
      else if (infix[i] == '(')
      {
         string tempString;
         tempString = tempString + infix[i] + ' ';
         postStack.push(tempString);
      }
      else if (infix[i] == ')')
      {
         while (!postStack.empty() && postStack.top()[0] != '(')
         {
            postfix = postfix + postStack.top() + ' ';
            postStack.pop();
         }
         
      }
   }

   for (int i = 0; i < postStack.size() + 1; i++)
      {
         postfix = postfix + postStack.top() + ' ';
         postStack.pop();
      }
   return postfix;
  
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";
   
   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         postfix = fixString(postfix);
         cout << "\tpostfix: " << postfix << endl;
      }
   }
   while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string & postfix)
{
   string assembly;

   return assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);
      
      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   }
   while (input != "quit");
      
}
