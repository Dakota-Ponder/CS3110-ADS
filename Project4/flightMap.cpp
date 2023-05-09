// THIS CODE WORKS!!!!!!!!

#include "flightMap.h"
#include <cassert>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stack>
using namespace std;

FlightMapClass::FlightMapClass() {
  size = 0;
  map = NULL;
}
// copy constructor
FlightMapClass::FlightMapClass(const FlightMapClass &f) {
  int i; // loop index

  // copy the size
  size = f.size;

  // dynamic allocation for 1D array

  // copy the cities
  for (i = 0; i < size; i++)
    cities.push_back(f.cities[i]);

  // dynamic allocation
  map = new list<flightRec>[size];

  // copy the flight map
  for (i = 0; i < size; i++)
    map[i] = f.map[i];
}

FlightMapClass::~FlightMapClass() { delete[] map; }

void FlightMapClass::ReadCities(ifstream &myCities) {
  string tempCity; // holds the city name temporarily
  int i, j, k;     // loop index

  myCities >> size;

  for (i = 0; i < size; i++) {
    myCities >> tempCity;
    cities.push_back(tempCity);
  }
}

void FlightMapClass::BuildMap(ifstream &myFlights) {
  int flightNum, price;       // holds the flightNum and price from a data file
  string origin, destination; // holds the cities info from a data file
  flightRec temp;             // holds the data temporarily
  bool success;               // whether the insertion is successful or not

  map = new list<flightRec>[size];

  // Reading info from a data file
  while (myFlights >> flightNum >> origin >> destination >> price) {
    temp.flightNum = flightNum;
    temp.origin = origin;
    temp.destination = destination;
    temp.price = price;

    // This for loop traverse the cities list
    // and look for the city that matches with the current
    // record's origin city
    for (int i = 0; i < size; i++) {
      // if found the city that matches,
      if (temp.origin == cities[i]) {
        // then insert the current record
        // and link it with the current city
        map[i].push_back(temp);
      }
    }
  }

  for (int i = 0; i < size; i++)
    map[i].sort(); // use the overloaded < operator in the sort
}

void FlightMapClass::DisplayMap() {
  list<flightRec> currList; // holds the current city's list
  flightRec currFlight;     // holds the current flight info

  // Display the heading
  cout << setw(19) << "Origin" << setw(21) << "Destination" << setw(8)
       << "Flight" << setw(7) << "Price" << endl;
  cout << "========================================================" << endl;

  // This for loop is used to display the entire flight map
  for (int i = 0; i < size; i++) {
    // if the origin city has no flight at all,
    // then skip the city
    if (map[i].size() == 0)
      continue;
    else {
      // Display origin city
      cout << " From " << setw(13) << cities[i] << " to:";

      currList = map[i];
      int j = 0;
      list<flightRec>::iterator k;
      for (k = map[i].begin(); k != map[i].end(); k++) {
        // currFlight is the current record in the list
        currFlight = *k;

        // Using different method to display in a tabular format
        if (j == 0) {
          cout << setw(17) << currFlight.destination << setw(8)
               << currFlight.flightNum << setw(4) << "$" << setw(3)
               << currFlight.price << endl;
          j++;
        } else {
          cout << setw(40) << currFlight.destination << setw(8)
               << currFlight.flightNum << setw(4) << "$" << setw(3)
               << currFlight.price << endl;
        }
      }
    }
  }
}

bool FlightMapClass::CheckCity(string cityName) const {
  // set bool flag to false
  bool found = false;

  // this for loop is used to traverse the cities list
  for (int i = 0; i < size; i++) {
    // if the city is found, then set the flag to true
    if (cityName == cities[i])
      found = true;
  }
  // return if the city is found or not
  return found;
}

void FlightMapClass::DisplayAllCities() const {
  // This for loop prints every cities in cities array
  for (int i = 0; i < size; i++)
    cout << cities[i] << endl;
}

void FlightMapClass::MarkVisited(int city) {
  // Simply set the city being visited to true
  visited[city] = true;
}

void FlightMapClass::UnvisitAll() {
  // This for loop changes all of the boolean values
  // to false in visited array
  if (visited.size() == 0) // check if the vector is empty
  {
    // loop through all the cities
    for (int i = 0; i < size; i++)

      // push back false to the vector
      visited.push_back(false);
  } else

    for (int i = 0; i < size; i++)
      visited[i] = false; // set all the values to false
}

bool FlightMapClass::IsVisited(int city) const {
  // return the boolean value of the city if it has been visited
  return visited[city];
}

