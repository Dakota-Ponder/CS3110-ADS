//
// Created by dlpon on 11/11/2022.
//
#include <iostream>
using namespace std;

int main()
{

  // a pointer to an integer pointer
  int** a2d = new int*[5];  // storing 5 pointers

  // loop through the array of pointers and allocate memory for each
  for(int i = 0; i < 5;i++)
  {
    a2d[i] = new int[5]; // creating 5 arrays of 5 integers and storing them in the array of pointers (a2d)
  }

  // to delete the 2d array, you need to delete each array of integers first
  // or you will have a memory leak
  for(int i = 0; i < 5;i++)
  {
    delete [] a2d[i];
  }
  // then delete the array of pointers
  delete [] a2d;


  // or you could use a 2d array like this
  int* array = new int[5 * 5]; // 5 rows, 5 columns

  // to access an element in the 2d array, you need to use the formula
  // array[row * 5 + column]
  for(int row = 0; row < 5; row++)
  {
    for(int col = 0; col < 5; col++)
    {
      array[row * 5 + col] = 0;  // sets the value to 0 for each element in the array
    }
  }

  return 0;
}
