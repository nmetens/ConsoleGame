// Name: Nathan Metens       // CS 202 w/ Karla Fant

// This is the game implementation file. Here, all of the
// classes are implemented. Each display function has the
// job of showing the user what obstacle they face and is
// interactive. The user is able to lose hearts, lose points
// as well as gain points and hearts. The classes that are 
// implemented: obstacleCourse, zombieHerd, lavaTrap, and
// roomWithDoors.

#include "game.h"
#include <cstring>
// These "#includes" are used for creating timers and having
// randum number generators:
#include <cstdlib>
#include <unistd.h>
#include <sys/time.h>

obstacleCourse::obstacleCourse(){
  obstacleStatus = true; // is there an obstale?
  gameStatus = true; // is the game still going?
}

obstacleCourse::~obstacleCourse(){
  gameStatus = false;
  obstacleStatus = false;
}

// function checks with the player class to determine
// if the player still has hearts. If not, the game is over.
bool obstacleCourse::gameOver(player &player1){
  if(player1.GameOver() == true){
    cout<<"\n*************"<<endl;
    cout<<"GAME OVER"<<endl;
    cout<<"*************"<<endl;
    player1.displayPoints();
    cout<<"*************\n"<<endl;
    gameStatus = true;
    exit(0);
  }
  else if(player1.Winner() == true){
    cout<<"\n*************"<<endl;
    cout<<"YOU WIN !!!!"<<endl;
    cout<<"*************"<<endl;
    player1.displayPoints();
    cout<<"*************\n"<<endl;
    gameStatus = true;
    exit(0);
  }
  return false;
}

//*********** zombieHerd class implementation ***********//
//*******************************************************//

zombieHerd::zombieHerd(): maxZombies(10){
  srand(time(0));
  numberOfZombies = rand() % maxZombies; // generate a random number between 0 and 10
}

zombieHerd::~zombieHerd(){
  maxZombies = 0;
  numberOfZombies = 0;
}

// This function displays the details of the zombieherd obstacle.
// There is a 2 second timer for suspense. Then the display calls the 
// action function which is interactive and provides the user with 
// the actions needed to escape the zombies, or get eaten alive!
void zombieHerd::display(player &player1){
  cout<<"\nYou are about to walk into a hallway..."<<endl;
  srand(time(0)); // creates a different amount of zombies each time
  numberOfZombies = rand() % maxZombies; // generate a random number between 0 and 10
  int num = numberOfZombies; // rand number less than 10

  // checks if there is a deactivation button and if the player has enough points to buy it
  if(deactivate() == true && player1.checkPoints(500)){
    cout<<"\nThere is a deactivation button available."<<endl;
    cout<<"Do you want to deactivate the obstacle for 500 points? (yes/no) ";
    string answer;
    cin>>answer;
    cin.ignore(100, '\n');
    cout<<"*************************************\n"<<endl;
    if(answer == "yes" || answer == "YES" || answer == "Yes" || answer == "Y" || answer == "y"){
      cout<<"\nThere were "<<num<<" zombies in the hallway, they were obliterated. -500 points."<<endl;
      cout<<"*************************************\n"<<endl;
      player1.subtractPoints(500); player1.displayPoints();
      return; // if zombies are eliminated, the player get a free walk
    }
  } 

  cout<<"\n There is a gun on the ground."<<endl;
  cout<<"But there is only one bullet."<<endl;
  cout<<"Do you want to pick it up? (yes/no) ";

  string answer2;
  cin>>answer2;
  cin.ignore(100, '\n');
  cout<<"*************************************\n"<<endl;

  bool hasGun = false; // does the user pick up a gun?
  if(answer2 == "YES" || answer2 == "yes" || answer2 == "Y" || answer2 == "y"){
    obstacleCourse *ptr = new zombieHerd;
    zombieHerd *zp = dynamic_cast<zombieHerd*>(ptr); // using dynamic casting to call the "non-self similar" function and experience RTTI
    if(zp != NULL)
      zp->buyAGun(); // calls the different derived function not mentioned int the abstract base class.
  }else{ cout<<"Alright, good luck!."<<endl;
    cout<<"*************************************\n"<<endl;

    // Creates a count down timer for suspense
    int counter = 2;
    sleep(1);
    while(counter >= 1){
      sleep(1);
      counter--;
    }
    action(num, player1); // calls the actions for the zombieHerd obstacle
  }
}