bool FlightMapClass::GetNextCity(string fromCity, string &nextCity) {
  list<flightRec> currList; // holds the current city's adj. list
  flightRec currFlight;     // holds the current flight info
  string destCity;          // holds the destination city name to check
  bool success = false;
  list<flightRec>::iterator k; // iterator for the list

  // assign currList to hold the current cities list of flights
  currList = map[GetCityNumber(fromCity)];

  // This for loop searches the unvisited adjacent city
  for (k = currList.begin(); k != currList.end(); k++) {
    // currFlight holds the current flight info in the list
    currFlight = *k;

    // cityNum holds the currFlight's destination city number
    destCity = currFlight.destination;

    // Check if the adjacent city is visited
    if (!visited[GetCityNumber(destCity)]) {
      // if not visited, then set the success flag to true
      success = true;
      break;
    }
  }

  // if success is true
  //  return nextCity to the found city number
  if (success) {
    nextCity = destCity;
  }

  return success;
}

int FlightMapClass::GetCityNumber(string cityName) const {
  int i; // loop index

  // This for loop searches the corresponding cityName
  for (i = 0; i < size; i++) {
    // if cities[i] matches with the cityName
    // then break the loop
    if (cities[i] == cityName)
      break;
  }

  // return the number that matches with the cityName
  //  when the loop is broken
  return i;
}

string FlightMapClass::GetCityName(int cityNumber) const {
  // return the city name that matches with the cityNumber in the array
  return cities[cityNumber];
}

void FlightMapClass::FindPath(string originCity, string destinationCity) {
  stack<string> iteneraryStack; // Stack to hold itinerary for flight
  stack<string> revStack;       // stack to store the itinerary in reverse order
  string topCity,
      nextCity;    // holds the city numbers for the top and next in the stack
  string tempCity; // holds the temporary city name
  bool success;
  int total = 0; // holds the total price, intitialized to 0

  UnvisitAll(); // clear marks on all cities

  // push origin city onto iteneraryStack, mark it visited
  iteneraryStack.push(originCity);
  MarkVisited(GetCityNumber(originCity));

  // Get the origin city, which is just the top of the stack
  topCity = iteneraryStack.top();

  // Loop invariant: the stack contains a directed path
  // from the origin city at the bottom of the stack to the city
  // at the top of the stack
  // find and unvisited city adjacent to the city on the top of the stack
  while (!iteneraryStack.empty() && (topCity != destinationCity)) {

    // set success to store the unvisited city adjacent to the top of the stack
    success = GetNextCity(topCity, nextCity);

    // if there isnt an unvisited city adjacent to the top of the stack
    if (!success)

      // pop the top of the stack, essentially backtracking
      iteneraryStack.pop();

    else // visit city
    {
      // push the next city onto the stack and mark it visited
      iteneraryStack.push(nextCity);
      MarkVisited(GetCityNumber(nextCity));
    }

    // if the stack is not empty, then set the topCity to the top of the stack
    if (!iteneraryStack.empty())
      topCity = iteneraryStack.top();
  }

  // if the stack is empty, then there is no path
  if (iteneraryStack.size() == 0) {
    // no path exists
    cout << "Sorry, EastWest airline does not fly from " << originCity << " to "
         << destinationCity << "." << endl;
  } else // the path exists, so print the path
  {
    list<flightRec> currList; // holds the current city's adj. list
    flightRec currFlight;     // holds the current flight info

    // Print the heading according to Project 4 output format
    cout << "EastWest airline serves between these two cities. " << endl;
    cout << "The flight itinerary is:" << endl;
    cout << "Flight #" << setw(15) << "From" << setw(15) << "To" << setw(7)
         << "Cost" << endl;

    cout << "---------------------------------------------" << endl;

    // Put itinerary in reverse order so that it can be printed
    while (!iteneraryStack.empty()) // while the stack is not empty
    {
      // store the top of the stack in the tempCity so that it can be pushed
      tempCity = iteneraryStack.top();
      iteneraryStack.pop();    // pop the top of the stack
      revStack.push(tempCity); // push the tempCity onto the revStack
    }

    // Get the origin city
    string origin, dest;

    // set the origin to the top of the revStack
    origin = revStack.top();
    revStack.pop(); // remove the top of the stack

    // while the revStack is not empty
    while (!revStack.empty()) {

      // set currList to the list of flights for the origin city
      currList = map[GetCityNumber(origin)];

      // grab the next destination city's number from the stack
      dest = revStack.top();
      revStack.pop(); // remove the top of the stack

      list<flightRec>::iterator iter; // iterator for the list

      // for loop to iterate through the list of flights
      for (iter = currList.begin(); iter != currList.end(); iter++) {

        // currFlight holds the current flight info in the list
        currFlight = *iter;

        // if the currFlight's destination city matches with the dest city
        // number print the corresponding flight info and add the price to the
        // total
        if (currFlight.destination == dest) {
          cout << setw(8) << currFlight.flightNum << setw(15)
               << currFlight.origin << setw(15) << currFlight.destination
               << setw(3) << "$" << setw(4) << currFlight.price << endl;

          // Calculate the total price
          total = total + currFlight.price;

          // Set the origin city's number to
          // current destination city's number
          origin = currFlight.destination;
          break;
        }
      }
    }

    // Print the total price
    cout << "---------------------------------------------" << endl;
    cout << setw(38) << "Total:" << setw(3) << "$" << setw(4) << total << endl;
  }
}