#include "CardClass.h"
#include "mytype.h"
//#include <bits/stdc++.h>
#include <ctime>
#include <iostream>
// #include "cardtype.h"
using namespace std;
// header file for the CardClass

// function prototypes
void SortCards(CardStruct deck[], int size);

// CardClass();
// Constructor
// Creates the deck of cards as an array of CardType
// Each card is given a value based on its face value
CardClass::CardClass() {

  // counter variable to keep track of index
  int index = 0;

  // loop through the enum type to assign the suit and value
  for (int i = CLUB; i <= SPADE; i++) {
    // another loop to assign values to the cards
    for (int j = 2; j <= 14; j++) {
      suitType suit = static_cast<suitType>(i);
      int value = j;

      int points;

      if (suit == HEART)
      {
        if (value / 10)
          points = 10;
        else
          points = 5;
      }
      else if (suit == SPADE && value == 12)
        points = 100;
      else if (suit == DIAMOND && value == 11)
        points = -100;
      else
        points = 0;

      CardStruct card = {suit, value, points};
      deck[index++] = card;
    }
  }

  topCard = 0;
  count = 52;
}

// randomizes the 52 cards
void CardClass::ShuffleCards() {

  srand(time(0));
  // variable to hold the temp card
  CardStruct temp;

  // loop to shuffle the cards
  for (int i = 0; i < SIZE; i++) {
    int r = i + (rand() % 52);

    // swap the cards
    temp = deck[r];
    deck[r] = deck[i];
    deck[i] = temp;
  }
}

// deals out one card when card
// also removes 1 card from the deck
CardStruct CardClass::DealCard()
{
  if (IsEmpty())
  {
    cout << "Deck is Empty" << endl;
    CardStruct card = {CLUB, -1, 0};

        return card;
  }

  CardStruct card = deck[topCard++];
  count--;

  // cout<<card.suit<<","<<card.value<<","<<card.points<<endl;

  return card;
}

// function that compares cards
bool compare(CardStruct A, CardStruct B) {
  return (A.suit < B.suit) || (A.suit == B.suit && A.value < B.value);
}



// search for the 2 of clubs using linear search
int CardClass::SearchCards(CardStruct player[], int size)
{
  // loop through the array
  for (int i = 0; i < size; i++)
  {
    // if the card is the 2 of clubs
    if (player[i].suit == CLUB && player[i].value == 2)
    {
      // return the index of the card
      return i;
    }
  }
  // if the card is not found
  return -1;
}


// returns the number of cards currently in the deck
int CardClass::GetSize() { return count; }

// returns whether or not the deck is empty
bool CardClass::IsEmpty() { return count == 0; }
