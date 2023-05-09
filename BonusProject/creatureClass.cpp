//
// Created by dlpon on 11/6/2022.
//

#include "creatureClass.h"
#include <iostream>
using namespace std;

// constructor
CreatureClass::CreatureClass()
{
  // set the location of the creature to (0,0)
  position.row = 0;
  position.col = 0;
}

// destructor
CreatureClass::~CreatureClass()
{
  // nothing to do here
}

// function to move the creature up
void CreatureClass::MoveUp()
{
  position.row--;
}

// function to move the creature down
void CreatureClass::MoveDown()
{
  position.row++;
}

// function to move the creature left
void CreatureClass::MoveLeft()
{
  position.col--;
}

// function to move the creature right
void CreatureClass::MoveRight()
{
  position.col++;
}

// function to assign the location of the creature
void CreatureClass::AssignLocation(coordinate loc)
{
  position = loc;
}

//function to report the location of the creature
coordinate CreatureClass::ReportLocation()
{
  return position;
}