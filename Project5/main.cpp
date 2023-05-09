/********************************************************************
* FILE: main.cpp
* DUE DATE: Monday, October 28th
* PURPOSE: This program allows a user to login to a system, and add and edit
*          the sellers list and users list.
* INPUTS:  The user enters various strings, doubles, and integers to insert
*          into Product, Seller, and PowerSeller objects.
* EXPECTATIONS: The program should correctly insert, remove, and access
*               items from SortedList objects.
* LIMITATIONS:  none.
********************************************************************/

/********************************************************************
* File: main.cpp
* Contents: implementation of Main Menu and main function
*
********************************************************************/

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <list>
#include "Person.h"
#include "Seller.h"
#include "PowerSeller.h"
using namespace std;

// Function Prototypes
void PrintSellers(const list<Seller *>& sellers);
void CheckSeller(const list<Seller*>& sellers);
void GetSellers(const string& database, list<Seller *>& sellers);
void DisplayMenu();
void RemoveSeller(list<Seller*> &sellers);
void AddSeller(list<Seller*> & sellers);

int main()
{
  // containers for sellers
  list<Seller *> allSellers;  // list of seller class pointers
  int choice;              // user's menu choice
  string firstname;        // user's first name
  string lastname;         // user's last name
  bool done = false;       // flag to exit the program

  // read in sellers
  GetSellers("sellers.dat", allSellers);
  cout << "Reading in the sellers now. " << endl;


  while(!done)  // while bool == true
  {
    // display menu
    DisplayMenu();

    // get user's choice from menu
    cin >> choice;

    // switch statement to handle user's choice
    switch(choice)
    {
      // case 1: print all seller info
    case 1: PrintSellers(allSellers);
      break;

      // case 2: check seller info
    case 2: CheckSeller(allSellers);
      break;

      // case 3: add a seller
    case 3: AddSeller(allSellers);
      break;

      // case 4: remove a seller
    case 4: RemoveSeller(allSellers);
        break;

        // case 5: exit the program
    case 5: done = true; // set bool to false
      break;

    }
      return 0;
  }


  return 0;
}

// function to print all sellers in the list
void PrintSellers(const list<Seller *> &allSellers)
{
  // iterator to traverse the list
  list<Seller *> :: const_iterator iter;  // iterator as a constant because we are not changing the list

  // for loop to loop through the list and print the sellers
  for(iter = allSellers.begin(); iter != allSellers.end(); iter++)
  {
    // print the seller using the print function in the Seller class
    // dereference the iterator to get the pointer to the Seller object
    (*iter)->print(cout);
  }
}


// function to check if seller is in the list
void CheckSeller(const list<Seller *> &allSellers)
{
  // variable to hold the name of the seller needing to be checked
  string firstname;
  string lastname;

  // variables to hold the sellers name if it is found in the list
  string first, last;

  // iterator to traverse the list
  list<Seller *> :: const_iterator iter;

  // get the name of the seller to be checked
  cout << "Enter the first name of the seller: ";
  cin >> firstname;

  // get the last name of the seller to be checked
  cout << "Enter the last name of the seller: ";
  cin >> lastname;

  // for loop to loop through the list and check if the seller is in the list
  for(iter = allSellers.begin(); iter != allSellers.end(); iter++)
  {
    first = (*iter)->getFirstName();  // get the first name of the seller
    last = (*iter)->getLastName();  // get the last name of the seller

    // if the seller is in the list, print the seller's info
    if(first == firstname && last == lastname)
    {
      (*iter)->print(cout);
      break;
    }
  }
}

// function to read in sellers from a file
// and add them to the list depending on seller type
void GetSellers(const string &database, list<Seller *> &allSellers)
{
  ifstream infile;  // input file stream of sellers

  // open the file
  infile.open(database.c_str());  // open the file and convert to c-string

  // while loop to read in sellers until end of file
  while(!infile.eof())
  {
    string space; // string to hold the space between first and last name
    getline(infile, space);

    // if the first character is a S, then it is a Seller
    if(space[0] == 'S')
    {
      Seller * sptr;
      sptr = new Seller; // create a new Seller object
      sptr->read(infile);            // read in the Seller object
      allSellers.push_back(sptr);    // add the Seller object to the list of sellers
    }
    else if(space[0] == 'P')
    {
      PowerSeller * psptr;  // pointer to PowerSeller
      psptr = new PowerSeller;  // allocate space for object
      psptr->read(infile);  // read in the Powerseller object from the input file
      allSellers.push_back(psptr);  // add the Powerseller object to the list of sellers
    }
    else if(space != "")
    {
      cout << "Error reading in the sellers.dat file. " <<
                  "Please check the file and try again. " << endl;
    }
  }
  infile.close();  // close the file
}

void DisplayMenu()
{
  cout << "Please choose from the following menu: " << endl;
  cout << "1. Print all seller information. " << endl;
  cout << "2. Check information of one seller. " << endl;
  cout << "3. Add a seller. " << endl;
  cout << "4. Remove a seller. " << endl;
  cout << "5. Quit. " << endl;
  cout << endl;
  cout << "Enter your choice: ";
}

// function to remove a seller from the list
// behaves almost like the CheckSeller function
// except it removes the seller from the list
void RemoveSeller(list<Seller *> &allSellers)
{
  // variable to hold the name of the seller needing to be removed
  // names provided by the user
  string firstname, lastname;

  // variables to hold the sellers name if it is found in the list
  string first, last;

  // iterator to traverse the list of sellers
  // iterator is not constant because we are changing the list of sellers
  list<Seller *> :: iterator iter;

  // get the name of the seller to be removed
  cout << "Enter the first name of the seller: ";
  cin >> firstname;

  // get the last name of the seller to be removed
  cout << "Enter the last name of the seller: ";
  cin >> lastname;

  // loop through the list of sellers and check if the seller is in the list
  for(iter = allSellers.begin(); iter != allSellers.end(); iter++)
  {
    first = (*iter)->getFirstName();  // get the first name of the seller
    last = (*iter)->getLastName();  // get the last name of the seller

    // if the seller is in the list, remove the seller from the list
    if(first == firstname && last == lastname)
    {
      // remove seller from the list using the erase function and iter as the parameter
      allSellers.erase(iter);
      break;
    }
  }
}

// function to add a seller to the list
void AddSeller(list<Seller *> &allSellers)
{
  string space;  // string to hold the seller type
  Seller * sptr;  // pointer to Seller object
  PowerSeller * psptr;  // pointer to PowerSeller object

  // prompt the user to enter the seller type
  cout << "Please enter the following information (enter invalid type to quit): "
          << endl;
  cout << "Is the seller a (S)eller or a (P)ower Seller? ";

  // get the seller type using getline
  getline(cin, space);
  cin.ignore(100, '\n');  // ignore the rest of the line

  // switch statement to check the seller type
  switch(space[0])
  {
  case 'S':
  case 's':
    sptr = new Seller;  // allocate space for Seller object
    cin >> *sptr;  // read in the seller object
    allSellers.push_back(sptr); // add the seller object to the list of sellers

    cout << "\nThe new seller has been added . Returning to Seller management...\n\n";

    break;
  case 'P':
  case 'p':
    psptr = new PowerSeller;  // allocate space for PowerSeller object
    cin >> *psptr;  // read in the PowerSeller object
    allSellers.push_back(psptr);  // add the PowerSeller object to the list of sellers

    cout << "\nThe new seller has been added . Returning to Seller management...\n\n";

    break;

    // default statement to handle invalid input
  default:
    cout << "\nInvalid seller type. Returning to Seller management...\n\n";
    break;
  }
}

