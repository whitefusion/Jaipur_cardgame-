CC = g++
#CFLAGS = -std=c++11 -g -pedantic -Wall -Wextra -O0 -fprofile-arcs -ftest-coverage
CFLAGS = -std=c++11 -g -pedantic -Wall -Wextra -O

#compilation of test 

jaipur: main.o Token.o AllTokens.o AllBonus.o Deck.o Card.o Market.o Player.o Human.o Game.o
	$(CC) $(CFLAGS) -o jaipur main.o Token.o AllTokens.o AllBonus.o Deck.o Card.o Market.o Player.o Human.o Game.o

%.o: %.cpp 
	$(CC) $(CFLAGS) -c $*.cpp

clean:
	\rm *.o jaipur

