/***********************************************************************
 * Header:
 *    STOCK
 * Summary:
 *    This will contain just the prototype for stocksBuySell(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Braden Hansen
 ************************************************************************/

#ifndef STOCK_H
#define STOCK_H

#include "dollars.h"   // for Dollars defined in StockTransaction
#include "queue.h"     // for QUEUE
#include <iostream>    // for ISTREAM and OSTREAM

struct Transaction
{
  int quantity;
  Dollars price;
  Dollars profit;
  Transaction() {quantity = 1; price = 1; profit = 0;}  
  Transaction(int q, Dollars p) { quantity = q; price = p; profit = 0;}
  Transaction(int q, Dollars p, Dollars prft) { quantity = q; price = p; profit = prft;}
  Transaction(const Transaction &rhs) 
  {quantity = rhs.quantity; price = rhs.price; profit = rhs.profit;}
};

// the interactive stock buy/sell function
void stocksBuySell();

#endif // STOCK_H

