// Name: Nathan Metens       // CS 202 w/ Karla Fant

// This is the implementation file for the player class.
// Here, the player name, points, and hearts are intialized
// only once for the entire game. The player is then passed 
// by reference to the other classes as a player object "player1/"

#include "player.h"
#include <iostream>
using namespace std;

player::player(): hearts(3), points(500), WIN(false){ // initialization list
  playerName = NULL; // default player name
}

player::~player(){ // reset each value to NULL (0)
  hearts = 0; 
  points = 0;
  WIN = false;
  if(playerName){
    delete [] playerName;
    playerName = NULL;
  }
}

void player::setPlayerName(char name[]){ // copies the name into the player class
  playerName = new char[strlen(name) + 1];
  strcpy(playerName, name);
}

char* player::displayName(){ // diplays the players name at the end of the game
  return playerName;
}

void player::displayPoints(){ // outputs the points
  cout<<"You have "<<points<<" points left."<<endl;
}

void player::displayHearts(){ // outputs the hearts
  cout<<"You have "<<hearts<<" hearts left."<<endl;
}

void player::subtractHeart(int heart){ // decriments the hearts
  hearts -= heart;
}

void player::subtractPoints(int points_to_subtract){ // subtracts given number of points
    points -= points_to_subtract;
}

bool player::checkPoints(int points_to_subtract){ // checks to see if there are enough points
  if(points - points_to_subtract >= 0)
    return true; // player has enough points to by certain thing
  return false; // player doesn't have enough points
}

bool player::GameOver(){ // determines if player still has hearts
  if(hearts <= 0)
    return true; // the player is out of hearts
  return false; // player still has hearts
}

bool player::Winner(){ // determines if the player has met the winning conditions
  if(WIN == true or points >= 800)
    return true;
  return false;
}

bool player::GameWin(bool winningDoor){ // returns true if the player wins the game
  if(winningDoor == true)
    WIN = true;
  return false;
}
