#ifndef _GAME_H
#define _GAME_H

#include "Game.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <cctype>

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::string;
//using std::strtok;

Game::Game(Deck &dd, Market &mm, Human &pp1, Human &pp2) : deck(dd), market(mm), p1(pp1), p2(pp2) { //construct a game for Human vs. Human
    bonus.shuffle();//initialize all bonus
    setRound(1);//initialize round to 1
    setTurn(1);//initialize turn to 1
    srand(time(NULL));
    /*for demo*/

    currplayer = 1;

    /* comment out this for demonstration
    if (rand() % 100 > 50)
        currplayer = 1;
    else 
        currplayer = 2;
    */
}

Game::~Game(){
    deck.clear(); 
    market.clear();
    p1.clear();
    p2.clear();
    tokens.clear();
    bonus.clear();
}

// initialize a new round
void Game::newRound(int winner){ 
    //clear player's basic points, bonus points, total points
    for (int i = 0; i < 3; i++){
        p1.addPoint(i,-1*p1.getPoints(i));
        p2.addPoint(i,-1*p1.getPoints(i));
    }

    setTurn(1);
    setCurrPlayer(winner);
    deck.newDeck();
    deck.shuffle();
    market.newMarket(deck);
    tokens.newAToken();
    bonus.newABonus();
    p1.newPlayer(deck);
    p2.newPlayer(deck);
}

void Game::setRound(int r){
    round = r;
}

void Game::setTurn(int t){
    turn = t;
}

void Game::setCurrPlayer(int id){
    currplayer = id;
}

// play a round
void Game::play_a_round(){
    int curr = getCurrPlayer();
    int next;
    if (curr == 1)
        next = 2;
    else 
        next = 1;

    while(!RoundTermination()){
        display(getPlayer(curr));
        play_a_turn(getPlayer(curr));
        int temp = curr;
        curr = next;
        next = temp;
        if(curr == 1){
            int currTurn = getTurn();
            setTurn(++currTurn);
        }
    }

    cout << endl;
    cout << "Points before assiging CAMEL token: " << "player " << getPlayer(1).getName() << "---" <<  p1.getPoints(2);
    cout << "; " << "player " << getPlayer(2).getName() << "---" << p2.getPoints(2) << endl;

    cout << "CAMEL numbers: " << "player " << getPlayer(1).getName() << "---" << p1.getSize(1);
    cout << "; " << "player " << getPlayer(2).getName() << "---" << p2.getSize(1) << endl;



    //winning  camel token
    if (p1.getSize(1) > p2.getSize(1)){
        p1.addPoint(0,5);
        p1.addPoint(2,5);
    }
    else{
        p2.addPoint(0,5);
        p2.addPoint(2,5);
    }

    cout << "Points after assiging CAMEL token: " << "player " << getPlayer(1).getName() << "---" <<  p1.getPoints(2);
    cout << "; " << "player " << getPlayer(2).getName() << "---" << p2.getPoints(2) << endl;

    cout << "Bonus token #: " << "player " << getPlayer(1).getName() << "---" <<  p1.getBToken();
    cout << "; " << "player " << getPlayer(2).getName() << "---" << p2.getBToken() << endl;

    cout << "Goods token #: " << "player " << getPlayer(1).getName() << "---" <<  p1.getGToken();
    cout << "; " << "player " << getPlayer(2).getName() << "---" << p2.getGToken() << endl;

    //cout << "Winner is: " << getPlayer(roundWinner()).getName() << endl; 

    // winning seal
    if (roundWinner() == 1)
        p1.addPoint(3,1);
    else 
        p2.addPoint(3,1);

    setCurrPlayer(roundWinner());

    int currRound = getRound();
    setRound(++currRound);
}

// player to play a turn
void Game::play_a_turn(Player &p){
    int act;
    int take;
    vector<vector<int> > trade;
    vector<int> sell;

    act = p.setAction(market);

    // verify the input and carry out action
    switch (act){
        // take
        case 1:
        {
            take = takeInputVerify(market);
            p.Take(take, market, deck);
            break;
        }
        // trade
        case 2:
        {
            trade = tradeInputVerify(p,market);
            p.Trade(trade.at(0), trade.at(1), market);
            break;
        }
        //sell
        case 3:
        {
            sell = sellInputVerify(p);
            p.Sell(sell, tokens, bonus);
            break;
        }
        //take camels
        case 4:
        {
            p.TakeCamel(market, deck); 
            break;
        }
    }
}

// check the index of card taking in
bool Game::takeVerify(Market &m, int &take){
    if (take < 1 || take > 5 || m.getGoods(take).getCard()=="CAMEL")
        return false;
    else 
        return true;
}

