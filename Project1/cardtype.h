//
// Created by dlpon on 8/27/2022.
//

#ifndef CARDTYPE_H
#define CARDTYPE_H

// CS2170_CARDTYPE_H
// define the enum type for card suits here
// also define the card struct type here

// enum type to hold face values of cards
enum CardSuitType {CLUB, DIAMOND, HEART, SPADE};
//enum CardRankType {ONE, TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JACK,QUEEN,KING, ACE};

// struct to hold the card info
struct CardType
{
  CardSuitType suit;
  int value;
  int points;
};
#endif
