#include "type.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// implement the overloaded operator
bool flightRec::operator < (const flightRec & rhs) const
{
  return (destination < rhs.destination);
}

// implement the overloaded operator
bool flightRec::operator == (const flightRec & rhs) const
{
  return ((origin == rhs.origin) && (destination == rhs.destination));
}

ostream& operator << (ostream & os, const flightRec & f)
{
  //display the every element in the flightRec in an appropriate format
  os << setw(15) << f.origin << setw(15) << f.destination
     << setw(10) << f.flightNum << setw(4)
     << "$" << setw(3) << f.price << endl;

  return os;
}