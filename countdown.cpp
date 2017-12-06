/*
countdown.cpp

count down game

the function plays MAX_ROUND round
for each round, the current player will choose 9 letters
then all players will enter the word

the function checks if word in the dictionary
if it is dictionary the score (the length of word) will be added to player's score

If a nine letter word is achieved the score is doubled to eighteen points.
The player (index = 0) is the player that chooses 9 letters before the game.
The next player (index + 1) will be the player that chooses 9 letters in next round


Read the note about the requirement at the end of this file


*/
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>
#include <fstream>
#include "player.h"

using namespace std;

#define MAX_ROUND 15  //maximum number of round

//the player will choose 9 letters
//At least three vowels and at least four consonants must be chosen
#define NUM_LETTERS 9
#define BUFFER_SIZE 101

//dictionary file name
#define DICTIONARY_FILE_NAME "words.txt"

/*
function readDictionary
read words from file and put into vector
*/
void readDictionary(vector<string>& words){

//open for reading
ifstream wordFile (DICTIONARY_FILE_NAME);
string word; //a word from file

//if file is opened
if (wordFile.is_open())
{
//read line by line
while ( getline (wordFile, word) )
{
words.push_back(word);
}//end while

//close file
wordFile.close();

}else{
cout << "Could not open file " << DICTIONARY_FILE_NAME << endl;
}
}

/*
function findWord
find word in dictinary
*/
bool findWord(const vector<string>& words, const string& word){

//iterate the word vector
for (vector<string>::const_iterator it = words.begin() ; it != words.end(); ++it){

if (*it == word){
return true;
}

}
return false; //not found
}

/*
function readInt
read an integer from standard input
*/
int readInt(string prompt){

string line; //a line from user
stringstream ss; //for converting from string to int
int number; //an integer

//prompt for an integer
cout << prompt;
getline(cin, line); //read a line

//convert string to int
ss << line;
ss >> number;

return number;
}

/*
function readNumPlayers
read and validate number of players
number of players is 2 or more
*/
int readNumPlayers(){

int numPlayers = 0; //number of players

//read and validate number of players
while (numPlayers < 2)
{
numPlayers = readInt("Please enter number of players: ");
if (numPlayers < 2)
{
cout << "The number of players must be two or more" << endl;
}
}//end while

return numPlayers;
}

/*
function chooseLetters
read and validate 9 letters
At least three vowels and at least four consonants must be chosen
*/
void chooseLetters(char letterArray[]){
string letters; //9 letters
bool valid;//At least three vowels and at least four consonants must be chosen

//read 9 letters and validate
do{
valid = true;

cout << "Choose " << NUM_LETTERS << " letters: ";
getline(cin, letters);

if (letters.length() == NUM_LETTERS)
{
int countVowels = 0; //number of vowels
int countConsonants = 0; //number of consonants

//count vowels and consonants
for (int i = 0; i < NUM_LETTERS; i++)
{
//convert to lower case
letterArray[i] = tolower(letters[i]);

if (letterArray[i] == 'a' || letterArray[i] == 'e' || letterArray[i] == 'i' ||
letterArray[i] == 'o' || letterArray[i] == 'u')
{
countVowels++;
}else if (isalpha(letterArray[i]))
{
countConsonants++;
}else{
//not the english letter
}
}

if (countVowels < 3 || countConsonants < 4)
{
valid = false;
}
}else{
valid = false;
}

if (!valid)
{
cout << "Please enter nine letters and at least three vowels and at least four consonants" << endl;
}
}while(!valid);
}

/*
function readPlayerWord
read a word where each letter occurs once on chosen array
*/
string readPlayerWord(char chosenLettersArray[]){

bool valid;//At least three vowels and at least four consonants must be chosen
string playerWord;//player's word
char copyLettersArray[NUM_LETTERS]; //create a copy of chosenLettersArray

//read 9 letters and validate
do{
valid = true;

//copy array of characters
for (int i = 0; i < NUM_LETTERS; i++){
copyLettersArray[i] = chosenLettersArray[i];
}

cout << "Enter your word: ";
getline(cin, playerWord);

//check unique word
for (unsigned int i = 0; i < playerWord.size(); i++)
{
//find in chosen letters
bool found = false;
for (int j = 0; j < NUM_LETTERS; j++)
{
if (copyLettersArray[j] == playerWord[i])
{
copyLettersArray[i] = '-';
found = true;
break;
}
}

if (!found)
{
valid = false;
}
}

if (!valid)
{
cout << "Letter must be from chosen letters and each of the nine letters can be used only once when compiling words." << endl;
}
}while(!valid);

return playerWord;
}

