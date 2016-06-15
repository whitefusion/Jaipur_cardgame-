#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::sort;

map<string,int> type2id = {{"DIAMD",1},{"GOLD",2},{"SILVR",3},{"LEATH",4},{"SPICE",5},{"CLOTH",6},{"CAMEL",7}};

//default constructor
Player::Player(){
    Card tmpC;
    tmpC.setCard("DIAMD");
    vector<Card> cards;
    vector<Card> herds;

    for (int i = 0; i < 3; ++i)
        cards.push_back(tmpC);
    size[0] = 3;

    tmpC.setCard("CAMEL");
    for (int i = 0; i < 2; ++i)
        herds.push_back(tmpC);
    size[1] = 2;

    hand.push_back(cards);
    hand.push_back(herds);

    name = "LLL";

    for (int i = 0; i < 4; ++i)
        point[i] = 0;

    GTokenNum = BTokenNum = 0;
}

// constructor
Player::Player(Deck &deck, string playerName){
    Card tmpC;
    int i;
    size[0] = size[1] = 0;

    vector<Card> cards;
    vector<Card> herds;

    // draw five cards from deck, if card == CAMEL put it in herds 
    for (i = 0; i < 5; ++i){
        tmpC = deck.drawCard();
        if (tmpC.getCard() == "CAMEL"){
            herds.push_back(tmpC);
            size[1]++;
        }
        else{
            cards.push_back(tmpC);
            size[0]++;
        }
    }

    hand.push_back(cards);
    hand.push_back(herds);

    name = playerName;

    // initialize all points to zero
    for (i = 0; i < 4; ++i)
        point[i] = 0;

    GTokenNum = BTokenNum = 0;
}

Player::~Player(){}

void Player::clear(){
    for(int i = 0; i < 2; ++i){
        hand.at(i).clear(); 
    }

    hand.clear();
}

// reinitialize player's hand
void Player::newPlayer(Deck &deck){
    for(int i = 0; i < 2; ++i){
        hand.at(i).clear(); 
        size[i] = 0;
    }
    hand.clear();

    GTokenNum = BTokenNum = 0;

    // initialize all points to zero
    for (int i = 0; i < 3; ++i)
        point[i] = 0;

    Card tmpC;
    size[0] = size[1] = 0;

    vector<Card> cards;
    vector<Card> herds;

    // draw five cards from deck, if card == CAMEL put it in herds 
    for (int i = 0; i < 5; ++i){
        tmpC = deck.drawCard();
        if (tmpC.getCard() == "CAMEL"){
            herds.push_back(tmpC);
            size[1]++;
        }
        else{
            cards.push_back(tmpC);
            size[0]++;
        }
    }

    hand.push_back(cards);
    hand.push_back(herds);
}


void Player::addPoint(int type, int p){
    point[type] += p; 
}

void Player::setName(string n){
    name = n;
}

//getName
string Player::getName() const{
    return name;
}

//getSize
int Player::getSize(int type) const{
    return size[type];
}

// setHand
void Player::setHand(Card c){
    if (c.getCard() == "CAMEL"){
        hand.at(1).push_back(c);
        size[1]++;
    }
    else{
        hand.at(0).push_back(c);
        size[0]++;
    }
}

//getHand
Card Player::getHand(int type, int location) const{ // location from 0
    if (type >= 0 && type <= 1){
        if (location >= 0 && location < size[type])
            return hand.at(type).at(location); 
        else{ // if location out of range, return the first card
            cout << "getHand: location is out of range! get the first card instead!" << endl;
            return hand.at(type).at(0);
        }
    }
    else{ // if type not found, return the card
        cout << "getHand: card type not found! will return a card(not camel) instead!" << endl;
    }
    return hand.at(0).at(0);
}

//delHand
void Player::delHand(int type, int location){
    hand.at(type).erase(hand.at(type).begin()+location);
    size[type]--;
}

//getPoints: 0--basic points from goods tokens, 1--bonus points, 2--total points, 3--seal
int Player::getPoints(int type) const{
    if (type >= 0 && type <=3)
        return point[type];
    else
        cout << "getPoints: point type not found! Will return total points!" << endl;
    return point[2];
}

//Sell
void Player::Sell(vector<int> goods2sell, All_Tokens &AT, All_Bonus &AB){ // pass an integer vector that contains the location(from 1) of the cards
    sort(goods2sell.begin(), goods2sell.end()); // just convenient for delete
    int i;
    int n = goods2sell.size();
    for (i = 0; i< n; ++i){
        int l = goods2sell.at(i)-1;
        string type = hand.at(0).at(l).getCard(); 
        int id = type2id[type];
        // update points, token number
        if (AT.getSize(id) != 0){
            point[0] += AT.getToken(id).getVal();
            point[2] += AT.getToken(id).getVal();
            AT.deleteToken(id);
            GTokenNum ++;
        }
    }

    // delete the handcard, update card size
    delHand(0,goods2sell.at(0)-1);
    for (i = 1; i < n; ++i)
        delHand(0,goods2sell.at(i)-i-1);

    //update the bonus points, bonus
    if (n > 2){
        point[1] += AB.getBonus(n).getVal(); 
        point[2] += AB.getBonus(n).getVal();
        AB.delBonus(n);
        BTokenNum++;
    }
}

