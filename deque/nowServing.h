/***********************************************************************
 * Header:
 *    NOW SERVING
 * Summary:
 *    This will contain just the prototype for nowServing(). You may
 *    want to put other class definitions here as well.
 * Author
 *    BRade
 ************************************************************************/

#ifndef NOW_SERVING_H
#define NOW_SERVING_H

#include "deque.h"     // for DEQUE

struct Request
{
  std::string name;
  std::string course;
  int minutes;

  Request() { minutes = 0;}
};


// the interactive nowServing program
void nowServing();

#endif // NOW_SERVING_H



