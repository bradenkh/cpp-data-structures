/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 *    Isabel Ding and Braden Hansen
 **********************************************************************/

#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"     // for QUEUE
#include "dollars.h"   // for DOLLARS
using namespace std;
using namespace custom;

// output the bought stock
void printBought(queue <Transaction> bought)
{
   std::cout << "Currently held:\n";
   while (!bought.empty())
   {
      Transaction trans(bought.front());
      bought.pop();
      std::cout << "\tBought " << trans.quantity << " shares at " << trans.price << "\n";
   }
   return;
}

// output the sold stock
void printSold(queue <Transaction> sold)
{
   std::cout << "Sell History:\n";
   while (!sold.empty())
   {
      Transaction trans(sold.front());
      sold.pop();
      std::cout << "\tSold " << trans.quantity << " shares at " << trans.price 
      << " for a profit of " << trans.profit << "\n";
   }
   return;
}

// output proceeds
void printProceeds(Dollars totalProceeds)
{
   std::cout << "Proceeds: " << totalProceeds << endl;
}

/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{
   // instructions
   cout << "This program will allow you to buy and sell stocks. "
        << "The actions are:\n";
   cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
   cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
   cout << "  display         - Display your current stock portfolio\n";
   cout << "  quit            - Display a final report and quit the program\n";

   // your code here...
   queue<Transaction> holdings;

   queue<Transaction> saleHistory;

   Dollars proceeds;

   string instruction;

   int quantity = 0;

   Dollars price;

   try

   {

      do

      {

         cout << "> ";

         cin  >> instruction;

         if (instruction == "buy")

         {

            //need to add validation/error handling

            cin >> quantity;

            cin >> price;

            holdings.push(Transaction(quantity, price));

         }

         else if (instruction == "sell")

         {

            //need to add validation/error handling

            cin >> quantity;

            cin >> price;

            Dollars originalCost = 0;

            Dollars saleAmount = 0;

            int tempQty = quantity;
            int totalShare = 0;
            queue<Transaction> temp = holdings;
            int size = temp.size();
            for (int i = 0; i < size; i++)
            {
                totalShare += temp.front().quantity;
                temp.pop();
            }

                // check if the sell share quantity is higher than we hold
            //if (quantity > totalShare)
            //{
            //    cout << "ERROR:You don't have that many shares" << endl;
            //}
            //else
            //{
                while (tempQty)
                {
                    int holdingQty = holdings.front().quantity;
                    Dollars holdingPrice = holdings.front().price;

                    if (tempQty >= holdingQty)
                    {
                        originalCost = holdingPrice * holdingQty;
                        saleAmount = price * holdingQty;
                        proceeds += saleAmount - originalCost;
                        saleHistory.push(Transaction(holdingQty, price, (saleAmount - originalCost)));
                        
                        tempQty -= holdingQty;
                        holdings.pop();
                        
                    }
                    else if (tempQty < holdingQty)
                    {
                        originalCost = holdingPrice * tempQty;
                        saleAmount = price * tempQty;
                        proceeds += saleAmount - originalCost;
                        // we will use this que to remake the holdings queue with a
                        // different value on the front
                        custom::queue <Transaction> tempQ;
                        // push our sale onto the sale history queue
                        saleHistory.push(Transaction(tempQty, price, (saleAmount - originalCost)));
                        // create a new transaction of what the first item should be
                        Transaction tempTrans((holdingQty - tempQty), holdingPrice);
                        // put it on our temporary queue, copy over everything esle and then copy back
                        tempQ.push(tempTrans);
                        holdings.pop();
                        while (!holdings.empty())
                        {
                           tempQ.push(holdings.front());
                           holdings.pop();
                        }
                        holdings = tempQ;
                        tempQty = 0;
                    }
                }
            //}
            
            //Transaction tempStock(holdings.front());

            //while (tempQty > tempStock.quantity)
            //{
               

            //}
            


            // put the oldest transaction into a temporary transaction
            //Transaction tempTrans = holdings.front();
            // subtract the quantity we want to sell
            //tempTrans.quantity = tempTrans.quantity - quantity;
            //queue <Transaction> tempQ;
            //tempQ.push(tempTrans);
            //if (!holdings.empty())
            //{
            //   holdings.pop();
            //}            
            //while (!holdings.empty())
            //{
            //   tempQ.push(holdings.front());
            //   holdings.pop();
            //}
            //holdings = tempQ;
            





            

            
                  

                  

         }

         else if (instruction == "display")
         {
            if (!holdings.empty())
            {
               printBought(holdings);
            }
           
            if (!saleHistory.empty())
            {
               printSold(saleHistory);
            }
           
            printProceeds(proceeds);
           

         }
         else if (instruction == "quit") {

            break;

         }

         else

         {

            cout << "Invalid command\n";

            cin.ignore(1000,'\n');

            cin.clear();

         }

      }

      while (instruction != "quit");

   }

   catch (const char * error)

   {

      cout << error << endl;

   }



}


