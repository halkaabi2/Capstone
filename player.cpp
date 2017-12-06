#include "player.h"


Player::Player(const char name[])
{
strcpy(this->name, name);
score = 0;
}

//getter of score
int Player::getScore() const{
return score;
}

//setter of score
void Player::setScore(int score){
this->score = score;
}

//get name
const char* Player::getName() const{
return name;
}

