// Name: Nathan Metens       // CS 202 w/ Karla Fant

// This is the node and array of DLL header file. These are
// teo separate classes with "has a" relationships. The node
// "has a" obstacleCourse abstract base class and the Arr class
// "has a" pointer to a node pointer and "has a" player class.

#include <time.h>
#include "game.h" // used for dynamic binding initialization in the node class 
using namespace std;

// This class manages the nodes and allows for dynamic binding (upcasting) of
// the obstacleCourse abstract base class. This is a DLL node.
class node{
  public:
    node(); 
    node(int random1); // used for setting traps randomly on each node
    ~node();
    node *& getNext(); // returns the address of the next ptr
    node *& getPrev(); // returns the address of the prev ptr
    void setNext(node *dest); // passes the destination for next
    void setPrev(node *dest); // previous is set to the dest
    void displayObstacle(player &player1); // player object passed by reference
  protected:
    obstacleCourse *ptr; // pointer to an obstacle abstract base class for dynamic binding
    node *next; // next ptr for forward movement
    node *prev; // prev ptr for player to move backwards
};

// This is the array implementation that holds a node pointer at each index.
// This class contains a player class object that will be used to keep track
// of the player's hearts and points by reference, updating each as the user
// goes through the obstacle course.
class Arr{ // the array of node ptrs (obstacle course)
  public:
    Arr();
    ~Arr();
    int addNode(); // wrapper function for recursive add
    int addNode(node *& head, int &index); // recursivly adds nodes in the array of DLL
    int display(); // wrapper for display
    int display(int &index); // for moving between indices of the array (left and right)
    int display(node *head, int index); // for displaying the obstacle data and user interface
    int removeAll(); // remove all wrapper function
    int removeAll(int &index); //keeps track of array index
    int removeList(node *& head); // deletes every node in an index's DLL
  private:
    player player1; // player object with hearts, points, name
    int arrSize; // size of the array
    node **head; // a pointer to a dynamically allocated array of node pointers
};