// This is the interactive obstacle function that promps the user
// to quickly react if there are more than 2 zombies. The user must
// be quick to escape, or get eaten and lose a life.
void zombieHerd::action(int num, player &player1){
  if(num <= 2){ // easy to run around 2 zombies
    cout<<"The hallway had only "<<num<<" zombies. You were able to get through."<<endl;
    cout<<"*************************************\n"<<endl;
  }else{ // if there are more than 2 zombies...
    cout<<"There are "<<num<<" zombies!!! RUN!"<<endl;
    char escape[5];
    struct timeval start, stop, timer; // allows for a stopwatch
    cout<<"QUICKLY TYPE 'RUN' TO EXCAPE!!"<<endl;

    srand(time(0));
    gettimeofday(&start, NULL); // stopwatch starts
    cin.get(escape, 5, '\n'); // takes user input
    cin.ignore(100, '\n');

    gettimeofday(&stop, NULL); // stopwatch ends after input is read 
    timersub(&stop, &start, &timer);
    cout<<"\nIt took you "<<timer.tv_sec<<" seconds to react."<<endl;

    if(strcmp(escape, "RUN") == 0 or strcmp(escape, "run") == 0 or strcmp(escape, "r") == 0 or strcmp(escape, "R") == 0 or strcmp(escape, "Run") == 0){
      cout<<"*************************************\n"<<endl;
      if(timer.tv_sec > 3){ // if user reacts in more than 3 seconds they die
        cout<<"\nYou stood around too long, the zombies ate your guts! -1 heart.\n";
        player1.subtractHeart(1); player1.displayHearts(); // subtracts a heart and displays
        obstacleCourse::gameOver(player1); // checks if the game is over
        cout<<"*************************************\n"<<endl;
        return;
      }
      cout<<"You escaped! Stay quiet..."<<endl; // player typed "RUN" correctly and fast
      cout<<"*************************************\n"<<endl;
    }
    else{ // user typed something other than "RUN"
      cout<<"\nYou tripped on your shoelace and the zombies ate you. -1 life."<<endl;
      player1.subtractHeart(1); player1.displayHearts();
      obstacleCourse::gameOver(player1); // checks if the game is over
      cout<<"*************************************\n"<<endl;
    }
  }
}

// This function creates a deactivation that kills all of the zombies
// leaving the hallway clear and the player can walk through without
// risking a heart. The activation is not always available, only a 
// small chance.
bool zombieHerd::deactivate(){
  int max = 100;
  srand(time(0)); 
  int deac = rand() % max; // generate a random number between 0 and 100
  if(deac % 7 == 0)
    return true; // if random number is divisible by 7, there is a trap deactivation button
  return false; // no trap deactivation
}

// This function gives an alternate story, where only one zombie is attacking player.
// they must react quickly to shoot the zombie, however, either way, they survive...
int zombieHerd::buyAGun(){
  // Creates a count down timer for suspense
  int counter = 1;
  sleep(1);
  while(counter >= 1){
    sleep(1);
    counter--;
  }

  cout<<"THERE IS A ZOMBIE RUNNING AT YOU!!!"<<endl;
  cout<<"QUICKLY TYPE 'SHOOT' TO KILL IT!!"<<endl;
  struct timeval start, stop, timer; // allows for a stopwatch
  string escape;
  srand(time(0));
  gettimeofday(&start, NULL); // stopwatch starts
  cin>>escape; // takes user input
  cin.ignore(100, '\n');

  gettimeofday(&stop, NULL); // stopwatch ends after input is read 
  timersub(&stop, &start, &timer);
  cout<<"\nIt took you "<<timer.tv_sec<<" seconds to react."<<endl;
  if((timer.tv_sec <= 3 and escape == "SHOOT") or (timer.tv_sec <= 3 and escape == "shoot")){
    cout<<"\nHead Shot! You killed the zombie, onwards..."<<endl;
  }else if(escape == "SHOOT" or escape == "shoot"){
    cout<<"\nYou missed the zombie's head and shot it in the leg, now it's crawling at you. You are able to go around it."<<endl;
  }else{
    cout<<"\nOh, it appears the zombie was after something else, you are safe..."<<endl;
  }
  return 0;
}

