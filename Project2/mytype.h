//
// Created by dlpon on 9/9/2022.
//

#ifndef CS2170_MYTYPE_H
#define CS2170_MYTYPE_H
// define the enum type for card suits here
// also define the card struct type here

// enum type to hold face values of cards
enum suitType { DIAMOND, CLUB, HEART, SPADE };


// struct to hold the card info
struct CardStruct {
  suitType suit; // enum type to hold the suit of the card
  int value; // int to hold the value of the card
  int points;  // int to hold the points of the card
};
#endif // CS2170_MYTYPE_H
