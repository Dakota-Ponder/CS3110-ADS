//
// Header file for the creature that is going to go through the maze
// A creature can move to the north, or the south, or the
// east, or the west one step at a time. It can be assigned to a location,
// and can report its current location. The only data it needs to keep up
// with is its location, or coordinates at all times
//
#ifndef CS2170_CREATURECLASS_H
#define CS2170_CREATURECLASS_H

struct coordinate
{
  int row, col;
};

enum SquareType {Wall, Clear, Visited, Path};
class CreatureClass
{
public:
  CreatureClass();
  ~CreatureClass();
  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();
  void AssignLocation(coordinate);
  coordinate ReportLocation();
private:
  coordinate position;
};


#endif // CS2170_CREATURECLASS_H
