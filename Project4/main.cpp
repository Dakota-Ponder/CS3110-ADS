#include "flightMap.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>
using namespace std;

int main()
{
  // Object of FlightMapClass
  FlightMapClass map;

  // Variables to hold the origin and destination cities
  string originCity, destinationCity;

  // open the cities file
  ifstream myCities("cities.dat");
  ifstream myFlights("flights.dat");
  ifstream myRequests("requests.dat");

  // make sure the files opened
  assert("cities.dat" && "flights.dat" && "requests.dat");

  //Read cities from a data file
  map.ReadCities(myCities);

  //Read flight informations from a data file and build a flight map
  map.BuildMap(myFlights);

  // display the flight map
  map.DisplayMap();

  // while loop that reads the request file info and searches for the flight itenerary
  // if a path is found, it displays the flight itenerary
  // else it displays a message that no flight is available
  while(myRequests >> originCity >> destinationCity)
  {
    cout << "Request is to fly from " << originCity << " to "
         << destinationCity << endl;

    // make sure the airline serves the origin city using CheckCity method
    if(!map.CheckCity(originCity))
    {
      // if the airline does not serve the origin city, display a message
      cout << "Sorry, EastWest Airlines does not serve " << originCity << "."
           <<  endl;
    }
    // check to make sure airline serves the destination city
    else if(!map.CheckCity(destinationCity))
    {
      cout << "Sorry, EastWest Airlines does not serve " << destinationCity
           << "." << endl;
    }
    // otherwise, find the path
    else
    {
      map.FindPath(originCity, destinationCity);
      cout << endl;
    }
  }


  return 0;
}