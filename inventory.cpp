#include <iostream>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;

struct bin
{
  string description;
  int numberOfParts;
};

// Function prototypes
void Display (bin binArray[], int index);
void RemoveParts (bin binArray[], int index, string desc, int number);
void AddParts (bin binArray[], int index, string desc, int number);

const int SIZE = 10;

int main ()
{
  // Array of size 10 of type struct bin
  bin binArray[SIZE];

  // Index variable to use as a counter for the items in binArray[]
  int index = 0;

  ifstream myIn1 ("../inventory.dat");
  string line;
  string desc = "";

  int number = 0;
  bool flag = false;

  // Read file as long as there are lines to read
  while (getline (myIn1, line))
  {
    // Conditional statement to filter the part descriptions from the part numbers
    if (flag == false)
    {
      desc = line;
      flag = true;
    }
    else
    {
      // Used since the number is really a string
      istringstream iss (line);
      iss >> number;
      flag = false;

      // Add the description and number of parts in binArray[] at index
      binArray[index].description = desc;
      binArray[index].numberOfParts = number;
      index++;
    }
  }

  cout << "Warehouse inventory before the operations\n\n" << endl;

  Display (binArray, index);

  // Opening operations file
  ifstream myIn2 ("../operations.dat");
  string operation;
  int lineNumber = 0;

  // Loop through file until last line
  while (getline (myIn2, line))
  {
    if (lineNumber == 0)
    {
      operation = line;
      lineNumber++;
    }
    else if (lineNumber == 1)
    {
      desc = line;
      lineNumber++;
    }
    else
    {
      istringstream iss (line);
      iss >> number;
      if (operation == "Add")
      {
        AddParts (binArray, index, desc, number);
      }
      else
      {
        RemoveParts (binArray, index, desc, number);
      }
      lineNumber = 0;
    }
  }
  cout << "\n\nWarehouse inventory after the operations\n\n" << endl;

  Display (binArray, index);
  return 0;
}

// Function to display the table of parts in two columns
void Display (bin binArray[], int index)
{
  cout << "Part \t\tQuantity\n\n" << endl;

  // Loop through the array and display each element
  for (int i = 0; i < index; i++)
  {
    cout << setw (20) << left;
    cout << binArray[i].description;
    cout << setw (10) << left;
    cout << binArray[i].numberOfParts << endl;
  }
}

// Funtion that increases the specific bins part count by a specicficied number
void AddParts (bin binArray[], int index, string desc, int number)
{
  // Loop through the array
  for (int i = 0; i < index; i++)
  {
    if (binArray[i].description == desc)
    {
      binArray[i].numberOfParts += number;
      break;
    }
  }
}

// Function that decreases the specific bins part count by a specified number
void RemoveParts (bin binArray[], int index, string desc, int number)
{
  for (int i = 0; i < index; i++)
  {
    if (binArray[i].description == desc)
    {
      if (binArray[i].numberOfParts - number > 0)
      {
        binArray[i].numberOfParts -= number;
      }
      else
      {
        // Do nothing
      }
      break;
    }
  }
}
