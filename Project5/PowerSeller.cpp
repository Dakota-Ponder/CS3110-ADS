#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include "PowerSeller.h"
#include "Seller.h"
using namespace std;

// constructor that sets the data members to empty strings and ints to null
PowerSeller::PowerSeller() : Seller()  // call the seller constructor
{
  website = "";
  currentSold = 0;
}

// copy constructor that uses overloaded assignment operator
PowerSeller::PowerSeller(const PowerSeller &p)
{
  *this = p;
}

// value constructor that uses the values input by the user to initialize
PowerSeller::PowerSeller(string newFirstName, string newLastName, string newUserID,
                         string newEmail, unsigned newavgRating, unsigned newTotalItemsSold,
                         string newWebsite, unsigned newCurrentSold) :
         Seller(newFirstName, newLastName, newUserID,
                newEmail, newavgRating, newTotalItemsSold)
{
  website = newWebsite;
  currentSold = newCurrentSold;
}

// destructor that resets the strings to empty strings
PowerSeller::~PowerSeller()
{
  website = "";
}

// overloaded assignment operator that sets the values in the *this pointer
// to the values in the rhs pointer
PowerSeller& PowerSeller::operator=(const PowerSeller &rhs)
{

  // copy base class data members
  firstName = rhs.firstName;
  lastName = rhs.lastName;
  userID = rhs.userID;
  email = rhs.email;
  avgRating = rhs.avgRating;
  totalItemsSold = rhs.totalItemsSold;

  // copy derived class data members
  website = rhs.website;
  currentSold = rhs.currentSold;
  return *this;
}

// overloaded input operator that reads in the values from the file
istream& operator>>(istream& is, PowerSeller& rhs)
{
  string space;  // used to read in the space between the first and last name
  Seller *seller = &rhs;  // create a pointer to the base class

  // read in the values from the file
  is >> *seller;

  cout << "Enter the website of the PowerSeller: ";
  getline(is, rhs.website);

  cout << "Enter the number of items sold this year: ";
  getline(is, space);

  if(space[0] == '-')
  {
    cout << "Error: Invalid input. Please enter a positive number." << endl;

    // set the values to null
    rhs.currentSold = 0;
  }
  else
  {
    // positive number, so convert to an int
    rhs.currentSold = (unsigned)atoi(space.c_str());
  }
  return is;
}

// overloaded output operator that prints the values to the screen
ostream& operator<<(ostream& os, const PowerSeller& rhs)
{
  // print base class data members
  rhs.print(os);

  // print derived class data members
  os << "Website: " << rhs.website << endl;
  os << "Items sold this year: " << rhs.currentSold << endl;
}

// function to get the sellers website
string PowerSeller::getWebsite() const
{
  return website;
}

// function to get the number of items sold this year
unsigned PowerSeller::getCurrentSold() const
{
  return currentSold;
}

// function to print the values to the screen
void PowerSeller::print(ostream& os) const
{
  // print base class data members
  Seller::print(os);

  // print derived class data members
  os << "Website: " << website << endl;
  os << "Items sold this year: " << currentSold << endl;
}

// function to read in the values from the file
void PowerSeller::read(ifstream& is)
{
  string space;  // used to read in the space between the first and last name

  // call read function from base class
  Seller::read(is);

  // read in the values from the file
  getline(is, website);
  getline(is, space); // read in the space between the first and last name
  currentSold = (unsigned)atoi(space.c_str());  // convert to an int

}

// function to set the sellers website
void PowerSeller::setWebsite(const string& newWebsite)
{
  website = newWebsite;
}

// function to set the number of items sold this year
void PowerSeller::setCurrentSold(const int newCurrentSold)
{
  currentSold = newCurrentSold;
}

