//
// Created by dlpon on 11/6/2022.
//
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <cassert>
#include "mazeClass.h"
#include "creatureClass.h"
using namespace std;

// function prototypes
void GoNorth(MazeClass &maze, CreatureClass &creature, bool &success);
void GoSouth(MazeClass &maze, CreatureClass &creature, bool &success);
void GoEast(MazeClass &maze, CreatureClass &creature, bool &success);
void GoWest(MazeClass &maze, CreatureClass &creature, bool &success);


// function to move the creature north recursively
void GoNorth(MazeClass &maze, CreatureClass &creature, bool &success)
{
  // get the current location of the creature and store it in a coordinate
  coordinate tmpPosition = creature.ReportLocation();

  // move the creature north by decrementing the row
  tmpPosition.row--;

  // if the new location is in the maze and is clear, move the creature
  if(maze.IsClear(tmpPosition) && maze.InMaze(tmpPosition) && !maze.IsVisited(tmpPosition))
  {
    // move the creature up
        creature.MoveUp();
        tmpPosition = creature.ReportLocation();  // update the position

        // mark the location as part of the path
        maze.MarkPath(tmpPosition);

        // if at exit, set success to true
        if(maze.IsExit(tmpPosition))
        {
          success = true;
        }
        // else if not at exit, call GoNorth
        else
        {
          GoNorth(maze, creature, success);
          if(!success)
          {
            GoWest(maze, creature, success);
                if(!success)
                {
                  GoEast(maze, creature, success);
                  if(!success)
                  {
                    // mark the location as visited
                        maze.MarkVisited(tmpPosition);

                        // backtrack by moving the creature down
                        // creature.MoveDown();
                        GoSouth(maze, creature, success);
                  }
                }
          }
        }


  }
  else
  {
    success = false;
  }


}

// function to move the creature south recursively
void GoSouth(MazeClass &maze, CreatureClass &creature, bool &success)
{
  // get the current location of the creature and store it in a coordinate
  coordinate tmpPosition = creature.ReportLocation();

  // move the creature south by incrementing the row
  tmpPosition.row++;

  // if the new location is in the maze and is clear, move the creature
  if(maze.IsClear(tmpPosition) && maze.InMaze(tmpPosition) && !maze.IsVisited(tmpPosition))
  {
    // move the creature down
        creature.MoveDown();
        tmpPosition = creature.ReportLocation();  // update the position

        // mark the location as part of the path
        maze.MarkPath(tmpPosition);

        // if at exit, set success to true
        if(maze.IsExit(tmpPosition))
        {
          success = true;
        }
        // else if not at exit, call GoSouth
        else
        {
          GoSouth(maze, creature, success);
          if(!success)
          {
            GoWest(maze, creature, success);
                if(!success)
                {
                  GoEast(maze, creature, success);
                  if(!success)
                  {
                    // mark the location as visited
                        maze.MarkVisited(tmpPosition);

                        // backtrack by moving the creature up
                        // creature.MoveUp();
                        GoNorth(maze, creature, success);
                  }
                }
          }
        }


  }
  else
  {
    success = false;
  }
}

// function to move the creature east recursively
void GoEast(MazeClass &maze, CreatureClass &creature, bool &success)
{
  // get the current location of the creature and store it in a coordinate
  coordinate tmpPosition = creature.ReportLocation();

  // move the creature east by incrementing the column
  tmpPosition.col++;

  // if the new location is in the maze and is clear, move the creature
  if(maze.IsClear(tmpPosition) && maze.InMaze(tmpPosition) && !maze.IsVisited(tmpPosition))
  {
    // move the creature right
        creature.MoveRight();
        tmpPosition = creature.ReportLocation();  // update the position

        // mark the location as part of the path
        maze.MarkPath(tmpPosition);

        // if at exit, set success to true
        if(maze.IsExit(tmpPosition))
        {
          success = true;
        }
        // else if not at exit, call GoEast
        else
        {
          GoEast(maze, creature, success);
          if(!success)
          {
            GoNorth(maze, creature, success);
                if(!success)
                {
                  GoSouth(maze, creature, success);
                  if(!success)
                  {
                    // mark the location as visited
                        maze.MarkVisited(tmpPosition);

                        // backtrack by moving the creature left
                        // creature.MoveLeft();
                        GoWest(maze, creature, success);
                  }
                }
          }
        }


  }
  else
  {
    success = false;
  }
}

// function to move the creature west recursively
void GoWest(MazeClass &maze, CreatureClass &creature, bool &success)
{
  // get the current location of the creature and store it in a coordinate
  coordinate tmpPosition = creature.ReportLocation();

  // move the creature west by decrementing the column
  tmpPosition.col--;

  // if the new location is in the maze and is clear, move the creature
  if(maze.IsClear(tmpPosition) && maze.InMaze(tmpPosition) && !maze.IsVisited(tmpPosition))
  {
    // move the creature left
        creature.MoveLeft();
        tmpPosition = creature.ReportLocation();  // update the position

        // mark the location as part of the path
        maze.MarkPath(tmpPosition);

        // if at exit, set success to true
        if(maze.IsExit(tmpPosition))
        {
          success = true;
        }
        // else if not at exit, call GoWest
        else
        {
          GoWest(maze, creature, success);
          if(!success)
          {
            GoNorth(maze, creature, success);
                if(!success)
                {
                  GoSouth(maze, creature, success);
                  if(!success)
                  {
                    // mark the location as visited
                        maze.MarkVisited(tmpPosition);

                        // backtrack by moving the creature right
                        // creature.MoveRight();
                        GoEast(maze, creature, success);
                  }
                }
          }
        }


  }
  else
  {
    success = false;
  }
}

// function to solve the maze
void SolveMaze(MazeClass &maze, CreatureClass &creature)
{
  // declare a boolean variable to indicate if the maze has been solved
  bool success = false;

  // call the recursive function to solve the maze
  GoNorth(maze, creature, success);

  // if the maze was solved, display a message
  if(success)
  {
    cout << "The maze was solved!" << endl;
  }
  // else if the maze was not solved, display a message
  else
  {
    cout << "The maze was not solved." << endl;
  }
}

int main()
{
  // create a creature object
  CreatureClass theseus;

  // create a maze object
  MazeClass labyrinth;

  // boolean to indicate if the maze was solved
  bool success = false;

  // variable to hold the file
  ifstream inFile;

  // variable to hold user input
  string fileName;

  // prompt the user to enter the maze file name
  cout << "Enter the name of the maze file: ";
  cin >> fileName;

// read the maze from the file
  inFile.open(fileName.c_str());
  labyrinth.ReadMaze(inFile);

  // display the maze
  labyrinth.DisplayMaze();

  // solve the maze
  SolveMaze(labyrinth, theseus);

  // display the maze
  labyrinth.DisplayMaze();

  return 0;
}


