// Person class for a user of the system.
// Class should contain first name, last name, user ID and email
// Also needs default constructor, value constructor that recieves
// all of the data to be placed into the data members,
// and a copy constructor.
//
#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Person
{
public:
  // Default constructor
  Person();

  //copy constructor
  Person(const Person& p);

  // Value constructor
  Person(string newFirstName, string newLastName,
         string newUserID, string newEmail);

  // Destructor
  virtual ~Person();  // set as virtual to allow for polymorphism

  // Accessors
  // function to get a users whole name
  string getName() const;

  // function to get a users first name
  string getFirstName() const;

  // function to get a users last name
  string getLastName() const;

  // function to get a users user ID
  string getUserID() const;

  // function to get a users email
  string getEmail() const;

  // Mutators

  // function to set a users whole name
  // set as const to prevent accidental changes
  // pass by reference to prevent copying
  void setName(const string& newFirstName, const string& newLastName);

  // function to set a users first name
  // set as const to prevent accidental changes
  // pass by reference to prevent copying
  void setFirstName(const string& newFirstName);

  // function to set a users last name
  // set as const to prevent accidental changes
  // pass by reference to prevent copying
  void setLastName(const string& newLastName);

  // function to set a users user ID
  // set as const to prevent accidental changes
  // pass by reference to prevent copying
  void setUserID(const string& newUserID);

  // fucntion to set a users email
  void setEmail(const string& newEmail);

  // function to print a users info to the screen
  virtual void print(ostream& os) const;

  // function to read a users info from a file
  virtual void read(ifstream& is);

  // overloaded operators for comparison between two Person objects
  bool operator==(const Person& rhs) const;
  bool operator!=(const Person& rhs) const;
  bool operator<(const Person& rhs) const;
  bool operator>(const Person& rhs) const;
  bool operator<=(const Person& rhs) const;
  bool operator>=(const Person& rhs) const;

  // overloaded operators for assignment between two Person objects
  Person& operator=(const Person& rhs);

  // overloaded operators for input and output for accessors and mutators
  friend ostream& operator<<(ostream& os, const Person& rhs);
  friend istream& operator>>(istream& is, Person& rhs);

protected:
  // putting user data in protected so that it can be accessed by
  // the derived classes

  // variable to hold the first name
  string firstName;

  // variable to hold the last name
  string lastName;

  // variable to hold ID
  string userID;

  // email
  string email;
};

#endif // CS2170_PERSON_H
