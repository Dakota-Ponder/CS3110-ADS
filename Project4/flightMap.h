#include <iostream>
#include <fstream>

#ifndef FLIGHTMAPCLASS_H
#define FLIGHTMAPCLASS_H

#include "type.h"
#include <list>
#include <vector>
#include <stack>

using namespace std;

class FlightMapClass
{
public:
  //constructors and destructor
  FlightMapClass();  // default constructor


  // copy constructor
  FlightMapClass(const FlightMapClass& f);

  // destructor
  ~FlightMapClass();


  //FlightMapClass operations:

  //Read cities from a data file
  void ReadCities(ifstream& myCities);
  //Pre-condition: Input stream is provided
  //Post-condition: Data file is read
  //				  Cities are in ascending order


  //Reads flight information and build the adjacency list
  void BuildMap(ifstream& myFlights);
  //Pre-condition: list of the flight information is provided
  //Post-condition: Flight map is built


  //Displays the flight map in a formatted table
  void DisplayMap();
  // using overloaded << opererator
  //Pre-condition: none
  //Post-condition: Flight map is displayed

  // methods below this point are added new
  bool CheckCity(string cityName) const;
  // Check whether a city is in the cities that EastWest airline serves.
  // Pre-condition: cityNumber to be checked is provided
  // Post-condition: return true if the city is in the cities array
  //              otherwise return false

  void DisplayAllCities() const;
  // Displays all of the cities

  void MarkVisited(int city);
  // Marks a city as visited
  // Pre-condition: city to be marked as visited is provided
  // Post-condition: a city is marked as visited

  void UnvisitAll();
  // Clears marks on all cities
  // Pre-condition: there are > 0 cities in a cities array
  // Post-condition: all cities marked as unvisited

  bool IsVisited(int city) const;
  // Determines whether a city was visited
  // Pre-condition: city is provided
  // Post-condition: return true if city has been visited
  //              otherwise return false

  bool GetNextCity(string fromCity, string &nextCity) ;
  // Determines the next unvisited city, if any,
  // that is adjacent to a given city.
  // success indicates whether an unvisited adjacent city was found
  // Pre-condition: topCity and nextCity provided
  // Post-condition: return true if an unvisited adjacent city was found
  //              otherwise return false
  int GetCityNumber(string cityName) const;
  // returns the integer index corresponding to a city name
  // Pre-condition: name of a city is provided
  // Post-condition: returns the index number corresponding to a city name

  string GetCityName(int cityNumber) const;
  // returns the name of a city given its corresponding index
  // Pre-condition: number of a city is provided
  // Post-condition: returns the city's name

  void FindPath(string originCity, string destinationCity);
  // Determines whether a sequence of flights between two cities exists.
  // Pre-condition: originCity and destinationCity are the origin and destination city, respectively
  // Post-condition: returns true if a sequence of flights exists
  //              from origin to destination; otherwise return false.
  //              Cities visited during the search are marked as visited
  //              in the flight map.

  // non-recursive algorithm to find the itenerary between two cities
  void IsPath(string originCity, string destinationCity) const;

private:
  int size;                 //number of cities in the map
  vector<string> cities;    //vector of cities of type string
  list<flightRec>* map;     //flight map adjacency list

  vector<bool> visited;     //to check whether a city was visited before
};

#endif
