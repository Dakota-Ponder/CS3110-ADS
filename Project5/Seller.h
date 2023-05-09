#ifndef SELLER_H
#define SELLER_H

#include <iostream>
#include <fstream>
#include <string>
#include "Person.h"
using namespace std;

// Seller class that inherits from Person
class Seller : public Person
{
public:

  // constructor
  Seller();

  // copy constructor
  Seller(const Seller& s);

  // value constructor
  Seller(string newFirstName, string newLastName,
         string newUserID, string newEmail, unsigned newavgRating, unsigned newTotalItemsSold);

  // destructor
  virtual ~Seller();

  // overloaded assignment operator that assigns one sellers info to another
  Seller& operator=(const Seller& rhs);

  // overloaded output and input operator that prints out a sellers info
  friend istream& operator>>(istream& is, Seller& rhs);
  friend ostream& operator<<(ostream& os, const Seller& rhs);

  // getters and setters

  // returns the average rating of a seller
  float getAvgRating() const;

  // sets the average rating of a seller
  void setAvgRating(unsigned newAvgRating);

  // returns the total items sold by a seller
  int getTotalItemsSold() const;

  // sets the total items sold by a seller
  void setTotalItemsSold(unsigned newTotalItemsSold);

  // function to print out a sellers info
  void print(ostream& os) const;

  // function to read in a sellers info from a file
  void read(ifstream& is);

protected:

  // average rating of a seller
  unsigned avgRating;

  // total items sold by a seller stored in a list
  unsigned totalItemsSold;

};

#endif // CS2170_SELLER_H
