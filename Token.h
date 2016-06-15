/*test*/


#ifndef _TOKEN_H
#define _TOKEN_H

#include <string>
#include <map>

class Token{
private:
    std::string type; // type of token
    int val;          // value of the token

public:
    Token(); //defaut constructor
    ~Token();//destructor

    //sets the type of Token ie gold or silver; 
    //return 'true' if string is valid otherwise return 'false'
    bool setType(std::string );

    //sets the rupee value of token
    //return 'true' if value is valid otherwise return 'false'
    bool setVal(int );

    std::string getType(); //returns the type of token

    int getVal();//returns amount of rupees
    bool operator ==(const Token&);//overload == to compare two tokens
};

#endif
