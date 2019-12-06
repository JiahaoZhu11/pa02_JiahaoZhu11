// movies.h
// Binary search tree header file for CS 24 lab

#ifndef MOVIES_H
#define MOVIES_H

#include <iostream>

using namespace std;

class Movies {

 public:

    Movies();                   // constructor
    ~Movies();                  // destructor
    bool insert(int value);     // insert value; return false if duplicate
    void printPreOrder() const; // prints tree data pre-order to cout
    void printInOrder() const;       // print tree data in-order to cout
    void printPostOrder() const;     // print tree data post-order to cout
    int sum() const;                 // sum of all values
    int count() const;               // count of values
    bool contains(int value) const;  // true if value is in tree
    int getPredecessor(int value) const;       // returns the predecessor value of the given value or 0 if there is none
    int getSuccessor(int value) const;         // returns the successor value of the given value or 0 if there is none
    bool remove(int value);                    // deletes the Node containing the given value from the tree

 private:

    struct Node {
        string name;
    	int rating;
	    Node *left, *right, *parent;
	    Node(string n="", int v=0) : name(n), rating(v), left(0), right(0), parent(0) { }
    };

    Node *root;

    //recursive helper functions
    Node* getNodeFor(string name, Node* n) const; //returns the node for a given name or NULL if none exists
    void clear(Node *n); // for destructor
    bool insert(int value, Node *n); // note overloading names for simplicity
    void printPreOrder(Node *n) const;
    void printInOrder(Node *n) const;
    void printPostOrder(Node *n) const;
    int sum(Node *n) const;
    int count(Node *n) const;

    // these should be used by getPredecessor and getSuccessor, and ONE of them should be used by remove
    Node* getSuccessorNode(int value) const;   // returns the Node containing the successor of the given value
    Node* getPredecessorNode(int value) const; // returns the Node containing the predecessor of the given value 
};

#endif
