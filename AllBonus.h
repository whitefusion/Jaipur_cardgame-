#ifndef _ALL_BONUS_H
#define _ALL_BONUS_H

#include "Token.h"
#include <vector>
#include <iostream>

class All_Bonus{
  private:
    // a 2-D vector inlucding 3, 4, 5-type bonus
    std::vector<std::vector<Token> > allBonus;     
    // the number of each type of bonus
    int size[3];
  public:
    All_Bonus(); // defaut constructor
    ~All_Bonus();//destructor 

    void clear();
    void shuffle(); // shuffle the order of each type of bonus in the pile
    int getSize(int ); // pass a integer such as 3, 4 or 5 and return the corresponding size of each type of bonus
    Token getBonus(int); //returns top Token dependent on an integer such as 3, 4, or 5 
    void pBonus();//print number of remaining bonus
    void delBonus(int); // delete the top bonus of type specified by an integer
    void newABonus();
};

#endif