/*
function playGame
the function plays MAX_ROUND round
for each round, the current player will choose 9 letters
then all players will enter the word
the function checks if word in the dictionary
if it is dictionary the score (the length of word) will be added to player's score
If a nine letter word is achieved the score is doubled to eighteen points.

The next player (index + 1) will be the player that chooses 9 letters in next round
*/
void playGame(vector<Player>& players, const vector<string>& words){

int round = 1; //current round
int choosenPlayerIndex = 0;//the index of player that choose 9 letters
char letters[NUM_LETTERS]; //9 letters
string playerWord;//player's word
int score; //player's score

//play MAX_ROUND round
do
{
cout << "*****************************"<< endl;
cout << "Round " << round << endl;
cout << "*****************************"<< endl;

//choose 9 letters
cout << "Player " << players[choosenPlayerIndex].getName() << ":" << endl;

//read and validate 9 letters
//At least three vowels and at least four consonants must be chosen
chooseLetters(letters);

//check words for each player
int current = (choosenPlayerIndex + 1) % players.size();

for (unsigned int i = 0; i < players.size(); i++)
{
//read a word from player
cout << "Player " << players[current].getName() << ":" << endl;
playerWord = readPlayerWord(letters);

//check if it is in dictionary
if (findWord(words, playerWord))
{
score = playerWord.length();

//If a nine letter word is achieved the score is doubled to eighteen points.
if (score == NUM_LETTERS)
{
score *= 2;
}

cout << "Word found. You have " << score << " score(s)" << endl;
}else{
score = 0;
cout << "Word not found. You have " << score << " score(s)" << endl;
}

//add score to players
players[current].setScore(players[current].getScore() + score);

//next player
current = (current + 1) % players.size();
}

cout << endl;

round++;//next round
//next player will choose 9 letters
choosenPlayerIndex = (choosenPlayerIndex + 1) % players.size();

}while (round < MAX_ROUND);

//print scores
cout << endl;
cout << "------------------------------------------"<< endl;
for (unsigned int i = 0; i < players.size(); i++)
{
cout << players[i].getName() << ", score: " << players[i].getScore() << endl;
}
cout << "------------------------------------------"<< endl;

//press Enter key to exit
cout << "Press Enter key to exit..." << endl;
cin.ignore();

}

/*
main function to start C++ application

the main function read player names, create vector of players,
read dictionary and call playGame to play count down game

*/
int main(){

int numPlayers; //number of players
vector<Player> players; //vector of players
string playerName; //player name
vector<string> words; //vector of words

//read number of players
numPlayers = readNumPlayers();

//read words from file and put into vector
cout << "Reading dictionary from file. Please wait..." << endl;
readDictionary(words);

//create players
for (int i = 0; i < numPlayers; i++)
{
//ask for name
cout << "Please enter the name of player " << i + 1 << ": ";
getline(cin, playerName);

//create player by calling constructor and add to vector
players.push_back(Player(playerName.c_str()));
}

//play game
playGame(players, words);

return 0;
}

/*
-----------------------------------------------------------------------------------

User input and output:
filename: countdown.cpp,
line 98, 143, 203, 350
line 67, 97, 122, 142, 178, 202, 228, 257, 258, 259,...

Control flow constructs, including use of at least three of the following:
if, else if, else, switch

filename: countdown.cpp,
line 56, 66, 145, 172, 156, 160, 163,...

At least two different types of iteration: for, do-while, while
filename: countdown.cpp,
line 139, 151, 117,...

At least one of the following data structures: c-style arrays, vectors, matrices
c-style arrays:
filename: player.h,  line 27
filename: countdown.cpp,  line 191

vector:
filename: countdown.cpp,  line 334, 336

At least three functions including at least one example of each of the following:
void return type, non-void return type, pass-by-value, pass-by-reference

void return: filename: countdown.cpp,  line 134, 246, ...
non-void return: filename: countdown.cpp,  line 75, 246, ...
pass-by-value: filename: countdown.cpp,  line 90, ...
pass-by-reference: filename: countdown.cpp,  line 49, ...

File input and/or output (using fstream, not including Bitmap.h file processing)

filename: countdown.cpp,  line 52

At least one class within dedicated file(s) with both private and public members

filename: player.h, player.cpp

*/

