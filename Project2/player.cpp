//
// Created by dlpon on 9/9/2022.
//
#include "player.h"
#include <iostream>
using namespace std;

// default constructor
// post-condition: count is assigned 0, score is assigned 0
PlayerClass::PlayerClass() {
  count = 0;
  int score[4] = {0, 0, 0, 0};
}

// Adds one card to the player's hand.
// Cards are always added to one’s hand by adding it at the end of all cards
// already in one’s hand. pre-condition: player has less than 13 cards
// post-condition: player has one more card in the hand count is increased by
// 1
void PlayerClass::AddCard(CardStruct) {
  CardStruct card;
  // check if player has less than 13 cards
  if (count < MAX_PLAYER_CARDS) {
    // add card to the end of the hand
    hand[count] = card;
    // increment count
    count++;
  } else {
    cout << "Player has more than 13 cards" << endl;
  }
}

// prints out the current cards the player has
// pre-condition:  The player has some cards on hand
// post-condition: the player’s cards are displayed.
void PlayerClass::DisplayCards() const {
  // check if player has cards
  if (count > 0) {
    // print out the cards
    for (int i = 0; i < count; i++) {
      cout << hand[i].value << " of " << hand[i].suit << endl;
    }
  } else {
    cout << "Player has no cards" << endl;
  }
}

// select to play the first card that has the suit supplied from the client
// program if no card can be found that has the suit supplied by the client
// program, the first card from the hand is played pre-condition: there are >=
// 1 cards in hand post-condition: a card is returned, count is decremented by
// 1
CardStruct PlayerClass::FollowOneCard(suitType s) {
  CardStruct card;
  // check if player has cards
  if (count > 0) {
    // check if player has card with suit s
    for (int i = 0; i < count; i++) {
      if (hand[i].suit == s) {
        // play card
        card = hand[i];
        // shift cards
        for (int j = i; j < count; j++) {
          hand[j] = hand[j + 1];
        }
        // decrement count
        count--;
        return card;
      }
    }
    // play first card
    card = hand[0];
    // shift cards
    for (int i = 0; i < count; i++) {
      hand[i] = hand[i + 1];
    }
    // decrement count
    count--;
    return card;
  } else {
    cout << "Player has no cards" << endl;
  }
}

// plays the first card of a round. The top card in the deck is selected
// pre-condition: there are >= 1 card in the hand
// post-condition: one card is played/returned, count is decremented by 1
CardStruct PlayerClass::StartOneHand() {
  // check if player has cards
  if (count > 0) {
    // play the first card
    CardStruct card = hand[0];
    // shift cards up
    for (int i = 0; i < count; i++) {
      hand[i] = hand[i + 1];
    }
    // decrement count
    count--;
    return card;
  } else {
    cout << "Player has no cards" << endl;
  }
}

// Checks to see if the player should lead the
// first round in the game, e.g., check whether the player has 2 of club
// pre-condition: the hand is full (have 13 cards)
// post-condition: if this player has 2 of club, true is returned, otherwise,
// return false.
bool PlayerClass::IsFirstLead() const {
  // check if player has 13 cards
  if (count == MAX_PLAYER_CARDS) {
    // check if player has 2 of club
    for (int i = 0; i < count; i++) {
      if (hand[i].value == 2 && hand[i].suit == CLUB) {
        return true;
      }
    }
  }
}

// play card 2 of club
// pre-condition: the player has 2 of club on hand
// post-condition: 2 of club is played/returned. Cards following “2 of Club”
// is shifted up
//                          number of cards remaining on hand is decremented
//                          by 1
CardStruct PlayerClass::Play2Club() {
  // check if player has 2 of club
  for (int i = 0; i < count; i++) {
    if (hand[i].value == 2 && hand[i].suit == CLUB) {
      // play 2 of club
      CardStruct card = hand[i];
      // shift cards up
      for (int j = i; j < count; j++) {
        hand[j] = hand[j + 1];
      }
      // decrement count
      count--;
      return card;
    }
  }
}

// The current score of the player is returned
int PlayerClass::GetScore() const { return score; }

// get the current players hand
int PlayerClass::GetHand() const {
  for (int i = 0; i < count; i++) {
    cout << hand[i].value << " of " << hand[i].suit << endl;
  }
  return count;
  }


// the points from the current round is added to the current player's score
// pre-condition: a point value is sent in from client
// post-condition: the player's score is increased by the points from the
// client program
void PlayerClass::AddScore(int) {
  // a point value is sent in from client
  int points;
  // the player's score is increased by the points from the client
  // program
  score += points;
}

// Return the number of cards the player has
// pre-condition: none
// post-condition:   the number of cards currently in the player’s hand is
// returned
int PlayerClass::GetCount() const { return count; }

// sorts the cards by suit
// pre-condition: there are >=1 cards in hand
// post-condition: the cards are sorted by suit
void PlayerClass::Sort() {
  // index of the last element in the array
  int last = count - 1;

  bool sorted = false;
  while (!sorted) {
    // assume the array is sorted
    sorted = true;
    // loop through the array
    for (int i = 0; i < last; i++) {
      // check if the current element is greater than the next
      if (hand[i].suit > hand[i + 1].suit) {
        CardStruct temp = hand[i];
        hand[i] = hand[i + 1];
        hand[i + 1] = temp;
        sorted = false;
      }
    }
    last--;
  }
}

// plays the card selected by user
// pre-condition:  the card number selected by the user is supplied
// post-condition: the card corresponding to the user choice is
// played/returned the number
//                          of cards in player's hand is decremented by 1. If
//                          this card is in the
//                         middle of one’s hand, all cards following that card
//                         are shifted as a result of removing the card
CardStruct PlayerClass::PlaySelectedCard(int choice) {
  // check if the card number selected by the user is supplied
  if (choice >= 0 && choice < count) {
    // play the card corresponding to the user choice
    CardStruct card = hand[choice];
    // shift cards up
    for (int i = choice; i < count; i++) {
      hand[i] = hand[i + 1];
    }
    // decrement count
    count--;
    return card;
  }
}

// Checks to see if the card the user chooses is a valid choice, e.g., whether
// it matches the leading suit on that hand, if he has any. pre-condition: the
// player's choice and the leading suit are supplied post-condition: returns
// true if
//         (1) user has cards of leading suit and the choice card is of that
//         suit, or (2) user does not have card of leading suit
//      and returns false otherwise
bool PlayerClass::IsValidChoice(suitType, int) const {
  // the player's choice and the leading suit are supplied
  suitType leadingSuit;
  int choice;
  // check if user has cards of leading suit
  for (int i = 0; i < count; i++) {
    if (hand[i].suit == leadingSuit) {
      // check if the choice card is of that suit
      if (hand[choice].suit == leadingSuit) {
        return true;
      }
    }
  }
  // check if user does not have card of leading suit
  for (int i = 0; i < count; i++) {
    if (hand[i].suit != leadingSuit) {
      return true;
    }
  }
  return false;
}
