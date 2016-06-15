#include "Human.h"
#include <string>
#include <iostream>
#include <cstring>

using std::string;
using std::cout;
using std::cin;
using std::endl;

Human::Human(Deck &deck, string playerName): Player(deck, playerName) {} 

Human::~Human(){}

int Human::setAction(Market &m){
    int act;
    char tmp[256];
    char *token;

    cout << "Options(Take--1,  Trade--2,  Sell--3,  TakeCamel--4): ";
    cin.getline(tmp,256);
    token = strtok(tmp, " \t\n\r\f");

    while (!token){
        cout << "Invalid choice! Try again." << endl;
        cout << "Choose the cards on MARKET want to take in: ";
        cin.getline(tmp, 256);
        token = strtok(tmp, " \t\n\r\f");
    }
    act = atoi(token);

    while (!actionVerify(act,m)){
        cout << "Invalid action! Try again." << endl;
        cout << "Options(Take--1,  Trade--2,  Sell--3,  TakeCamel--4): ";
        cin.getline(tmp, 256);
        token = strtok(tmp, " \t\n\r\f");

        while (!token ){
            cout << "Invalid choice! Try again." << endl;
            cout << "Choose the cards on MARKET want to take in: ";
            cin.getline(tmp, 256);
            token = strtok(tmp, " \t\n\r\f");
        }

        act = atoi(token);
    }

    return act;
}

bool Human::actionVerify(int act, Market &m){
    if (act > 4 || act < 1)
        return false;

    bool allCamel = true;
    int nonCML = 0;
    for (int i = 0; i < 5; ++i){
        if (m.getGoods(i+1).getCard() != "CAMEL"){
            allCamel = false;
            nonCML++;
        }
    }

    int gc, dc, sc, rc;
    gc = dc = sc = rc = 0;

    for (int i = 0; i < getSize(0); ++i){
        string tmp = getHand(0,i).getCard();
        if (tmp == "DIAMD")
            dc++;
        else if (tmp == "GOLD")
            gc++;
        else if (tmp == "SILVR")
            sc++;
        else
            rc++;
    }

    switch (act){
        //take
        case 1:
        {
            if (allCamel || getSize(0) == 7)
                return false;
            else 
                return true;
        }

        // trade
        case 2:
        {
            if (nonCML > 1 && (getSize(0) + getSize(1) > 1))
                return true;
            else
                return false;
        }

        //sell
        case 3:
        {
            if (gc > 1 || dc > 1 || sc > 1 || rc > 0)
                return true;
            else 
                return false;
        }

        //take camel
        case 4:
        {
            if (nonCML < 5) 
                return true;
            else
                return false;
        }
    }

    return false;
}
