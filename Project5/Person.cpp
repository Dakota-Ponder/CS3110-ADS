#ifndef PERSON_CPP
#define PERSON_CPP

#include "Person.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;


// default constructor
// sets person to a set of empty strings
Person::Person()
{
  firstName = "";
  lastName = "";
  userID = "";
  email = "";
}

// copy constructor that uses overloaded assignment operator
// to set the values in the *this pointer
Person::Person(const Person &p)
{
  *this = p;
}

// value constructor that uses the values input by the user to initialize
// the data members
Person::Person(string newFirstName, string newLastName, string newUserID,
               string newEmail)
{
  firstName = newFirstName;
  lastName = newLastName;
  userID = newUserID;
  email = newEmail;
}

// destructor that resets the strings to empty strings
Person::~Person()
{
  firstName = "";
  lastName = "";
  userID = "";
  email = "";
}

// function to get a users whole name
string Person::getName() const
{
  string name = firstName + " " + lastName;
  return name;
}

// function to get a users first name
string Person::getFirstName() const
{
  return firstName;
}

// function to get a users last name
string Person::getLastName() const
{
  return lastName;
}

// function to get a users user ID
string Person::getUserID() const
{
  return userID;
}

// function to get a users email
string Person::getEmail() const
{
  return email;
}

// function to set a users whole name
void Person::setName(const string& newFirstName, const string& newLastName)
{
  firstName = newFirstName;
  lastName = newLastName;
}

// function to set a users first name
void Person::setFirstName(const string& newFirstName)
{
  firstName = newFirstName;
}

// function to set a users last name
void Person::setLastName(const string& newLastName)
{
  lastName = newLastName;
}

// function to set a users user ID
void Person::setUserID(const string& newUserID)
{
  userID = newUserID;
}

// function to set a users email
void Person::setEmail(const string& newEmail)
{
  email = newEmail;
}

// function to print a persons information
void Person::print(ostream& os) const
{
  os << "Name: " << getName() << endl;
  os << "User ID: " << getUserID() << endl;
  os << "Email: " << getEmail() << endl;

}

// function to read a persons information from a file
void Person::read(ifstream& is)
{
  string temp;  //
  // read in the first name
  getline(is, firstName);
  // read in the last name
  getline(is, lastName);
  // read in the user ID
  getline(is, userID);
  // read in the email
  getline(is, email);

  return;
}

// overloaded == operator
// returns true if the user names are the same
bool Person::operator==(const Person& rhs) const
{
  if (firstName == rhs.firstName && lastName == rhs.lastName)
    return true;
  else
    return false;
}

// overloaded != operator
bool Person::operator!=(const Person& rhs) const
{
  return (firstName != rhs.firstName || lastName != rhs.lastName);
}

// overloaded < operator
// return true if last name is less than rhs last name
// return true if last names are the same and first name is less than rhs
bool Person::operator<(const Person& rhs) const
{
  if(lastName < rhs.lastName || lastName == rhs.lastName && firstName < rhs.firstName)
  {
    return true;
  }
}

// overloaded <= operator
// returns true if lhs name is <=
// last name takes priority, followed by first name if the last are equal
bool Person::operator<=(const Person &rhs) const
{
  // check last name
  if (lastName < rhs.lastName)
  {
    return true;
  }
  else if(lastName > rhs.lastName)
  {
    return false;
  }
  // last names are the same
  //

  // check first name
  if(firstName <= rhs.lastName)
  {
    return true;
  }
  else // if last names are the same
       // but first name is greater than rhs return false
    return false;
}

// overloaded > operator
// returns true if last name is greater than rhs last name
// return true if last names are == and first name is greater than the rhs first name
bool Person::operator>(const Person &rhs) const
{
  if((lastName > rhs.lastName) || (lastName == rhs.lastName && firstName > rhs.firstName))
  {
    return true;
  }
  else
    return false;
}

// overloaded >= operator
// returns true if last name is >=, false otherwise
bool Person::operator>=(const Person &rhs) const
{
  if(lastName > rhs.lastName)
  {
    return true;
  }
  if(lastName < rhs.lastName)
  {
    return false;
  }
  // last names are the same but we have to check first names
  if(firstName >= rhs.firstName)
  {
    return true;
  }

  // if last names are the same but first name is less than rhs return false
  return false;
  }

// overloaded assignment operator
// returns the values in the *this pointer
// copies the values from the rhs pointer to the left hand side pointer
  Person& Person::operator=(const Person &rhs)
  {
    // assign the values from the rhs pointer to the left hand side pointer
    firstName = rhs.firstName;
    lastName = rhs.lastName;
    userID = rhs.userID;
    email = rhs.email;

    // return the values in the *this pointer
    return *this;
  }

// overloaded >> operator
// returns the input stream from the user
// uses the getline function to read in the users input
  // TODO : try to use the read function instead of getline
  istream& operator>>(istream &is, Person& rhs)
  {
    cout << "Enter first name: ";
    getline(is, rhs.firstName);

    cout << "Enter last name: ";
    getline(is, rhs.lastName);

    cout << "Enter user ID: ";
    getline(is, rhs.userID);

    cout << "Enter email: ";
    getline(is, rhs.email);

    return is;
  }

  // overloaded << operator
  // returns the output stream to the user
  ostream& operator<<(ostream &os, const Person& rhs)
  {
    // print the persons information
  rhs.print(os);
  return os;
  }

#endif