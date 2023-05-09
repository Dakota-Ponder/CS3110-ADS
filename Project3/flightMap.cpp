#include "flightMap.h"
#include <iostream>
#include <fstream>
#include <cstddef>
#include <cassert>
#include <iomanip>
using namespace std;

FlightMapClass::FlightMapClass()
{
  size = 0;
  map = NULL;
}

// copy constructor
FlightMapClass::FlightMapClass(const FlightMapClass& f)
{
  int i;				//loop index

  //copy the size
  size = f.size;

  //dynamic allocation for 1D array

  //copy the cities
  for(i=0; i<size; i++)
    cities.push_back(f.cities[i]);

  //dynamic allocation
  map = new list<flightRec> [size];

  //copy the flight map
  for(i=0; i<size; i++)
    map[i]=f.map[i];
}

FlightMapClass::~FlightMapClass()
{
  delete [] map;
}

void FlightMapClass::ReadCities(ifstream& myCities)
{
  string tempCity;		//holds the city name temporarily
  int i,j,k;				//loop index

  myCities >> size;

  for(i=0; i<size; i++)
  {
    myCities >> tempCity; // read a city name
    cities.push_back(tempCity);  // add the city name to the vector
  }
}

void FlightMapClass::BuildMap(ifstream& myFlights)
{
  int flightNum, price;		//holds the flightNum and price from a data file
  string origin, destination;	//holds the cities info from a data file
  flightRec temp;				//holds the data temporarily
  bool success;				//whether the insertion is successful or not

  map = new list<flightRec> [size];  // dynamic allocation

  //Reading info from a data file
  while(myFlights >> flightNum >> origin >> destination >> price)
  {
    temp.flightNum = flightNum;
    temp.origin = origin;
    temp.destination = destination;
    temp.price = price;

    //This for loop traverse the cities list
    //and look for the city that matches with the current
    //record's origin city
    for(int i=0; i<size; i++)
    {
      //if found the city that matches,
      if(temp.origin == cities[i])
      {
        //then insert the current record
        //and link it with the current city
        map[i].push_back(temp);
      }
    }
  }

  for (int i=0; i<size; i++)
    map[i].sort();  // use the overloaded < operator in the sort
}

void FlightMapClass::DisplayMap()
{
  list<flightRec> currList;		//holds the current city's list
  flightRec currFlight;			//holds the current flight info

  //Display the heading
  cout << setw(19) << "Origin" << setw(21) << "Destination"
       << setw(8) << "Flight" << setw(7) << "Price" << endl;
  cout << "========================================================" << endl;

  //This for loop is used to display the entire flight map
  for(int i=0; i<size; i++)
  {
    //if the origin city has no flight at all,
    //then skip the city
    if(map[i].size() == 0)
      continue;
    else
    {
      //Display origin city
      cout << " From " << setw(13) << cities[i] << " to:";

      currList = map[i];
      int j=0;
      list<flightRec>::iterator k;
      for(k=map[i].begin(); k!=map[i].end(); k++)
      {
        //currFlight is the current record in the list
        currFlight = *k;


        //Using different method to display in a tabular format
        if(j==0)
        {
          cout << setw(17) << currFlight.destination
               << setw(8) << currFlight.flightNum
               << setw(4) << "$" << setw(3) << currFlight.price
               << endl;
          j++;
        }
        else
        {
          cout << setw(40) << currFlight.destination
               << setw(8) << currFlight.flightNum
               << setw(4) << "$" << setw(3) << currFlight.price
               << endl;
        }
      }
    }
  }
}