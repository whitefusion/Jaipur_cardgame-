#ifndef MARKET_H
#define MARKET_H

#include "Deck.h"
#include "Card.h"
#include <iostream>
#include <vector>

class Market{
 private:
  std::vector<Card> goods;
  int size; // the current number of cards

 public:
  Market(); // default constructor 
  Market(Deck &);// constructor that will make up three camels and two random goods cards from deck
  ~Market(); // destructor

  Card getGoods(int ); // return a card that specified by an integer(order) in the market
  void setGoods(Deck &); // fill the market with cards from deck
  void setGoods_byCard(Card ); // set a chosen market card as the card desired
  void printMarket(); // print the market card in graphic manner
  int getSize();
  void delGoods(int);
  void newMarket(Deck &);
  void clear();
};

#endif
