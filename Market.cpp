#include "Market.h"
#include <string>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

//default constructor
Market::Market(){
    Card tmpC;
    tmpC.setCard("CAMEL");
    for (int i = 0; i < 5; ++i)
        goods.push_back(tmpC); 
    size = 5;
}

// constructor that will make up three camels and two random goods cards from deck
Market::Market(Deck &deck){
    Card tmpC;
    tmpC.setCard("CAMEL");
    for (int i = 0; i < 3; ++i)
        goods.push_back(tmpC); 
    for (int i = 0; i < 2; ++i){
        tmpC = deck.drawCard();
        goods.push_back(tmpC); 
    }
    size = 5;
}

void Market::newMarket(Deck &deck){
    goods.clear();
    size = 0;
    Card tmpC;
    tmpC.setCard("CAMEL");
    for (int i = 0; i < 3; ++i)
        goods.push_back(tmpC); 
    for (int i = 0; i < 2; ++i){
        tmpC = deck.drawCard();
        goods.push_back(tmpC); 
    }
    size = 5;
}

//destructor
Market::~Market(){
}

void Market::clear(){
    goods.clear();
}

int Market::getSize(){
    return size;
}

// getGoods id from 1
Card Market::getGoods(int id){
    Card tmpC;
    if (id > 0 && id < size+1){
        tmpC = goods.at(id-1);
        return tmpC;
    }
    // if the card id is outside the market, always return the first card
    else{ 
        cout << "Invalid choice! You get the first Card instead!" << endl; 
        tmpC = goods.at(0);
    }
    return tmpC; 
}

// delGoods
void Market::delGoods(int id){
    goods.erase(goods.begin()+id-1);
    size--;
}

// setGoods
void Market::setGoods(Deck &deck){
    int n = 5 - size;
    if (deck.getsize() != 0){
        for (int i = 0; i < n; ++i){
            if(deck.getsize() == 0)
                break;
            goods.push_back(deck.drawCard()); 
            size++;
        }
    }
}

// setGoods
void Market::setGoods_byCard(Card c){
    goods.push_back(c);
    size++;
}
// pirntMarket
void Market::printMarket(){
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>MARKET<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
//    cout << "============================================================================================================================================================================================" << endl;
    for (int i = 0; i < size; ++i)
        cout << ".-------." << "     ";
    cout << endl;

    for (int i = 0; i < size; ++i){
        cout << "| " << goods.at(i).getCard();
        if (goods.at(i).getCard() == "GOLD")
            cout << "  |";
        else 
            cout << " |";
        cout << "     ";
    }
    cout << endl;

    for (int i = 0; i < size; ++i){
        cout << "|       |" << "     "; 
    }
    cout << endl;

    for (int i = 0; i < size; ++i){
        cout << "|   " << i+1 << "   |" << "     "; 
    }
    cout << endl;

    for (int i = 0; i < size; ++i){
        cout << "|       |" << "     "; 
    }
    cout << endl;

    for (int i = 0; i < size; ++i){
        cout << "`-------'" << "     "; 
    }
    cout << endl;
 //   cout << "============================================================================================================================================================================================" << endl;
}