//*************** lavaTrap implementation ***************//
//*******************************************************//

lavaTrap::lavaTrap(): maxLength(100){
  srand(time(0));
  lengthOfTrap = (rand() % maxLength) + 1; // generate random length greater than 0
}

lavaTrap::~lavaTrap(){
  maxLength = 0;
  lengthOfTrap = 0;
}

// This function displays the info about the lava trap and then it
// calls the action function.
void lavaTrap::display(player &player1){
  cout<<"You begin to feel a lot of heat around the corner..."<<endl;
  srand(time(0));
  int len = (rand() % lengthOfTrap) + 1;

  if(deactivate() == true && player1.checkPoints(150) == true){ // checks if deactivation is present
    cout<<"\nThere is a deactivation button that costs 150 points."<<endl;
    cout<<"Do you want to use it? (yes/no) ";
    string answer;
    cin>>answer;
    cin.ignore(100, '\n');
    cout<<"*************************************\n"<<endl;
    if(answer == "YES" || answer == "yes" || answer == "Y" || answer == "y"){
      cout<<"\nThe length of the lava trap was "<<len<<" feet."<<endl;
      cout<<"A bridge has been built for you to cross safely. -150 points."<<endl;
      player1.subtractPoints(150); player1.displayPoints();
      cout<<"*************************************\n"<<endl;
      return;
    }
  }

  cout<<"\nYou notice a green bottle on the ground, do you want to drink it? (yes/no) ";
  string answer;
  cin>>answer;
  cin.ignore(100, '\n');
  cout<<"*************************************\n"<<endl;
  if(answer == "YES" || answer == "yes" || answer == "Y" || answer == "y"){
    obstacleCourse *ptr = new lavaTrap;
    lavaTrap *lp = dynamic_cast<lavaTrap*>(ptr); // using dynamic casting to call the "non-self similar" function and experience RTTI
    if(lp != NULL){
      lp->superJump(); // calls the different derived function not mentioned int the abstract base class.
    }
  }else{
    cout<<"Wise choice, you never know what it could be..."<<endl;
    int counter = 2;
    sleep(1); // suspense counter
    while(counter >= 1){
      sleep(1);
      counter--;
    }
    cout<<"\nThe length of the lava trap is "<<len<<" feet."<<endl;
    action(len, player1);
  }
}

