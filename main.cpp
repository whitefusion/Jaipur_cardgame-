#include "Card.h"
#include "Deck.h"
#include "Market.h"
#include "Player.h"
#include "Human.h"
#include "AllBonus.h"
#include "AllTokens.h"
#include "Game.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cstring>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cin;


int main(){
    // initialize deck and market
    Deck   d1;
    d1.shuffle();
    Market m1(d1);

    Human p1(d1,"name1");
    Human p2(d1,"name2");

    Game g1(d1, m1, p1, p2);

    // initialize player game mode
    int mode;
    char tmp[256];
    char *token;

    cout << "Game starts! Choose Modes---> 1: AI vs. AI; 2: Human vs. Human; 3: Human vs. AI: " ; 
    cin.getline(tmp,256);

    token = strtok(tmp, " \t\n\r\f");
    while (!token || atoi(token) > 3 || atoi(token) < 1){
        cout << "Invalid choice! Try again." << endl;
        cout << "Choose Modes---> 1: AI vs. AI; 2: Human vs. Human; 3: Human vs. AI: ";
        cin.getline(tmp, 256);
        token = strtok(tmp, " \t\n\r\f");
    }
    mode = atoi(token);

    switch(mode){
        case 1:
        {
            cout << " AI vs. AI " << endl;     
            break;
        }
        case 2:
        {
            cout << "Enter Name for Player 1: ";
            cin.getline(tmp, 256);
            string n1(tmp);
            cout << "Enter Name for Player 2: ";
            cin.getline(tmp, 256);
            string n2(tmp);

            p1.setName(n1);
            p2.setName(n2);
            break;
        }
        case 3:
        {
            cout << "Enter Name for Human Player: ";
            cin.getline(tmp,256);
            string n1(tmp);
            p1.setName(n1); 
            break;
        }
    }

    while (p1.getPoints(3) != 2 && p2.getPoints(3) != 2){
        g1.play_a_round();
        int winner = g1.roundWinner();
        cout << "The winner of Round " << g1.getRound() - 1 << " is: " << g1.getPlayer(winner).getName() << endl;
        cout << "Starting a NEW ROUND..." << endl;
        std::this_thread::sleep_for (std::chrono::seconds(3));
        g1.newRound(winner);
    }

    int finalwinner = g1.finalWinner();

    cout << endl;
    cout << "The FINAL winner of this game is " << g1.getPlayer(finalwinner).getName() << endl;

    return 0;
}

