#include "CardClass.h"
//#include <bits/stdc++.h>
#include <ctime>
#include <iostream>
// #include "cardtype.h"
using namespace std;
// header file for the CardClass

// function prototypes
void SortCards(CardType deck[], int size);

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
      CardSuitType suit = static_cast<CardSuitType>(i);
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

      CardType card = {suit, value, points};
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
  CardType temp;

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
CardType CardClass::DealCard()
{
  if (IsEmpty())
  {
    cout << "Deck is Empty" << endl;
    CardType card = {CLUB, -1, 0};

    return card[topCard];
  }

  CardType card = deck[topCard++];
  count--;

  // cout<<card.suit<<","<<card.value<<","<<card.points<<endl;

  return card;
}

// function that compares cards
bool compare(CardType A, CardType B) {
  return (A.suit < B.suit) || (A.suit == B.suit && A.value < B.value);
}

/*
// displays the cards in one players hands
void CardClass::PrintCards(CardType deck[], int size)
{



  // array to hold the card values as string types
  string values[] = {"0", "1", "2",  "3", "4", "5", "6", "7",
                     "8", "9", "10", "J", "Q", "K", "A"};

  for(int i = 0 ; i <= 4; i++)
  {
    cout << "Player " << i << endl;

    cout << "SUIT\tVALUE\tPOINTS" << endl;

    // loop to print out the cards
    for (int i = 0; i < size; i++)
    {
      // variable of type string to hold the suit of the card
      string suit;

      // switch statement to assign the suit of the card
      // based on the enum type value
      switch (deck[i].suit) {
      case CLUB:
        suit = "CLUB";
        break;
      case DIAMOND:
        suit = "DIAMOND";
        break;
      case HEART:
        suit = "HEART";
        break;
      case SPADE:
        suit = "SPADE";
        break;
      }

      // cout statement to print out the card's suit , value , and points
      cout << suit << "\t" << values[deck[i].value] << "\t" << deck[i].points
           << endl;
    }
        cout << endl;
  }
  cout << endl;

  return;
}*/

/*
// sort the cards based on their suit using bubble sort
void CardClass::SortCards(CardType deck[], int size)
{
  // indicates whether additional comparisons are needed
  bool sorted = false;

  // the index of the last element in the array
  int last = size - 1;

  // temp variable of type CardType to hold the temp card
  CardType temp;

  while (!sorted)
  {
    // assuming the remaining array is sorted
    sorted = true;

    // loop through the array
    for (int i = 0; i < last; i++)
    {
      // if the current card is greater than the next card
      if (deck[i].suit > deck[i + 1].suit)
      {
        // swap the cards
        temp = deck[i];
        deck[i] = deck[i + 1];
        deck[i + 1] = temp;

        // set sorted to false because the remaining array is not sorted
        sorted = false;
      }
    }
    // move the last index down by 1
    last--;
  }
  return;
}*/

// search for the 2 of clubs using linear search
int CardClass::SearchCards(CardType player[], int size)
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
