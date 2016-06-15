#include "AllTokens.h"
#include <map>
#include <string>
#include <iostream>

using std::vector;
using std::map;
using std::string;
using std::cout;
using std::endl;

map<int,string> tokenName = {{1,"DIAMD"}, {2,"GOLD"}, {3,"SILVR"},{4,"LEATH"}, {5,"SPICE"}, {6,"CLOTH"}, {7, "CAMEL"}};

vector<vector<int> > tokens = {
        {5, 5, 5, 7, 7}, // diamond tokens    
        {5, 5, 5, 6, 6}, // gold tokens
        {5, 5, 5, 5, 5}, // silver tokens
        {1, 1, 1, 1, 1, 1, 2, 3, 4}, // leather tokens
        {1, 1, 2, 2, 3, 3, 5}, // spice tokens
        {1, 1, 2, 2, 3, 3, 5}, //cloth tokens
        {5} // camel tokens
};

// default constructor
All_Tokens::All_Tokens(): number{5,5,5,9,7,7,1}{
    int i;
    size_t j;
    Token tmpT; // temporary token
    vector<Token> tmpTs; // temporary vector of tokens 

    for (i = 0; i < 7; ++i){
        tmpT.setType(tokenName[i+1]); 
        for (j = 0; j < tokens.at(i).size(); ++j){
            tmpT.setVal(tokens.at(i).at(j));
            tmpTs.push_back(tmpT);
        } 
        allTokens.push_back(tmpTs);
        tmpTs.clear();
    }
}

void All_Tokens::newAToken(){
    for (int i = 0; i < 7; ++i)
        allTokens.at(i).clear();
    allTokens.clear();

    for (int i = 0; i < 7; ++i)
        number[i] = 0;

    number[0] = 5;
    number[1] = 5;
    number[2] = 5;
    number[3] = 9;
    number[4] = 7;
    number[5] = 7;
    number[6] = 1;

    int i;
    size_t j;
    Token tmpT; // temporary token
    vector<Token> tmpTs; // temporary vector of tokens 

    for (i = 0; i < 7; ++i){
        tmpT.setType(tokenName[i+1]); 
        for (j = 0; j < tokens.at(i).size(); ++j){
            tmpT.setVal(tokens.at(i).at(j));
            tmpTs.push_back(tmpT);
        } 
        allTokens.push_back(tmpTs);
        tmpTs.clear();
    }
}

// destructor 
All_Tokens::~All_Tokens(){
}

void All_Tokens::clear(){
    for (int i = 0; i < 7; ++i)
        allTokens.at(i).clear(); 
    allTokens.clear();
}

// getSize
int All_Tokens::getSize(int id){
    if (id >= 1 && id <= 7){
        return number[id-1];
    }
    
    cout << "getSize:Invalid type of token!" << endl;
    return -1;
}

//getToken
Token All_Tokens::getToken(int id){
    if (id >= 1 && id <= 7)
        return allTokens.at(id-1).at(getSize(id)-1); 
    else // if the id is invalid, then always return last token
        cout << "getToken: Invalid type of token!" << endl;
    return allTokens.at(6).at(getSize(6)-1);
}

//deleteToken
void All_Tokens::deleteToken(int id){
    allTokens.at(id-1).erase(allTokens.at(id-1).end()-1);
    number[id-1]--;
}

// print Tokens
void All_Tokens::printTokens(){
    int i, c, row, ts, tf;
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>TOKENS<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
 //   cout << "============================================================================================================================================================================================" << endl;
    // output the first four types of tokens: diamond, gold, silver, leather

    for (row = 0; row < 2; ++row){
        if (row == 0){
            ts = 0;  
            tf = 4;
        }
        else {
            ts = 4;
            tf = 7;
        }
        for (i = ts; i < tf; ++i){
            cout << "  "; 
            for(c = 0; c < getSize(i+1)-1; ++c)
                cout << "  * *";
            if (getSize(i+1) > 0){
                cout << "  * * *";
                cout << "           ";
            }
        }
        cout << endl;

        for (i = ts; i < tf; ++i){
            cout << "  ";
            for (c = 0; c < getSize(i+1)-1; ++c)
                cout << "*    ";
            if (getSize(i+1) > 0){
                cout << "*       *";
                cout << "         ";
            }
        }
        cout << endl;

        for (i = ts; i < tf; ++i){
            cout << " ";
            for (c = 0; c < getSize(i+1)-1; ++c)
                cout << allTokens.at(i).at(c).getVal() << "    ";
            if (getSize(i+1) > 0){
                if (i == 1)
                    cout << "*  " << allTokens.at(i).at(c).getType() << "   *";
                else 
                    cout << "*  " << allTokens.at(i).at(c).getType() << "  *";
                cout << "        ";
            }
            else
                cout << " ";
        }
        cout << endl;

        for (i = ts; i < tf; ++i){
            cout << " ";
            for (c = 0; c < getSize(i+1)-1; ++c)
                cout << "*    ";
            if (getSize(i+1) > 0){
                cout << "*   -" << allTokens.at(i).at(c).getVal() << "-   *";
                cout << "        ";
            }
            else
                cout << " ";
        }
        cout << endl;

        for (i = ts; i < tf; ++i){
            cout << "  ";
            for (c = 0; c < getSize(i+1)-1; ++c)
                cout << "*    ";
            if (getSize(i+1) > 0){
                cout << "*       *";
                cout << "         ";
            }
        }
        cout << endl;

        for (i = ts; i < tf; ++i){
            cout << "  "; 
            for(c = 0; c < getSize(i+1)-1; ++c)
                cout << "  * *";
            if (getSize(i+1) > 0){
                cout << "  * * *";
                cout << "           ";
            }
        }
        cout << endl;
    }

//    cout << "============================================================================================================================================================================================" << endl;
}

