#include <iostream>
#include <fstream>

#ifndef FLIGHTMAPCLASS_H
#define FLIGHTMAPCLASS_H

#include "type.h"
#include <list>
#include <vector>

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

private:
  int size;                 //number of cities in the map
  vector<string> cities;    //vector of cities of type string
  list<flightRec>* map;     //flight map adjacency list
};

#endif
