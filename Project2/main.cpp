//
// Created by dlpon on 9/9/2022.
//
#include "CardClass.h"
#include "player.h"
#include <ctime>
#include <iostream>
#include <string>
using namespace std;

const int MAX_ROUNDS = 13; // Maximum rounds

// declare prototypes of the functions here
void DisplayCard(const CardStruct c);
int FindLead(PlayerClass p[]);
void PlayRound(PlayerClass p[], CardStruct t[], int &lead);
void DisplayCard(const CardStruct c);
int GetChoice(PlayerClass user, suitType s, int turn);
int FindCollector(const CardStruct t[], int &score, suitType leadingSuit);
void DisplayScoreBoard(PlayerClass p[]);
void PrintCards(CardStruct players[], int size, int i);

int main() {
  // declare local variables
  // CardStruct table[MAX_PLAYERS];		//This structure holds the 4 cards
  // played by the 4 players in one round of the game
  CardClass deckOfCards;            // deck is created
  PlayerClass players[MAX_PLAYERS]; // user and players
  int winner, i, num;

  string name[4] = {"Computer 1", "Computer 2", "Computer 3", "User"};
  CardStruct player[4][13]; // player's cards

  // seed the random number generator
  srand(time(NULL));

  // shuffle the deck
        deckOfCards.ShuffleCards();

        // deal only one card at a time
        // by repetitavely calling the DealCard method of CardClass
        // and adding the card to the player's hand


  cout << "The winner is " << name[winner] << endl;
  getchar();

  return 0;
}

// This function calls the PlayerClass member function to find who leads the
// first game
int FindLead(PlayerClass p[]) {
  // fill in code
  for (int i = 0; i < MAX_PLAYERS; i++) {
    if (p[i].IsFirstLead()) {
      return i;
    }
  }
}

// This function plays one round of the game
//  p[] pass in the 4 PlayerClass objects, i.e., the 4 players
//  t[] will hold the 4 cards for a round
//  lead will:
//     (1)pass in who should lead the current round, and
//     (2)pass back to the calling function who will lead the next round of the
//     game
void PlayRound(PlayerClass p[], CardStruct t[], int &lead) {
  // declare local variables
  suitType leadingSuit; // the suit of the first card played in the round
  int collector;        // the index of the player who collects the cards
  int i;                // loop counter

  // First, print "user" if the lead is 0
  // otherwise print the computer number
  if (lead == 0) {
    cout << "User";
  } else {
    cout << "Computer " << lead;
  }

  // This for loop lets the players to each play a card
  // Make sure to collect the 4 cards played in the array t
  for (i = 0; i < MAX_PLAYERS; i++) {
    // if a player's hand is full
    // and if the player is leading,
    // then start the game by play 2 of club
    if (p[i].IsFirstLead() && i == lead) {
      t[i] = p[i].Play2Club();
    }

    // else if computer is leading, then the computer plays a card
    else if (i == lead) {
      t[i] = p[i].StartOneHand();
    }

    // else if the user is leading, get a choice from the user
    // otherwise computer plays a card by following a leading suit
    else if (i == 0) {
      t[i] = p[i].PlaySelectedCard(GetChoice(p[i], leadingSuit, i));
    } else {
      t[i] = p[i].PlaySelectedCard(leadingSuit);
    }

    // Print "user" if the lead is 0
    // otherwise prints computer number
    if (i == 0) {
      cout << "User";
    } else {
      cout << "Computer " << i;
    }

    // sets the leading suit played by the players who is leading the round
    if (i == lead) {
      leadingSuit = t[i].suit;
    }

    // Displays a card played by a current player
    DisplayCard(t[i]);

    // Clockwise rotation, move onto the next player
    lead = (lead + 1) % MAX_PLAYERS;
  }

  // Finds who has the highest value of a round
  // And assigns lead to who has the highest value
  for (i = 0; i < MAX_PLAYERS; i++) {
    if (t[i].value > t[lead].value) {
      lead = i;
    }
  }

  // Display which player gets how many points on this round
  cout << "Player " << lead << " gets " << t[lead].value << " points" << endl;

  // Adds current round's score to the player who had the highest value
  p[lead].AddScore(t[lead].value);

  // Prints the score board
  DisplayScoreBoard(p);
}

// This function prints one card's suit and value
void DisplayCard(const CardStruct c) {
  // print out players suit and value
  cout << c.suit << " " << c.value << endl;
}

// This function read the user's choice
//  turn : if it is 0, the user is leading the round; otherwise the user is
//  following in the round s : leading suit of the current game
int GetChoice(PlayerClass user, suitType s, int turn) {

  // declare local variables
  int choice;

  // if the user is leading the round get a choice from the user
  if (turn == 0) {
    // prompt the user to enter a choice
    cout << "Enter a choice: ";
    cin >> choice;

  }

  // if the user is playing after the lead,
  // then get a choice and check if it is a valid choice
  // continue to ask until a valid choice is made
  else {
    // prompt the user to enter a choice
    cout << "Enter a choice: ";
    cin >> choice;

    // check if the choice is valid
    while (!user.IsValidChoice(static_cast<suitType>(choice), s)) {
      // prompt the user to enter a choice
      cout << "Enter a choice: ";
      cin >> choice;
    }
  }
}

// This function find who has played the card of highest value of the round
int FindCollector(const CardStruct t[], int &score, suitType leadingSuit) {
  // declare local variables
  int collector = 0;

  // loop to sum up all of the points
  // and then find who has played the card of highest value for the round
  for (int i = 0; i < MAX_PLAYERS; i++) {
    // sum up all of the points
    score += t[i].value;

    // find who has played the card of highest value for the round
    if (t[i].value > collector) {
      collector = t[i].value;
    }
  }

  // the array index corresponding to the player with the highest value for the
  // round is retured.
  return collector;
}

// This function prints each player's score
void DisplayScoreBoard(PlayerClass p[]) {
  // fill code
  // print out each players score
  for (int i = 0; i < MAX_PLAYERS; i++) {
    cout << "Player " << i << " score: " << p[i].GetScore() << endl;
  }
}

// This function finds who won the game
//  winner's index is retured
int FindWinner(PlayerClass p[]) {

  // fill code
  // declare local variables
  int winner = 0;
  int highestScore = 0;
  // loop to find who has the highest score
  for (int i = 0; i < MAX_PLAYERS; i++) {
    // find who has the highest score
    if (p[i].GetScore() > highestScore) {
      highestScore = p[i].GetScore();
      winner = i;
    }
  }
  // the array index corresponding to the player with the highest score is
  // retured.
  return winner;
}

// displays the cards in one players hands
void PrintCards(CardStruct players[], int size, int i) {

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
