#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include "parameters.h"
using namespace std;

// Constants
const int MAX_ROWS = 50;
const int MAX_COLS = 50;

// Function prototypes
int Fibonacci(int n);
int Sum(int n);
int Largest(int arr[], int lower, int upper);
int FindEagle(int grid[][MAX_COLS], int rows, int cols);
void DisplayGrid(int grid[][MAX_COLS], int rows, int cols);


int main()
{

  Largest(const_cast<int *>(LargestVal), 0, 12);


  int eagle;  // varaible to hold the eagle's location
  int grid[MAX_ROWS][MAX_COLS];  // 2D array to hold the grid
  int i, j;  // loop variables
  int row, column;  // variables to hold the number of rows and columns

  ifstream myin;
  string filename;

  // open the file and check if it opened
  myin.open("eagle.dat");

  myin >> row >> column; // read the number of rows and columns

  while (!myin.eof()) // while input was successful
  {

    // read the grid
    // boundary is set to 0
    for (i = 0; i < row; i++)
      for (j = 0; j < column; j++)
        myin >> grid[i][j];

    // display the grid
    DisplayGrid(grid, row, column);



    // count the eagles in the grid
    eagle = 0;   // initialize the eagle counter to 0

    // nested for loop to iterate through the grid
    for (i = 0; i < row; i++)
      for (j = 0; j < column; j++) {

        // if the current cell is a possible int for an eagle
        if (grid[i][j] > 0) {

          // increment the eagle counter
          eagle++;

          // call the FindEagle function to find the eagles in the grid
          int s = FindEagle(grid, i, j);

          // output the number of eagles found
          cout << "An eagle size " << s << " is found.\n";
        }
      }

    // output the total number of eagles found
    cout << "\n" << eagle << " eagle(s) found in the picture.\n\n\n";

    myin >> row >> column; // read the grid size for the next grid in the file
  }

  return 0;
}


// Function that computes the nth number of fibonacci series
// If fibonacci(0) = 0, fibonacci(1) = 1
int Fibonacci(int n)
{
  // Base case: if n <= 1, return n. n will either be a 0 or a 1
  if(n <= 1)
  {
    return n;
  }
  else
    return Fibonacci(n - 2) + Fibonacci(n - 1);
}

// Function that computes the sum of the first n numbers for a given number n
// Sum(6) should return 21
// Recurrence relation: sum(n) = n + sum(n - 1)
int Sum(int n)
{
  // Base case: if n <= 1 return n
  if(n <= 1) {
    return n;
  }
  else
    return n + Sum(n -1);
}

// a recursive function that computes the largest number in an array
// recurrence relation is: n + (n - 1) + (n - 2) + ... + 1
// where n is the size of the array
// lower is the lower bound of the array
// upper is the upper bound of the array
int Largest(int arr[], int first, int last)
{
  int value, currentLargest;

  // Base case: if lower == upper and arr[lower] > 0, return 1 (base case)
  if(first == last)
  {
    return arr[first];
  }
  else

    // value is assigned the current index of the array (arr[first])
    value = arr[first];

    //  currentLargest is assigned the largest number in the array
    currentLargest = Largest(arr, first + 1, last);

    if(value > currentLargest)
    {
      return value;
    }
    else
      return currentLargest;
}


// Function that counts the number of objects in a photograph
// Data is in a 2D grid of cells with 0 for empty and 1 - 9 for filled
// Two cells are connected if they are adjacent horizontally, vertically, or diagonally
// The following shows a 3 x 4 grid with 3 eagles
// 0 0 1 2
// 1 0 0 0
// 1 0 3 1
// FindEagle function takes parameters of a 2D array, xy coordinates of a cell that
// is part of an eagle and erases the image of an eagle
// Returns an int value that counts how many cells have been counted as part of an eagle
// and have been erased
// Recurrence relation: findEagles(arr, x, y) = 1 + findEagles(arr, x, y + 1) + findEagles(arr, x, y - 1)
int FindEagle(int grid[][MAX_COLS],int startRow, int startCol)
{

  int size = 0;  // size of the eagle

  // Base case: if grid[startRow][startCol] == 0, return 0
  if(grid[startRow][startCol] == 0) {
    return 0;
  }
  else
  {
    // else if not zero, there is an eagle, so increment size
    size++;

    // erase the cell
    grid[startRow][startCol] = 0;

    // recursively call the function to check the cells above, below, left, and
    // right you have to call it 8 times to fully check
    size += FindEagle(grid, startRow - 1, startCol);     // check the cell above
    size += FindEagle(grid, startRow + 1, startCol);     // check the cell below
    size += FindEagle(grid, startRow, startCol - 1);     // left
    size += FindEagle(grid, startRow, startCol + 1);     // right
    size += FindEagle(grid, startRow - 1, startCol - 1); // upper left
    size += FindEagle(grid, startRow - 1, startCol + 1); // upper right
    size += FindEagle(grid, startRow + 1, startCol - 1); // lower left
    size += FindEagle(grid, startRow + 1, startCol + 1); // lower right
  }
  // return the size of the eagle
  return size;
}

// Function that displays the grid
void DisplayGrid(int grid[][MAX_COLS], int rows, int cols)
{
  int i, j;

  for (i = 0; i < rows; i++)
  {
    for (j = 0; j < cols; j++)
      cout << grid[i][j] << " ";
    cout << endl;
  }
}
