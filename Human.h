/* Human is subclass of the player that is used to 
   define the action of human player*/


#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"
#include "Deck.h"
#include "Market.h"
#include <string>

class Human: public Player{
public:
  Human(Deck &deck, std::string playerName);
  ~Human();

  int setAction(Market &);
  bool actionVerify(int, Market &);
};

#endif
