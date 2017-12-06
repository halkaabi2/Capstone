#ifndef PLAYER_H //prevent to include this file many times
#define PLAYER_H

#include <cstring> //for copy string

#define MAX_STRING 50 //maximum length of players' names

/*
define Player class
*/
class Player{
public:
//constructor
Player(const char name[]);

//getter of score
int getScore() const;

//setter of score
void setScore(int score);

//get name
const char* getName() const;

private:
//name of player
char name[MAX_STRING];

//current score of player
int score;
};

#endif

