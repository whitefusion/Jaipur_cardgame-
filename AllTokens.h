#ifndef _ALL_TOKENS_H
#define _ALL_TOKENS_H

#include "Token.h"
#include <vector>
#include <iostream>

class All_Tokens{
 private:
    // a 2-D vector stores all kind of tokens, each row stroes a type of token: Diamond, Gold, Silver, Leather, Spice, Cloth, Camel
    std::vector<std::vector<Token> > allTokens;
    // an integer array storing the number of each type of tokens
    int number[7];
 public:
    All_Tokens(); //default constructor
    ~All_Tokens();//destructor
    void clear();

    int getSize(int ); // get the current number of the tokens interested in by passing an integer: 1--Diamond, 2--Gold, 3-Silver, 4--Leather, 5--Spice, 6--Cloth, 7--Camel 
    Token getToken(int); //returns a Top token of specific type of token ie 1--Diamond, 2--Gold...
    void printTokens();//prints all remaining tokens
    void deleteToken(int);//deletes top Token of a specific type of token ie 1--diamond...
    void newAToken();
};

#endif
