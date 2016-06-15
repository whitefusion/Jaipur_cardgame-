#include "Token.h"
#include <string>
#include <map>
#include <iostream>

using std::string;
using std::map;
using std::multimap;
using std::pair;
using std::cout; using std::endl;

//token type map
map<string,int> tokenType = {{"DIAMD",1},{"GOLD",2},{"SILVR",3}, \
        {"LEATH",4},{"SPICE",5},{"CLOTH",6},{"CAMEL",7}, {"3Bonus",8},{"4Bonus",9},{"5Bonus",10}}; 

// multimap of tokenValue
multimap<string,int> tokenValue = {
{"DIAMD",7},{"DIAMD",5},
{"GOLD",6},{"GOLD",5},
{"SILVR",5},
{"CLOTH",5},{"CLOTH",3},{"CLOTH",2},{"CLOTH",1},
{"SPICE",5},{"SPICE",3},{"SPICE",2},{"SPICE",1},
{"LEATH",4},{"LEATH",3},{"LEATH",2},{"LEATH",1},
{"CAMEL",5},
{"3Bonus",3},{"3Bonus",2},{"3Bonus",1},
{"4Bonus",6},{"4Bonus",5},{"4Bonus",4},
{"5Bonus",10},{"5Bonus",9},{"5Bonus",8}
};

// default constructor
Token::Token(){
    type = "DIAMD";
    val = 7;
}

// destructor
Token::~Token(){}

// setType
bool Token::setType(string t){
    if (tokenType[t] >= tokenType["Diamond"] && tokenType[t] <= tokenType["5Bonus"]){
        type = t;
        return true;
    }
    else{
        cout << "Invalid token type!" << endl; 
        return false;
    }
}

// setVal
bool Token::setVal(int v){
    string thisToken = getType();
    pair<multimap<string,int>::iterator, multimap<string,int>::iterator> ii;
    multimap<string,int>::iterator it;
    ii = tokenValue.equal_range(thisToken);
    for (it = ii.first; it != ii.second; ++it){
        if (v == it->second){ 
            val = v;
            return true;
        }
    }

    cout << "Invalid token value of " << thisToken << "!" << endl;
    return false;
}

// getType
string Token::getType(){
    return type;
}

// getVal
int Token::getVal(){
    return val;
}

bool Token::operator ==(const Token& mytoken){
  return (this->type == mytoken.type && this->val==mytoken.val);
}
