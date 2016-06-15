#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include "AllBonus.h"
#include "AllTokens.h"
#include "Market.h"
#include <string>
#include <iostream>
#include <vector>

class Player{ //this is an abstract class bc setAction is a pure virtural function
    private: 
        std::vector<std::vector<Card>> hand;// good cards, herd 
        std::string name;
        int size[2]; // number of cards and camels
        int point[4];// basic, bonus, total and seal; 
        int GTokenNum;// # of goods token earned
        int BTokenNum; // # of bonus token earned

    //protected:
        // pure virtual function that will be defined in the AI and Human 

    public:
        virtual int setAction(Market &)=0;
        Player();
        Player(Deck& , std::string);//initialize a player
        virtual ~Player();
        void clear();

        // get points of a player, integer is the index of the 4 types of points 
        // ie(basic, bonus, total, seal) 
        int getPoints(int) const;
        int getSize(int) const;
        int getGToken() const {return GTokenNum;};
        int getBToken() const {return BTokenNum;};
        //1st int indicates card or herds: 0--card, 1--herds; 
        //2nd int means which handcard in card or herds 
        Card getHand(int, int) const ;
        std::string getName() const ;// get the name of a player
 
        void delHand(int, int ); // delete the card from player's hand that has been played 
        void setHand(Card);//update hands, if 'CAMEL' set it into herds, otherwise into cards
        void setName(std::string);
        void addPoint(int , int );

        //sell the cards included in vector<int> by location
        void Sell(std::vector<int>, All_Tokens &, All_Bonus &);
        //firs two vector<int>: cards need to exchange in market and hand card;
        //take several goods from market and exchange the same # of cards from hand
        //# of camel need to exchange = 1st int - 2nd int
        void Trade(std::vector<int>, std::vector<int>, Market &);
        //int means the location on market, take only 1 card from market, 
        //and draw a card (not Camel) from deck to market
        void Take(int, Market &, Deck &);
        void TakeCamel(Market &, Deck &); // take all the camels on market into herds
        void printPlayer();//hands, points,tokens
        // reinitialize a player's hand
        void newPlayer(Deck &);
};

#endif
