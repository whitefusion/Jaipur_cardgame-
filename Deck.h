#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>
#include <iostream>

class Deck{
 private:
  std::vector<Card> deck;

 public:
  Deck(); // default constructor that generates all goods cards
  ~Deck(); // destructor

  void shuffle(); // shuffle the deck by default constructor
  int getsize(){return deck.size();}; // return the current number of cards in the deck
  void delGoods(int ); // delete a cards in the deck specified by an integer
  Card drawCard(); //draw 'top' card from deck
  void pDeck();
  void clear();

  void newDeck();
};

#endif
