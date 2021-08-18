// Name: Nathan Metens       // CS 202 w/ Karla Fant

// This is the player headerfile. The class is a player class
// that holds all of the information for a player such as name,
// number of hearts, number of points, and this class is passed
// by refernce to the Arr class so that the player is able to move
// around the obstacle cource and be updataed correctly.

#include <string>
#include <cstring>
using namespace std;

class player{
  public:
    player();
    ~player();
    void displayPoints(); // shows the user how many points they have
    bool checkPoints(int points_to_subtract); // checks to see if the player has enough points
    void displayHearts(); // shows the remaining hearts
    void subtractHeart(int heart); // removes a heart when they lose a life
    bool GameOver(); // returns false if the player still has hearts
    bool Winner(); // determines if the player has met the winning conditions
    bool GameWin(bool winningDoor); // passes true for the winning Door to change WIN to true
    void subtractPoints(int points_to_subtract); // subtracts the given amount of points from total
    void setPlayerName(char name[]);
    char* displayName(); // diplays the players name at the end of the game
  private:
    int hearts; // how many chances the player gets
    int points; // starting points
    char *playerName; // the player's name in a dynamically allocated array
    bool WIN; // true if the player wins the game
};
