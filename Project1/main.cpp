// if late, give reason and pass # here
/*
 PROGRAMMER:       	Dakota Ponder
 Program Description:
  This program will simulate a cards being dealt in a game of hearts
  Description of what assignment does/produces/performs/....
  Description of what program input is and form.......
  Description of what program output is and form.......
*/

#include "CardClass.h"
#include <iostream>
#include <vector>
using namespace std;

// function prototypes
void PrintCards(CardType players[], int size, int i);
void SortCards(CardType deck[], int size);

int main() {
  // create an object of CardClass which is a deck of cards
  CardClass object;

  // initialize 4 players
  // vector<vector<CardType>> players(4);

  // deals cards to 4 players (Each player is defined as a 1-D array of
  // CardStruct type)
  CardType player1[13];
  CardType player2[13];
  CardType player3[13];
  CardType player4[13];

  // shuffle the cards
  object.ShuffleCards();

  // I plan on making this its own function later on to look better in the main
  // file
  int i = 0;
  // deal cards to 4 players while deck is not empty
  while (!object.IsEmpty()) {
    player1[i] = object.DealCard();
    player2[i] = object.DealCard();
    player3[i] = object.DealCard();
    player4[i] = object.DealCard();
    i++;
  }

  // turn this into a for loop
  // sort the cards for each player
  SortCards(player1, 13);
  SortCards(player2, 13);
  SortCards(player3, 13);
  SortCards(player4, 13);

  // use a loop
  // print out the cards for each player
  PrintCards(player1, 13, 0);
  PrintCards(player2, 13, 1);
  PrintCards(player3, 13, 2);
  PrintCards(player4, 13, 3);

  // display who is holding the 2 of clubs using the search function
  for (int i = 0; i < 4; i++) {
    if (object.SearchCards(player1, 13) == 0) {
      cout << "Player 1 is holding the 2 of clubs" << endl;
      break;
    } else if (object.SearchCards(player2, 13) == 1) {
      cout << "Player 2 is holding the 2 of clubs" << endl;
      break;
    } else if (object.SearchCards(player3, 13) == 2) {
      cout << "Player 3 is holding the 2 of clubs" << endl;
      break;
    } else if (object.SearchCards(player4, 13) == 3) {
      cout << "Player 4 is holding the 2 of clubs" << endl;
      break;
    } else {
      cout << "No one is holding the 2 of clubs" << endl;
      break;
    }
  }
}

  // sort the cards based on their suit using bubble sort
  void SortCards(CardType deck[], int size)
  {
    // indicates whether additional comparisons are needed
    bool sorted = false;

    // the index of the last element in the array
    int last = size - 1;

    // temp variable of type CardType to hold the temp card
    CardType temp;

    while (!sorted) {
      // assuming the remaining array is sorted
      sorted = true;

      // loop through the array
      for (int i = 0; i < last; i++) {
        // if the current card is greater than the next card
        if (deck[i].suit > deck[i + 1].suit) {
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
  }

  // displays the cards in one players hands
  void PrintCards(CardType players[], int size, int i) {

    // array to hold the card values as string types
    string values[] = {"0", "1", "2",  "3", "4", "5", "6", "7",
                       "8", "9", "10", "J", "Q", "K", "A"};

    cout << "Player " << i + 1 << endl;
    cout << "SUIT\tVALUE\tPOINTS" << endl;

    // loop to print out the cards
    for (int i = 0; i < size; i++) {
      // variable of type string to hold the suit of the card
      string suit;

      // switch statement to assign the suit of the card
      // based on the enum type value
      switch (players[i].suit) {
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
      cout << suit << "\t" << values[players[i].value] << "\t"
           << players[i].points << endl;
    }
    cout << endl;

    return;
  }
