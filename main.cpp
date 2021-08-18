// Name: Nathan Metens       // CS 202 w/ Karla Fant

// This is the main client program that does all of the connected
// work for the player. The player only has to navigate the game
// menu and pick theur user name before starting the game. The
// menu is implemented as a switch statement to act like the 
// main menu for a real game :)

#include <iostream>
#include "node.h"

int main() {

  do{ // replay the menu until the user quits or begins playing

    cout<<"\n\t***************************"<<endl;
    cout<<"\t   Obstacle Course Game."<<endl;
    cout<<"\t***************************"<<endl;
    cout<<"\t   Main Menu:"<<endl;
    cout<<"\t***************************"<<endl;
    cout<<"\t      1. Game Rules\n\t      2. Start Game\n\t      3. Player Settings\n\t      4. Exit Game"<<endl;
    cout<<"\t***************************"<<endl;

    player player1; // creates the user player

    int option = 0;
    cout<<"\t   Select a menu option: ";
    cin>>option;
    cin.ignore(100, '\n');
    cout<<"\t***************************"<<endl;

    switch(option){
      case 1:{ // displays the rules to win and lose to the player
              cout<<"\t   Welcome to the game.\n\n\t   You start with 3 hearts and 500 points\n\t   You can win in two ways:\n\t  (1) Get 800 total points\n\t  (2) Choose the Winning Door\n\n\t   Good Luck!!"<<endl;
              cout<<"\t***************************\n"<<endl;
              break;
      }
      case 2:{ // start the game
               Arr my_arr;
               my_arr.display();
               break;
             }
      case 3:{ // set the player name
               char name[20];
               cout<<"\t   Enter your player name: ";
               cin.get(name, 20, '\n');
               cin.ignore(100, '\n');
               player1.setPlayerName(name);
               break;
             }
      case 4:{ // exit the game
               return 0;
             }
      default:{ // player picked invalid option
                 cout<<"\n\t   You did not enter a valid option."<<endl;
                 break;
              }
    }

  } while(1);

  return 0;
}
