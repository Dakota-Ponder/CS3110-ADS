#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include "Seller.h"
using namespace std;

// seller constructor
// set strings to null and ints to 0
Seller::Seller()
{
  avgRating = 0;
  totalItemsSold = 0;
}

// seller copy constructor
// copies one seller to another
Seller::Seller(const Seller& s)
{
  *this = s; // uses this pointer to assign one seller to another
}

// seller value constructor
Seller::Seller(string newFirstName, string newLastName,
               string newUserID, string newEmail,
               unsigned newavgRating, unsigned newTotalItemsSold) :
              Person(newFirstName, newLastName, newUserID, newEmail)
{
  avgRating = newavgRating;
  totalItemsSold = newTotalItemsSold;
}

// seller destructor
Seller::~Seller()
{
  // nothing to do
}

// overloaded assignment operator
// copies rhs seller info to the left hand side
Seller& Seller::operator=(const Seller& rhs)
{
  firstName = rhs.firstName;
  lastName = rhs.lastName;
  userID = rhs.userID;
  email = rhs.email;
  avgRating = rhs.avgRating;
  totalItemsSold = rhs.totalItemsSold;
  return *this;
}

// overloaded input operator
istream &operator>>(istream &is, Seller &rhs)
{

  string space;            // used to read in the space between first and last name
  Person * person = &rhs;  // a pointer to the base class
  is >> *person;          // read the base class info

  // read in the rest of the seller info
  cout << "Enter the average rating: ";
  getline(is, space);

  // check if the input is negative
  if(space[0] == '-')
  {
    // can't allow negative ratings
    cout << "Error: negative ratings are not allowed." << endl;

    // set the rating to 0
    rhs.avgRating = 0;
  }
  else
    // convert the string to unsigned int
    rhs.avgRating = (unsigned)atoi(space.c_str());

  // return the input stream
  return is;

}

// overloaded output operator
ostream &operator<<(ostream &os, const Seller &rhs)
{
  // print seller info using the print function
  rhs.print(os);

  // return the output stream
  return os;
}

// returns the average rating of a seller
float Seller::getAvgRating() const
{
  return avgRating;
}

// sets the average rating of a seller
void Seller::setAvgRating(unsigned newAvgRating)
{
  avgRating = newAvgRating;
}

// sets the total items sold by a seller
void Seller::setTotalItemsSold(unsigned newTotalItemsSold)
{
  totalItemsSold = newTotalItemsSold;
}

// print function
// prints out a sellers info
void Seller::print(ostream& os) const
{
  // variable to hold the users input
  string input;

  // print the base class info
  Person::print(os);
  os << "    Average Rating: " << avgRating << endl;
  os << "  Total Items Sold: " << totalItemsSold << endl;
}

// read function
void Seller::read(ifstream& is)
{
  // variable to hold temp char
  string temp;

  // read in the base class info
  Person::read(is);

  // read in the rest of the seller info
  getline(is, temp);
  avgRating = atoi(temp.c_str());  // convert the string to an int

  getline(is, temp);
  totalItemsSold = atoi(temp.c_str()); // convert the string to an int

}