// check the indices for exchange
bool Game::tradeVerify(vector<int> &mtake, vector<int> &htake, Player &p, Market &m){
    // if no cards in hand, return false
    if (p.getSize(0)+p.getSize(1) < 2 || mtake.size() < 2)
        return false;

    int msize = mtake.size();
    int hsize = htake.size();

    // out of range
    for (int i = 0; i < msize; ++i)
        if (mtake.at(i) > 5 || mtake.at(i) < 1 || isalpha(mtake.at(i)))
            return false;

     for (int i = 0; i < hsize; ++i)
         if (htake.at(i) > 7 || htake.at(i) < 1 || isalpha(htake.at(i)))
             return false;


    // Rules: mcards >= hcards; --- total card # conserved 
    // size[0] + mcards - hcards <= 7; --- new size of hand cards should be <= 7
    // mcards - hcards <= size[1]; --- # of camel to exchange <= available camels
    // cannot take camel cards on market

    // no same index are allowed
    for (int i = 0; i < msize; ++i){
        for (int j = 0; j < msize; ++j){
            if ((i !=j) && (mtake.at(i) == mtake.at(j)))
                return false;
        }
    }
    
    // no same index are allowed
    for (int i = 0; i < hsize; ++i){
        for (int j = 0; j < hsize; ++j){
            if ((i != j) && (htake.at(i) == htake.at(j)))
                return false;
        }
    }

    // same goods cannot be traded
    for (int i = 0; i < msize; ++i){
        for (int j = 0; j < hsize; ++j){
            if (market.getGoods(mtake.at(i)).getCard() == p.getHand(0,htake.at(j)-1).getCard())
                return false;
        }
    }

    

    // size ...
    if (msize < hsize || p.getSize(0) + msize - hsize > 7 || p.getSize(1) < msize - hsize)
        return false;
    else {
         for (int i = 0; i < msize; ++i)
             if (m.getGoods(mtake.at(i)).getCard() == "CAMEL" )
                 return false;
    }        
    return true;
}

// check the indices of cards for sell
bool Game::sellVerify(vector<int> &hsell, Player &p){
    //check if input are within 1 to handsize
    int sellSize = hsell.size();

    if (sellSize == 0)
        return false;

    for (int i = 0; i < sellSize; ++i){
        for (int j = 0; j < sellSize; ++j){
            if ((i != j) && (hsell.at(i) == hsell.at(j)))
                return false;
        }
    }

    for (int i = 0; i < sellSize; ++i)
        if (hsell.at(i) > p.getSize(0) || hsell.at(i) < 1)
            return false;

    // check if only one good
    for (int i = 1; i < sellSize; ++i)
        if (p.getHand(0,hsell.at(i-1)-1).getCard() != p.getHand(0,hsell.at(i)-1).getCard())
            return false;
    // check if goods are DIAMOD, GOLD or SILVR?
    for (int i = 0; i < sellSize; ++i){
        string tmp = p.getHand(0,hsell.at(i)-1).getCard(); 
        if ((tmp == "DIAMD" || tmp == "GOLD" || tmp == "SILVR") && sellSize < 2)
            return false;
    }

    return true;
}

// return a valid input for take
int Game::takeInputVerify(Market &m){
    int take;
    char tmp[256];
    char *token;

    cout << "Choose the ID of the card want to take: ";
    cin.getline(tmp,256);
    token = strtok(tmp, " \t\n\r\f");
    while (!token){
        cout << "Invalid choice! Try again." << endl;
        cout << "Choose the ID of the card want to take: ";
        cin.getline(tmp, 256);
        token = strtok(tmp, " \t\n\r\f");
    }
    take = atoi(token);

    while(!takeVerify(m, take)){
        cout << "Invalid choice! Try again: ";
        cin.getline(tmp,256);
        token = strtok(tmp, " \t\n\r\f");
        while (!token){
            cout << "Invalid choice! Try again." << endl;
            cout << "Choose the ID of the card want to take: ";
            cin.getline(tmp, 256);
            token = strtok(tmp, " \t\n\r\f");
        }
        take = atoi(token);
    }
    return take;
}

