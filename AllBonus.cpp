#include "AllBonus.h"
#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>

using std::vector;
using std::cout;
using std::endl;
using std::map;
using std::string;

#define TEST 1// if TEST=1, seed for shuffle will be fixed

map<int,string> BonusName = {{1,"3Bonus"}, {2,"4Bonus"}, {3,"5Bonus"}};

vector<vector<int>> Bonus = {
  {1,1,2,2,3,3}, // 3bonus value
  {4,4,5,5,6,6}, // 4bonus value
  {8,8,9,9,10,10} // 5bonus value
};

//constructor
All_Bonus::All_Bonus(): size{6,6,6}{
  int i;
  size_t j;
  Token temp;
  vector<Token> tempvec;

  for(i = 0; i < 3 ; ++i){
    temp.setType(BonusName[i+1]);
    for( j = 0; j < Bonus.at(i).size(); ++j){
      temp.setVal(Bonus.at(i).at(j));
      tempvec.push_back(temp);
    }
    allBonus.push_back(tempvec);
    tempvec.clear();
  }
}

void All_Bonus::newABonus(){
    for (int i = 0; i < 3; ++i)
        allBonus.at(i).clear();
    allBonus.clear();

    for (int i = 0; i < 3; ++i)
        size[i] = 0;

    size[0] = 6;
    size[1] = 6;
    size[2] = 6;
    int i;
    size_t j;
    Token temp;
    vector<Token> tempvec;

    for(i = 0; i < 3 ; ++i){
        temp.setType(BonusName[i+1]);
        for( j = 0; j < Bonus.at(i).size(); ++j){
            temp.setVal(Bonus.at(i).at(j));
            tempvec.push_back(temp);
        }
        allBonus.push_back(tempvec);
        tempvec.clear();
    }

    shuffle();
}

//destructor
All_Bonus::~All_Bonus(){
}

void All_Bonus::clear(){
    for (int i = 0; i < 3; ++i)
        allBonus.at(i).clear();
    allBonus.clear();
}


// shuffle the Bonus
void All_Bonus::shuffle()
{
  unsigned seed;
  if (TEST == 0)
      seed = std::chrono::system_clock::now().time_since_epoch().count();
  else 
      seed = 839223;

  for(int i = 0; i < 3; i++){
    std::shuffle(allBonus.at(i).begin(), allBonus.at(i).end(), std::default_random_engine(seed));
  }
}

//return the size of the input bonus
int All_Bonus::getSize(int id)
{
  if(id >=3 && id <=5){
    return size[id-3];
  }
  cout<<"getSize: Invalid type of Bonus!"<<endl;
  return -1;
}

Token All_Bonus::getBonus(int id)
{
  if( id >= 3 && id <=5)
    return allBonus.at(id-3).at(getSize(id)-1);
  else{ 
    cout<<" getBonus: Invalid type of bonus! Get the 3Bonus instead!" << endl;
  }
  return allBonus.at(0).at(getSize(3)-1);
}

// deleteBonus
void All_Bonus::delBonus(int id){
	allBonus.at(id-3).erase(allBonus.at(id-3).begin()+getSize(id));
	size[id-3]--;	
}

//print all Bonus
void All_Bonus::pBonus()
{
      int i, c, ts, tf;
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>BONUS<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
 //   cout << "============================================================================================================================================================================================" << endl;


	ts = 3;  
	tf = 6;
	for (i = ts; i < tf; ++i){
	    cout << "  "; 
	    for(c = 0; c < getSize(i)-1; ++c)
		cout << "  * *";
	    if (getSize(i) > 0){
		cout << "  * * *";
		cout << "           ";
	    }
	}
	cout << endl;

	for (i = ts; i < tf; ++i){
	    cout << "  ";
	    for (c = 0; c < getSize(i)-1; ++c)
		cout << "*    ";
	    if (getSize(i) > 0){
		cout << "*       *";
		cout << "         ";
	    }
	}
	cout << endl;

	for (i = ts; i < tf; ++i){
	    cout << " ";
	    for (c = 0; c < getSize(i)-1; ++c)
			cout << "*    "; // comment this line if test
            //for test
            /*
		    if (allBonus.at(i-3).at(c).getVal() == 10)
                cout << allBonus.at(i-3).at(c).getVal() << "   "; // for test to visualize
		    else 
                cout << allBonus.at(i-3).at(c).getVal() << "    "; // for test to visualize
            */
            

	    if (getSize(i) > 0){
		    cout << "*  " << allBonus.at(i-3).at(c).getType() << " *";
		    cout << "        ";
	    }
	    else
		    cout << " ";
	}
	cout << endl;

	for (i = ts; i < tf; ++i){
	    cout << " ";
	    for (c = 0; c < getSize(i)-1; ++c)
		    cout << "*    ";
	    if (getSize(i) > 0){
            cout << "*         *"; // comment this line if test
            //for test
            /*
            if (allBonus.at(i-3).at(c).getVal()==10)
                cout << "*   -" << allBonus.at(i-3).at(c).getVal() << "-  *"; // for test to visualize
            else 
                cout << "*   -" << allBonus.at(i-3).at(c).getVal() << "-   *"; // for test to visualize
            */
            
		    cout << "        ";
	    }
	    else
		    cout << " ";
	}
	cout << endl;

	for (i = ts; i < tf; ++i){
	    cout << "  ";
	    for (c = 0; c < getSize(i)-1; ++c)
		cout << "*    ";
	    if (getSize(i) > 0){
		cout << "*       *";
		cout << "         ";
	    }
	}
	cout << endl;

	for (i = ts; i < tf; ++i){
	    cout << "  "; 
	    for(c = 0; c < getSize(i)-1; ++c)
		cout << "  * *";
	    if (getSize(i) > 0){
		cout << "  * * *";
		cout << "           ";
	    }
	}
	cout << endl;

//    cout << "============================================================================================================================================================================================" << endl;
}


