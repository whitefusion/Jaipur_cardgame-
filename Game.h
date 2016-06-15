#ifndef GAME_H
#define GAME_H

#include "Market.h"
#include "Deck.h"
#include "Player.h" 
#include "Human.h"
#include "AllTokens.h"
#include "AllBonus.h"
#include <iostream>

class Game{
 private:
  Deck &deck;
  Market &market;
  Player &p1, &p2;
  All_Tokens tokens;
  All_Bonus bonus;
  int round, turn, currplayer;

 public:
  // constructor for H-H mode;
  Game(Deck &, Market &, Human &, Human &);
  ~Game();

  void play_a_round(); 
  void play_a_turn(Player &); 
  void display(Player &);

  void setRound(int);
  void setTurn(int);
  void setCurrPlayer(int);

  All_Tokens getATokens() const {return tokens;};
  All_Bonus  getABonus() const {return bonus;};
  Market getMarket() const {return market;};
  Deck &getDeck() const {return deck;};
  int getRound() const {return round;};
  int getTurn() const {return turn;};
  int getCurrPlayer() const {return currplayer;};
  Player& getPlayer(int id) const {
      if(id == 1) 
          return p1;
      else 
          return p2;
  };

  bool RoundTermination();
  int roundWinner();
  int finalWinner();
  //bool actionVerify(int, Player &);
  void newRound(int);

 private:
  bool takeVerify(Market &, int &);
  bool tradeVerify(std::vector<int> &, std::vector<int> &, Player &, Market &);
  bool sellVerify(std::vector<int> &, Player &);
  int takeInputVerify(Market &);
  std::vector<std::vector<int> > tradeInputVerify(Player &, Market &);
  std::vector<int> sellInputVerify(Player &);
  
};

#endif 
