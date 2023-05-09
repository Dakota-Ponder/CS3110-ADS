// Header file for the PowerSeller class
// Powerseller class inherits from Seller class

#ifndef CS2170_POWERSELLER_H
#define CS2170_POWERSELLER_H

#include <iostream>
#include <fstream>
#include <string>
#include "Seller.h"
using namespace std;

class PowerSeller : public Seller
{
public:

  // default constructor
  PowerSeller();

  // copy constructor
  PowerSeller(const PowerSeller &p);

  // value constructor
  PowerSeller(string newFirstName, string newLastName, string newUserID,
              string newEmail, unsigned newavgRating, unsigned newTotalItemsSold,
              string newWebsite, unsigned newCurrentSold);


  // destructor
  virtual ~PowerSeller();

  // overloaded assignment operator
  PowerSeller& operator=(const PowerSeller &rhs);

  // overloaded input operator and output operator
  friend istream &operator>>(istream &is, PowerSeller &rhs);
  friend ostream &operator<<(ostream &os, const PowerSeller &rhs);

  // function to get the website of the powerseller
  string getWebsite() const;

  // function to get the current items sold by the powerseller
  unsigned getCurrentSold() const;

  // function to set the website of the powerseller
  void setWebsite(const string& newWebsite);

  // function to print the powerseller info
  void print(ostream &os) const;

  // function to read the powerseller info from a files
  void read(ifstream &is);

  // function to set the current items sold by the powerseller
  void setCurrentSold(const int newCurrentSold);

protected:
  string website;       // the website of the powerseller
  unsigned currentSold; // the number of items sold in the current year
};

#endif // POWERSELLER_H