// return a valide 2D vector for trade
vector<vector<int> > Game::tradeInputVerify(Player &p, Market &m){
    vector<vector<int> > temp;
    vector<int> tempM;
    vector<int> tempH;

    char tmp[256];
    char *token;

    // read in user's input
    cout << "Choose the cards on MARKET want to take in: ";
    //cin.getline(tmp, 256);
    cin.getline(tmp, 256);

    token = strtok(tmp, " \t\n\r\f");
    while (!token ){
        cout << "Invalid choice! Try again." << endl;
        cout << "Choose the cards on MARKET want to take in: ";
        cin.getline(tmp, 256);
        token = strtok(tmp, " \t\n\r\f");
    }

    tempM.push_back(atoi(token));
    token = strtok(NULL, " \t\n\r\f");
    while (token){
        tempM.push_back(atoi(token));
        token = strtok(NULL, " \t\n\r\f");
    }

    cout << "Choose the cards on HANDS want to trade: ";
    cin.getline(tmp, 256);

    token = strtok(tmp, " \t\n\r\f");


    // if nothing input, will trade camels
    if (token){
        tempH.push_back(atoi(token));
        token = strtok(NULL, " \t\n\r\f");
        while (token){
            tempH.push_back(atoi(token));
            token = strtok(NULL, " \t\n\r\f");
        }        
    }

    while(!tradeVerify(tempM, tempH, p, m)){
        tempM.clear();
        tempH.clear();
        cout << "Invalid choice! Try again." << endl;
        cout << "Choose the cards on MARKET want to take in: ";
        cin.getline(tmp, 256);

        token = strtok(tmp, " \t\n\r\f");
        while (!token){
            cout << "Invalid choice! Try again." << endl;
            cout << "Choose the cards on MARKET want to take in: ";
            cin.getline(tmp, 256);
            token = strtok(tmp, " \t\n\r\f");
        }


        tempM.push_back(atoi(token));
        token = strtok(NULL, " \t\n\r\f");
        while (token){
            tempM.push_back(atoi(token));
            token = strtok(NULL, " \t\n\r\f");
        }

        cout << "Choose the cards on HANDS want to trade: ";
        cin.getline(tmp, 256);

        token = strtok(tmp, " \t\n\r\f");

        // if nothing input, will trade camels
        if (token){
            tempH.push_back(atoi(token));
            token = strtok(NULL, " \t\n\r\f");
            while (token){
                tempH.push_back(atoi(token));
                token = strtok(NULL, " \t\n\r\f");
            }
        }
    }

    temp.push_back(tempM);
    temp.push_back(tempH);

    return temp;
}

// return a valid vector of indices for sell
vector<int> Game::sellInputVerify(Player &p){
    vector<int> temp;
    char tmp[256];
    char *token;

    cout << "Choose the cards on HANDs to sell: ";
    //cin.getline(tmp, 256);
    cin.getline(tmp, 256);

    token = strtok(tmp, " \t\n\r\f");


    while (!token){
        cout << "Invalid choice! Try again." << endl;
        cout << "Choose the cards on MARKET want to take in: ";
        cin.getline(tmp, 256);
        token = strtok(tmp, " \t\n\r\f");
    }


    temp.push_back(atoi(token));

    token = strtok(NULL, " \t\n\r\f");
    while (token){
        temp.push_back(atoi(token));
        token = strtok(NULL, " \t\n\r\f");
    }

    while (!sellVerify(temp, p)){
        temp.clear();
        cout << "Invalid choice! Try again." << endl;
        cout << "Choose the cards on HANDs to sell: ";
        cin.getline(tmp, 256);

        token = strtok(tmp, " \t\n\r\f");

        while (!token){
            cout << "Invalid choice! Try again." << endl;
            cout << "Choose the cards on MARKET want to take in: ";
            cin.getline(tmp, 256);
            token = strtok(tmp, " \t\n\r\f");
        }


        temp.push_back(atoi(token));
        token = strtok(NULL, " \t\n\r\f");
        while (token){
            temp.push_back(atoi(token));
            token = strtok(NULL, " \t\n\r\f");
        }
    }

    return temp;
}

// check if round is terminated
bool Game::RoundTermination(){
    // check the size of deck
    if (getDeck().getsize() == 0)
        return true;
    // check the number of tokens
    int numZero = 0;
    for (int i = 0; i < 6; ++i){
        if (getATokens().getSize(i+1) == 0)
            numZero++;
    }
    if(numZero > 2)
        return true;

    return false;
}

// return the Round winner, 1--player1, 2--player2
int Game::roundWinner(){
    

    // check the total rupees
    if (p1.getPoints(2) > p2.getPoints(2))
        return 1;
    else if (p1.getPoints(2) < p2.getPoints(2))
        return 2;
    else if (p1.getBToken() > p2.getBToken())
        return 1;
    else if (p1.getBToken() < p2.getBToken())
        return 2;
    else if (p1.getGToken() > p2.getGToken())
        return 1;
    else
        return 2;
}

int Game::finalWinner(){
    if (p1.getPoints(3) == 2)
        return 1;
    else 
        return 2;
}

// display the tokens, bonus, market and player's hands
void Game::display(Player &p){
    system("clear");
    tokens.printTokens();
    bonus.pBonus();
    market.printMarket();
    p.printPlayer();
    cout << "=====================================================================================Round " << getRound() << " Turn " << getTurn() << "=========================================================================================" << endl;
}


#endif
