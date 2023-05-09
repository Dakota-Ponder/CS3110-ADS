//
// Created by dlpon on 11/6/2022.
//

#include "mazeClass.h"
#include "creatureClass.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <iomanip>
#include <sstream>
#include <stack>
using namespace std;

// constructor to initialize the 2D array of characters of type SquareType
MazeClass::MazeClass()
{
  // allocate memory for the 2D array of characters
  Maze = new SquareType*[20];
  for(int i = 0; i < 20; i++)
  {
    Maze[i] = new SquareType[20];
  }
}

// destructor
MazeClass::~MazeClass()
{
  // deallocate memory for the 2D array of characters
  for(int i = 0; i < 20; i++)
  {
    // delete the array of characters
    delete [] Maze[i];
  }
  // delete the array of pointers
  delete [] Maze;
}

// function to read a file a 2d array with dynamic allocation
// input file looks like this:
// 20 7 《--size of the maze number of columns number of rows
// 0 18 《-- the coordinates of the entrance point
// 6 12 《--the coordinates of the exit point
//****************** *
//* * ***** *
//* ***** *** *
//* ***** ***** ** *
//* * * *
//* ******* * *
//************ *******
void MazeClass::ReadMaze(ifstream &inFile) {
  // read the size of the maze
  inFile >> width >> height;

  // read the coordinates of the entrance and exit
  inFile >> entrance.col >> entrance.row;
  inFile >> Exit.col >> Exit.row;


  // read the maze from the file
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      // inFile >> Maze[i][j];
      char ch; // temporary variable to read the character from the file
      inFile >> ch;
      if (ch == '*') {
        Maze[i][j] = Wall;
      } else if (ch == ' ') {
        Maze[i][j] = Clear;
      } else {
        Maze[i][j] = Visited;
      }
    }
  }
}

// function to display the 2d array that was read in from the file
  // the display should look like this:
  //****************** *
  //* * ***** *
  //* ***** *** *
  //* ***** ***** ** *
  //* * * *
  //* ******* * *
  //************ *******
void MazeClass::DisplayMaze()
{
        // display the maze
        for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
        if (Maze[i][j] == Wall) {
                cout << "*";
        } else if (Maze[i][j] == Clear) {
                cout << " ";
        } else if (Maze[i][j] == Visited) {
                cout << ".";
        } else if (Maze[i][j] == Path) {
                cout << "+";
        }
        }
        cout << endl;
        }
}

// function to check if the location is a wall
bool MazeClass::IsWall(coordinate loc)
{
  // if the location is a wall, return true
  if(Maze[loc.row][loc.col] == Wall)
  {
    return true;
  }
  // if the location is not a wall, return false
  else
  {
    return false;
  }
}

// function to check if the location is clear
bool MazeClass::IsClear(coordinate loc)
{
  // if the location is clear, return true
  if(Maze[loc.row][loc.col] == Clear)
  {
    return true;
  }
  // if the location is not clear, return false
  else
  {
    return false;
  }
}

// function to check if the location is a path
bool MazeClass::IsPath(coordinate loc)
{
  // if the location is a path, return true
  if(Maze[loc.row][loc.col] == Path)
  {
    return true;
  }
  // if the location is not a path, return false
  else
  {
    return false;
  }
}

// function to check if the location is visited
bool MazeClass::IsVisited(coordinate loc)
{
  // if the location is visited, return true
  if(Maze[loc.row][loc.col] == Visited)
  {
    return true;
  }
  // if the location is not visited, return false
  else
  {
    return false;
  }
}

// function to check if the location is the exit
bool MazeClass::IsExit(coordinate loc)
{
  // if the location is the exit, return true
  if(loc.row == Exit.row && loc.col == Exit.col)
  {
    return true;
  }
  // if the location is not the exit, return false
  else
  {
    return false;
  }
}

// function to check if the location is in the maze
bool MazeClass::InMaze(coordinate loc)
{
  // if the location is in the maze, return true
  if(loc.row >= 0 && loc.row < height && loc.col >= 0 && loc.col < width)
  {
    return true;
  }
  // if the location is not in the maze, return false
  else
  {
    return false;
  }
}

// function to mark the location as a path
void MazeClass::MarkPath(coordinate loc)
{
  // set path as the char 'p' at the location

  // mark the location as a path
  Maze[loc.row][loc.col] = Path;
}

// function to mark the location as visited
void MazeClass::MarkVisited(coordinate loc)
{
  // set visited as the char 'v' at the location

  // mark the location as visited
  Maze[loc.row][loc.col] = Visited;
}

// function to get the entrance location
coordinate MazeClass::GetEntrance()
{
  // return the entrance location
  return entrance;
}



/*/ function to get the exit location
coordinate MazeClass::GetExit()
{
  // return the exit location
  return Exit;
}*/