// The action function is the lavatrap action. Here the user is given
// the option to attemp a jump or spend their points on a raft, which
// costs 500 points. If the user feels confident that they can jump
// accross a reasonable sized length of lava, they will have a chance
// factor that is calculated randomly to determine whether or not they
// succeed or fall in and burn, loosing a life.
void lavaTrap::action(int len, player &player1){
  char answer[3];
  if(len >= 25){
    cout<<"\nThis length is too much for any human to jump. Would you like to buy a lava boat? (Y/N) ";
    cin.get(answer, 3, '\n');
    cin.ignore(100, '\n');
    cout<<"*************************************\n"<<endl;
    if(strcmp(answer, "Y") == 0){
      if(player1.checkPoints(200) == false){ // checks if user has enought points
        cout<<"\nSorry you don't have enough points, so you fell in the lava. -1 heart."<<endl;
        player1.subtractHeart(1); player1.displayHearts();
        obstacleCourse::gameOver(player1); // checks if the game is over
        cout<<"*************************************\n"<<endl;
        return;
      } // player has enough points ...
      player1.subtractPoints(200);
      cout<<"\n-200 points"<<endl;
      cout<<"Nice! You made it to the other side."<<endl;
      player1.displayPoints();
      cout<<"*************************************\n"<<endl;
    }
    else{
      cout<<"\nYou burned in the lava. -1 heart."<<endl;
      player1.subtractHeart(1); player1.displayHearts();
      obstacleCourse::gameOver(player1); 
      cout<<"*************************************\n"<<endl;
    }
  }else{
    cout<<"Do you think you can make the jump? (Y/N) ";
    cin.get(answer, 3, '\n');
    cin.ignore(100, '\n');
    cout<<"*************************************\n"<<endl;
    if(strcmp(answer, "Y") == 0 or strcmp(answer, "y") == 0){
      int size = 100; // size of chance 
      srand(time(0));
      int chance = rand() % size; 
      if(chance >25){ // they have a 75 percent chance of success
        cout<<"\nNice jump! You made it accross."<<endl;
        cout<<"*************************************\n"<<endl;
      }
      else{
        cout<<"\nNice try, but with your luck, you fell right in! -1 heart."<<endl;
        player1.subtractHeart(1); player1.displayHearts();
        obstacleCourse::gameOver(player1); 
        cout<<"*************************************\n"<<endl;
      } 
    }else{
      cout<<"Do you want to buy a lava boat for 200 points? (yes/no) ";
      string answer;
      cin>>answer;
      cin.ignore(100, '\n');
      cout<<"*************************************\n"<<endl;
      if(answer == "YES" || answer == "yes" || answer == "Y" || answer == "y"){
        if(player1.checkPoints(200)){
          cout<<"\nYou don't have enough points for a lava boat, so you melted in the lava. -1 heart."<<endl;
          player1.subtractHeart(1); player1.displayHearts();
          obstacleCourse::gameOver(player1);
          cout<<"*************************************\n"<<endl;
          return;
        }else{
          player1.subtractPoints(200);
          cout<<"\n-200 points"<<endl;
          cout<<"Nice! You made it to the other side."<<endl;
          player1.displayPoints();
          cout<<"*************************************\n"<<endl;
        }
      }else{
        cout<<"\nYou chose not to buy a lava boat, so you cooked in the lava. -1 heart."<<endl;
        player1.subtractHeart(1); player1.displayHearts();
        obstacleCourse::gameOver(player1);
        cout<<"*************************************\n"<<endl;
      }
    }
  }
} 

// determines the chance that a deactivation is available for purchase
bool lavaTrap::deactivate(){
  int max = 100;
  srand(time(0)); 
  int deac = rand() % max; // generate a random number between 0 and 100
  if(deac % 7 == 0) // if deac is divisible by 7, there is a deactivation available
    return true;
  return false;
}

// This function gives the user super jump powers and their chance of making the jumps
// increase, as well as the length they can cover.
void lavaTrap::superJump(){
  cout<<"Nice! You just drank a Super Jump.\nNow you can jump over one lava trap no matter its length!"<<endl;
  cout<<"You just jumped over this one! Onwards!!"<<endl;
  return;
}

//************* roomWithDoors implementation ****************//
//***********************************************************//

roomWithDoors::roomWithDoors(): numDoors(4){ // 4 initial doors
  doorMessage = NULL;
} 

roomWithDoors::roomWithDoors(const roomWithDoors & source){ // copy constructor because of dynamic memory
  if(source.doorMessage){
    doorMessage = new char[strlen(source.doorMessage) + 1];
    strcpy(doorMessage, source.doorMessage);
  }
}

roomWithDoors::~roomWithDoors(){ // destructor
  numDoors = 0; 
  if(doorMessage){
    delete [] doorMessage;
    doorMessage = NULL;
  }
}

