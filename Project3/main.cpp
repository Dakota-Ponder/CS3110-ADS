#include "flightMap.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
  FlightMapClass map, map1;
  ifstream myCities("cities.dat");
  ifstream myFlights("flights.dat");

  //Read cities from a data file
  map.ReadCities(myCities);

  //Read flight informations from a data file and build a flight map
  map.BuildMap(myFlights);

  //Display the entire map
  map.DisplayMap();

  return 0;
}