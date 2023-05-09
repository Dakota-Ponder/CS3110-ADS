//
// A Maze object consists of a maze (2D array of character), the total
// number of rows and columns of the maze, and the entrance and exit locations of the maze.
//


#ifndef CS2170_MAZECLASS_H
#define CS2170_MAZECLASS_H

#include "creatureClass.h"
#include <iostream>
#include <fstream>
using namespace std;

class MazeClass
{ public:
  MazeClass();
  ~MazeClass();
  void ReadMaze(ifstream&);
  void DisplayMaze();
  bool IsWall(coordinate);
  bool IsClear(coordinate);
  bool IsPath(coordinate);
  bool IsVisited(coordinate);
  bool IsExit(coordinate);
  bool InMaze(coordinate);
  void MarkPath(coordinate);
  void MarkVisited(coordinate);
  coordinate GetEntrance();

  // overloaded >> extraction operator to read the maze from a file
  friend ifstream& operator>>(ifstream&, MazeClass&);

private:
  // 2D array of characters to store the maze of size 20x20
  SquareType **Maze;  // pointer to an array of pointers
  coordinate entrance, Exit;
  int height, width;
};


#endif // CS2170_MAZECLASS_H
