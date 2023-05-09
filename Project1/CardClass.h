#include <iostream>
#include <vector>

#ifndef CARDCLASS_H
#define CARDCLASS_H


#include "cardtype.h"
//using std::ostream;
using namespace std;

class CardClass {
private:
  // constant for the deck array
  static const int SIZE = 52;

  // count variable to track remaining cards in the deck
  int count;

  // variable to keep the index of the top card
  int topCard;

public:
  CardClass();
  // Default constructor

  // deck of cards implemented in terms of an array of 52 cards
  CardType deck[SIZE]{};

  // randomizes the 52 cards
  void ShuffleCards();

  // Sort the cards using bubble sort or selection sort
  //void SortCards(CardType deck[], int size);

  // use linear search to find the player who has 2 of Clubs
  // return -1 if not found
  static int SearchCards(CardType players[], int size);

  // deals out one card when card
  // also removes 1 card from the deck
  CardType DealCard();

  // returns the number of cards currently in the deck
  int GetSize();

  // returns whether or not the deck is empty
  bool IsEmpty();

  //void PrintCards(CardType deck[], int size);

};
#endif