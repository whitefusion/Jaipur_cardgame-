#include "Card.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

//Default Consturtor sets type to "DIAMD"//
Card::Card(){this->cardType="DIAMD";}

//Construttor set type to given string//
Card::Card(string s){
  this->cardType=s;
}

//Deconstrutor sets type to emptpy string//
Card::~Card(){}

//gettype() returns the type of card//
string Card::getCard(){
  return this->cardType;
}

//settype() sets card type to given string//
void Card::setCard(string s ){
  this->cardType=s;
}

// overloaded "==" to compare two cards ( for test "deck.h")

bool Card::operator==(const Card &other)
{
  return this->cardType == other.cardType;
}

/*int main(){///TEST MAIN FOR CARD
  Card * test= new Card();
  cout<<test->getCard();
  test->setCard("testing");
  cout<<endl<<test->getCard()<<endl;
  
  return 0;
}
*/
