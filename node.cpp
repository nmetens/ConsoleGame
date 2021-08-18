// Name: Nathan Metens       // CS 202 w/ Karla Fant

// This is the node.h implementation file. Here the nodes
// for the DLL are initialized and randomized with obstacles
// from the game.cpp file. The Arr class is also implemented
// here. The array is initialized with a random size and then
// holds a randome number of nodes at each index. The Arr 
// display function is the user interaction that allows the user
// to move around the array of DLL (obstacle course). The user
// is able to move forwards and backwards in any index of DLL and
// if the user is at the beginning of a DLL at a new index, then
// they also have the option of going left or right in the array.

#include "node.h"

// *************** Node class member functions ******************//
// **************************************************************//

node::node(): next(0), prev(0), ptr(0) {}

// Initializes the next and prev pointers to NULL and determines
// by random chance which obstacle will be pointed to using dynamic binding.
node::node(int randomNumber): next(0), prev(0){ // initialization list for next and prev ptrs
  srand(randomNumber); // returns a time to generate a random number
  int max = 100;
  randomNumber *= 73; // really trying to randomize the number
  randomNumber = rand() % max; // creates a randum number between 0 and 100
  if(randomNumber >= 0 && randomNumber < 33){
    ptr = new zombieHerd; // dynamic binding of random obstacle for each new node
  }else if(randomNumber >= 33 && randomNumber <66){
    ptr = new lavaTrap; // dynamic binding to the lavatrap obstacle
  }else{ // randomNumber >= 66 && randomNumber <= 100
    ptr = new roomWithDoors; // dynamic binding to the roomWithDoors obstacle
  }
}

node::~node(){ // sets each pointer to NULL
  if(next){
    delete next; next == NULL;
  }
  if(prev){
    delete prev; prev = NULL;
  }
  if(ptr){ // calls the abstract base class's destructor for correct derived obstacle
    delete ptr; ptr = NULL;
  }
}

node *& node::getNext(){ // returns address of next ptr
  return next; 
}

node *& node::getPrev(){ // returns address of prev ptr
  return prev;
}

void node::setNext(node *dest){ // sets the next ptr to given destination
  next = dest;
}

void node::setPrev(node *dest){ // sets prev ptr to dest
  prev = dest;
}

// dynamic binding calling the correct function for the right derived class
void node::displayObstacle(player &player1){ 
  ptr->display(player1); 
}

// ************* Array of DLL member functions ******************//
// **************************************************************//

// This exception is when the user ties going out of the bounds of the array

struct INVALID_INDEX{ // error handling for the index of the array
  int index;
};

Arr::Arr(){
  srand(time(0));
  arrSize = (rand() % 5) + 3; // plus three just so that there are AT LEAST 3 indices and at most 8
  int DLLsize = (rand() % 3) +3; // AT LEAST 3 obstacles per DLL and no more than 6 indices per array
  head = new node*[arrSize]; // allocates array size of node pointers
  int random = rand(); // a random number based on srand and a max of 100

  for(int i=0; i<arrSize; i++){
    head[i] = new node((i+1)*random);
    head[i]->setPrev(head[i]); // creates the first node of each new index, connecting to itself so user doesn't go NULL
    node *temp = head[i]; // temp ptr to traverse new list and add at end

    for(int j=0; j<DLLsize; j++){ // creates the DLL at the index
      temp->getNext() = new node((j+1)*7+(i+j*random)); // randomizing the number
      temp->getNext()->setPrev(temp);
      temp = temp->getNext();
      temp->setNext(temp); // setting next to itself, that way the user cannot go to NULL (out of bounds)
    }
  }
}

Arr::~Arr(){ // destructor calls removeAll function
  removeAll(); // delete each DLL and set each index to NULL
  delete [] *head; // deletes the array
  head = NULL;
}

int Arr::removeAll(){ // wrapper to the recursive functions
  if(head == NULL) return 0; // nothing to delete
  int index = 0; // pass the first index
  return removeAll(index);
}

int Arr::removeAll(int &index){
  if(index == arrSize) return 0; // reached the end of the array
  node *temp = head[index];
  removeList(temp);
  head[index] = NULL; // make the index ptr NULL after deleted list
  index++;
  return removeAll(index); // incriment the index
}

int Arr::removeList(node *& temp){ // go through, deleting the DLL recursively
  if(temp == NULL) return 0;
  node *del = temp;
  temp = temp->getNext();
  delete del; del = NULL;
  return removeList(temp); 
}

// These are the user interaction functions for the entire obstacle course.
// The user has control of the direction they choose to go. The user will
// interact with each random obstacle at each node in the DLL of each index
// in the array.
int Arr::display(){ // this is the display wrapper
  if(head == NULL) return 0;
  int index = 0; // pass index 0 of the array
  return display(index);
}

int Arr::display(int &index){
  INVALID_INDEX invalid; // error handling object created
  if(index == arrSize-1){ // reached the end of the array
    cout<<"******************************************"<<endl;
    cout<<"\nYou have reached the end of the obstacle course."<<endl;
  }
  if(index == 0){
    cout<<"******************************************"<<endl;
    cout<<"\nYou are at the beginning of the obstacle course."<<endl;
  }
  try{ // try this block for the value of index. If the user tries to exit the array bounds we catch them.
    int direction = display(head[index], index); // either 0 for "Left" or 1 for "Right"
    if(direction == 1)
      ++index; // go to the "Right" in the Arr
    else if(direction == 0)
      --index; // go to the "Left" in the Arr
    if(index < 0 or index >= arrSize){
      invalid.index = index;
      throw(index);
    }
    return display(index);
  }
  catch(...){
    cout<<"******************************************"<<endl;
    cout<<"\nYou tried going out of bounds."<<endl; 
    exit(1);
  }
  return 0; 
}

int Arr::display(node *head, int index){
  if(head->getNext() == head){ // the end of a DLL has been reached
    cout<<"##########################################"<<endl;
    cout<<"This is the last obstacle in this ally way.\nYou must go backwards after it..."<<endl;       
    cout<<"##########################################"<<endl;
  }
  if(head->getPrev() == head){  // user is at the start of a DLL at an index of the array
    cout<<"You are at the start of ally way "<<index + 1<<"."<<endl; // tells the user which index they are at, starting at 1
    cout<<"\nGo Forwards, Right, or Left? (F/R/L) "; // directions can be capital or lowercase
    string answer;
    cin>>answer;
    cin.ignore(100,'\n');
    cout<<"******************************************"<<endl;
    if(answer == "R" || answer == "r"){
      return 1;	// right (incrimenting the array index) 
    }else if(answer == "L" || answer == "l"){
      return 0; // left (decrimenting the array index)
    }
  }
  // displays the obstacle course by what the abstract base class is pointing to for the node
  head->displayObstacle(player1); 
  cout<<"\n\nGo forward or backward? (F/B) "; // go down or up a DLL at a particular index
  string answer;
  cin>>answer;
  cin.ignore(100, '\n');
  cout<<"******************************************"<<endl;
  if(answer == "F" || answer == "f"){
    cout<<"Going Forwards..."<<endl;
    return display(head->getNext(), index); // traverse forwards
  }
  cout<<"Going backwards..."<<endl;
  return display(head->getPrev(), index); // traverse backwards
}