// This function is the description of the door obstacle. The user
// will have a 25 percent chance of winning, a 25 percent chance of
// losing, and 50 percent chance of getting a small reqard.
void roomWithDoors::display(player &player1){
  cout<<"You are about to enter a room... "<<endl;
  if(deactivate() == true && player1.checkPoints(50)){ // lower points to deactivate the doors
    cout<<"\nThere is a deactivation button available."<<endl;
    cout<<"Do you want to deactivate the obstacle for 50 points? (yes/no) ";
    string answer;
    cin>>answer;
    cin.ignore(100, '\n');
    cout<<"*************************************\n"<<endl;
    if(answer == "yes" || answer == "YES" || answer == "Yes" || answer == "Y" || answer == "y"){
      cout<<"\nYou passed the chance of getting the winning door. -50 points"<<endl;
      player1.subtractPoints(50); player1.displayPoints();
      cout<<"*************************************\n"<<endl;
      return; // if zombies are eliminated, the player get a free walk
    }
  } 
  int doorNumber = 0; // the player's choice if door
  cout<<"\nThere are "<<numDoors<<" doors to choose from."<<endl;
  cout<<"One door is the winning door, another door is the losing door, the other is +1 heart, and finally the -1 heart door."<<endl;

  action(doorNumber, player1); // if the deactivation was not selected, then continue to the actions
}

// This function is the interactive part of the roomWithDoors obstacle.
// The doors are randomized here and the player's choice could be one
// of 4 options. One of the options is winning the game, and another
// one of the options is losing the game. The only way the player can 
// win is if they get the lucky door.
void roomWithDoors::action(int doorNumber, player &player1){

  // setting the doors randomly... 
  srand(time(0));
  int deathDoor = (rand() % 4) +1; // the door number is eqaul to any number including and between 1 and 4
  int winningDoor = ((deathDoor) % 4) +1; // equal to 1 plus the deathDoor
  int HeartDoor = ((winningDoor) % 4) +1; // equal to 1 plus the winningDoor
  int pointsDoor = ((HeartDoor) % 4) +1; // equal to 1 plus the HeartDoor

  if(player1.checkPoints(400) == true){
    cout<<"Do you want a hint for 400 points? (yes/no) ";
    string answer;
    cin>>answer;
    cin.ignore(100, '\n');
    cout<<"*************************************\n"<<endl;
    if(answer == "yes" || answer == "YES" || answer == "Yes" || answer == "Y" || answer == "y"){
      obstacleCourse *ptr = new roomWithDoors;
      roomWithDoors *dp = dynamic_cast<roomWithDoors*>(ptr); // using dynamic casting to call the "non-self similar" function and experience RTTI
      if(dp != NULL){
        dp->doorHint(deathDoor); // calls the different derived function not mentioned int the abstract base class.
      }
      player1.subtractPoints(400); player1.displayPoints();
    }
  }
  cout<<"\nWhich door will you pick? (1/2/3/4) ";
  cin>>doorNumber;
  cin.ignore(100, '\n');
  cout<<"*************************************\n"<<endl;

  // the following sequence finds the door that the user selected
  if(doorNumber == deathDoor){
    cout<<"You entered the DEATH door!!!"<<endl;
    player1.subtractHeart(1000); // removes all the hearts
    gameOver(player1); // game will end
    cout<<"*************************************\n"<<endl;
    return;
  }else if(doorNumber == winningDoor){
    cout<<"You entered the WINNING door!!!"<<endl;
    player1.GameWin(true);
    gameOver(player1); // game will end with a win
    cout<<"*************************************\n"<<endl;
  }else if(doorNumber == HeartDoor){
    cout<<"Nice, you gained a heart. +1 heart."<<endl;
    player1.subtractHeart(-1); // adds a heart to player
    player1.displayHearts();
    cout<<"*************************************\n"<<endl;
  }else if(doorNumber == pointsDoor){
    cout<<"You just got some points. +150 points."<<endl;
    player1.subtractPoints(-150); // passing in -150 will add 150
    player1.Winner(); // checks if player has 800 points or more to win
    gameOver(player1); // checks if player will end with a win
    player1.displayPoints();
    cout<<"*************************************\n"<<endl;
  }
  return;
} 

bool roomWithDoors::deactivate(){
  int max = 100;
  srand(time(0)); 
  int deac = rand() % max; // generate a random number between 0 and 100
  if(deac % 7 == 0)
    return true; // if random number is divisible by 7, there is a trap deactivation button
  return false; // no trap deactivation
}

// This function tells the user to not pick the death door. It is a very
// useful hint, but it is worth a lot of points.
int roomWithDoors::doorHint(int death){
  cout<<"Whatever you do, DON'T pick door number "<<death<<"!!"<<endl;
  return 0;
}