//Take
void Player::Take(int location, Market &M, Deck &D){
    //check the current size of hand cards: not exceed 7 
    if (size[0] < 7){
        //take the card,update card size
        setHand(M.getGoods(location));
        M.delGoods(location);
        //draw a card from deck to market
        M.setGoods(D);
    }
    else
        cout << "Take: Cannot take card: already 7 cards!" << endl;
}

//Trade
//firs two vector<int>: cards need to exchange in market and hand card;
//take several goods from market and exchange the same # of cards from hand
//third int: # of camel need to exchange
// Rules: mcards >= hcards; --- total card # conserved 
// size[0] + mcards - hcards <= 7; --- new size of hand cards should be <= 7
// mcards - hcards <= size[1]; --- # of camel to exchange <= available camels
// should test the above in Game.cpp or Rules.cpp
// the following assumes the above rules are satisfied
void Player::Trade(vector<int> mcards, vector<int> hcards, Market &M){ // location for both market and hand cards from 1
    sort(mcards.begin(), mcards.end());
    sort(hcards.begin(), hcards.end());
    int hc = hcards.size();  
    int mc = mcards.size();
    int CamelNum = mc - hc;
    int i;

    // take mc cards from market to hand
    for (i = 0; i < mc; ++i)
        setHand(M.getGoods(mcards.at(i))); 
    // delete the mc cards from market
    M.delGoods(mcards.at(0));
    for (i = 1; i < mc; ++i){
        M.delGoods(mcards.at(i)-i);
    }
    // exchange hc cards from hand to market
    for (i = 0; i < hc; ++i)
        M.setGoods_byCard(hand.at(0).at(hcards.at(i)-1)); 
    // delete the hc cards from hand
    if (hc > 0){
        delHand(0,hcards.at(0)-1);
        for (i = 1; i < hc; ++i)
            delHand(0,hcards.at(i)-i-1);
    }

    // exchange CamelNum cards to market from herds
    for (i = 0; i < CamelNum; ++i){
        M.setGoods_byCard(getHand(1,0)); 
        delHand(1,0);
    }
}

//TakeCamel
void Player::TakeCamel(Market &M, Deck &D){
    int i;
    int n = M.getSize();
    vector<int> L;
    // take all CAMEL cards in market into herds
    for (i = 0; i < n; ++i){
        Card tmpC = M.getGoods(i+1);
        if (tmpC.getCard() == "CAMEL"){ 
            setHand(tmpC);
            L.push_back(i);
        }
    }

    // delete all the CAMEL cards in market
    int m = L.size();
    M.delGoods(L.at(0)+1);
    for (i = 1; i < m; ++i)
        M.delGoods(L.at(i)-i+1);

    // fill up the market from deck
    M.setGoods(D);
}

void Player::printPlayer(){//hands, points,tokens
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << getName() << "'s Hands and Herds<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
//    cout << "============================================================================================================================================================================================" << endl;

    for (int i = 0; i < size[0]; ++i)
        cout << ".-------." << "     ";
    cout << "          ";
    for (int i = 0; i < size[1]; ++i)
        cout << ".-------." << "     ";

    cout << "Rupees from Tokes: " << getPoints(0) << "   "; 
    cout << endl;

    for (int i = 0; i < size[0]; ++i){
        cout << "| " << hand.at(0).at(i).getCard();
        if (hand.at(0).at(i).getCard() == "GOLD")
            cout << "  |";
        else 
            cout << " |";
        cout << "     ";
    }

    cout << "          ";

    for (int i = 0; i < size[1]; ++i){
        cout << "| " << hand.at(1).at(i).getCard();
        cout << " |";
        cout << "     ";
    }

    cout << "Rupees from Bonus: " << getPoints(1) << "   "; 
    cout << endl;

    for (int i = 0; i < size[0]; ++i)
        cout << "|       |" << "     "; 
    cout << "          ";
    for (int i = 0; i < size[1]; ++i)
        cout << "|       |" << "     "; 

    cout << "Total Rupees: " << getPoints(2) << "   "; 
    cout << endl;

    for (int i = 0; i < size[0]; ++i)
        cout << "|   " << i+1 << "   |" << "     "; 
    cout << "          ";
    for (int i = 0; i < size[1]; ++i)
        cout << "|       |" << "     "; 

    cout << "Token earned: " << getGToken() << "   ";
    cout << endl;

    for (int i = 0; i < size[0]; ++i)
        cout << "|       |" << "     "; 
    cout << "          ";
    for (int i = 0; i < size[1]; ++i)
        cout << "|       |" << "     "; 

    cout << "Bonus earned: " << getBToken() << "   ";
    cout << endl;

    for (int i = 0; i < size[0]; ++i)
        cout << "`-------'" << "     "; 
    cout << "          ";
    for (int i = 0; i < size[1]; ++i)
        cout << "`-------'" << "     "; 

    cout << "Seals: " << getPoints(3) << "   "; 
    cout << endl;
}

