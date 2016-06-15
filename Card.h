#ifndef _CARD_H
#define _CARD_H

#include <string>

class Card {
 private:
     std::string cardType;  

 public:
  Card();// default constructor
  Card(std::string);//constructor that sets the type with given string
 ~Card();   // destructor!!

 std::string getCard();//public method that 
 //that returns type of card ie gold or silver
 void setCard(std::string );//public method that 
 //set the type of card
 bool operator==(const Card&);// for test "Deck.h"
} ; 

#endif
