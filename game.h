// Name: Nathan Metens       // CS 202 w/ Karla Fant

// This is the header file which contains an abstract
// base class along with three derived obstacle 
// classes that each have their own functionality
// in providing a game. Each class has similar
// functions to allow for dynamic binding.

#include <iostream>
#include <cstring>
#include <string> // built in string type
#include "player.h"
using namespace std;

// This is the abstract base class that holds 
// the pure virtual functions that are implemented
// in the derived obstacle classes.
class obstacleCourse{ // abstract base class
// Class takes care of the dynamic casting.
  public:
    obstacleCourse();
    virtual ~obstacleCourse();
    bool gameOver(player &player1); 
// below are the pure virtual functions
    virtual void display(player &player1) = 0; 
    virtual void action(int, player &player1) = 0; // holds actions for the obstacle, passing the number of zombies. length of trap, or number of doors.
    virtual bool deactivate() = 0; // Each trap may have a deactivation button, or it may not. This is based on a coin flip 
  protected:
    bool obstacleStatus; // obstacle present?
    bool gameStatus; // game over?
};

// Obstacle presents a random number of zombies.
// If there are few enought zombies, they may be
// avoided or eliminated. If there are too many
// to handle, the user is eaten and loses a life.
class zombieHerd: public obstacleCourse{ // derived obstacle class
  public:
    zombieHerd();
    ~zombieHerd();
// These are the same signature functions as the base class
    void display(player &player1);
    void action(int numberOfZombies, player &player1); // displays obstacle details
    bool deactivate(); 
// This function is different to experience RTTI
    int buyAGun(); // this function allows you to buy a gun and eliminate one zombie, possibly giving the player a chance to live
  private:
    int numberOfZombies; // (rand)how many zombies 
    int maxZombies; // maximum number of zombies
};

// Obstacle presents a random width of the lava trap.
// If the trap is of a certain length, it may be 
// possible to jump over it. If not, you lose a life.
class lavaTrap: public obstacleCourse{ // derived obstacle class
  public:
    lavaTrap();
    ~lavaTrap();
// These are the same signature functions as the base class
    void display(player &player1);
    void action(int lengthOfTrap, player &player1);
    bool deactivate(); 
// This function is different to experience RTTI
    void superJump(); // this function gives the user some powers to jump to lengths up to 50 feet instead of 25 feet
  private:
    int lengthOfTrap; // can you jump over it?
    int maxLength;
};

// obstacle that presents 3 doors to choose from.
// one door is the winning door.
class roomWithDoors: public obstacleCourse{ // derived obstacle class
  public:
    roomWithDoors();
    roomWithDoors(const roomWithDoors & source); // copy constructor because of dynamic memory allocations
    ~roomWithDoors();
// These are the same signature functions as the base class
    void display(player &player1);
    void action(int, player &player1);
    bool deactivate(); 
// This function is different to experience RTTI
    int doorHint(int doorNumber); // This function eliminates the death door
  private:
    int numDoors; // how many doors there are to pick
    char *doorMessage;
};
