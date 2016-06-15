/*  Intermediate Programming, Final project */
/* Jaipur Game, Deck.cpp*/
/* Xin Bai, 11/19/2014 */

#include "Deck.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <random>

using std::cout;
using std::endl;
using std::vector;

#define Dnum 6//number of diamonds in a deck
#define Gnum 6//number of gold in a deck 
#define Sinum 6//number of silver in a deck
#define Clnum 8//number of cloth in a deck 
#define Spnum 8//number of spice in a deck 
#define Lnum 10//number of leather in a deck
#define Canum 8//number of camel in a deck
#define Tnum 55//total number of cards in a deck 

#define TEST 1 // if TEST=1, seed for shuflle will be fixed 

 // default constructor , build 55 cards
Deck::Deck(){
    int dnum,gnum,sinum,clnum,spnum,lnum,canum;

    Card Diamonds("DIAMD");
    Card Gold("GOLD");
    Card Silver("SILVR");
    Card Cloth("CLOTH");
    Card Spice("SPICE");
    Card Leather("LEATH");
    Card Camel("CAMEL");

    for(dnum=0; dnum<Dnum; dnum++){
	    deck.push_back(Diamonds);
    }

    for(gnum=0; gnum<Gnum; gnum++){
	    deck.push_back(Gold);
    }

    for(sinum=0; sinum<Sinum; sinum++){
	    deck.push_back(Silver);
    }

    for(clnum=0; clnum<Clnum; clnum++){
	    deck.push_back(Cloth);
    }

    for(spnum=0; spnum<Spnum; spnum++){
	    deck.push_back(Spice);
    }

    for(lnum=0; lnum<Lnum; lnum++){
	    deck.push_back(Leather);
    }

    for(canum=0; canum<Canum; canum++){
	    deck.push_back(Camel);
    }
}

void Deck::newDeck(){
    deck.clear();
    int dnum,gnum,sinum,clnum,spnum,lnum,canum;

    Card Diamonds("DIAMD");
    Card Gold("GOLD");
    Card Silver("SILVR");
    Card Cloth("CLOTH");
    Card Spice("SPICE");
    Card Leather("LEATH");
    Card Camel("CAMEL");

    for(dnum=0; dnum<Dnum; dnum++){
	    deck.push_back(Diamonds);
    }

    for(gnum=0; gnum<Gnum; gnum++){
	    deck.push_back(Gold);
    }

    for(sinum=0; sinum<Sinum; sinum++){
	    deck.push_back(Silver);
    }

    for(clnum=0; clnum<Clnum; clnum++){
	    deck.push_back(Cloth);
    }

    for(spnum=0; spnum<Spnum; spnum++){
	    deck.push_back(Spice);
    }

    for(lnum=0; lnum<Lnum; lnum++){
	    deck.push_back(Leather);
    }

    for(canum=0; canum<Canum; canum++){
	    deck.push_back(Camel);
    }
}

//destructor
Deck::~Deck()
{
}

void Deck::clear(){
    deck.clear();
}

//print all deck ( for test )
void Deck::pDeck()
{
  vector<Card>::iterator dit = deck.begin();
  while( dit != deck.end()){
      cout << (*dit).getCard()<<endl;
      dit++;
    }
}


//shuffle the deck
void Deck::shuffle(){
    //int i,j;
  unsigned seed;
    if (TEST == 0)
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    else 
        seed = 7834923;

    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
}


/*// find the number of certatin card in the deck, return number
//for test only
int Deck::fCard(Card& tcard)
{
    int counter=0;
    vector<Card>::iterator dit = deck.begin();
    while (dit != deck.end())
    {
	    if(*dit == tcard)
	    ++counter;
	    dit++;
    }
    return counter;
}
*/
//return a card and deleter it from the deck
Card Deck::drawCard(){
  Card temp;
  vector<Card>::iterator dit = deck.end()-1;
  temp = *dit;
  deck.erase(dit);
  return temp;
}

