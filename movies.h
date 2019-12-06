// movies.h
// Binary search tree header file for CS 24 lab

#ifndef MOVIES_H
#define MOVIES_H

#include <iostream>

using namespace std;

class Movies {

 public:

    Movies();                               // constructor
    ~Movies();                              // destructor
    bool insert(string name, double rating);// insert movie name and rating; return false if duplicate
    void printPreOrder() const;             // prints tree data pre-order to cout
    int count() const;                      // count of movies
    void bestMovie(string prefix) const;    // true if movie is in tree
    int getPredecessor(int value) const;    // returns the predecessor of the given name or "" if there is none
    int getSuccessor(int value) const;      // returns the successor of the given name or "" if there is none

 private:

    struct Node {
        string name;
        double rating;
	    Node *left, *right, *parent;
	    Node(string n="", double r=0.0) : name(n), rating(r), left(0), right(0), parent(0) { }
    };

    Node *root;

    //recursive helper functions
    Node* getNodeFor(string name, Node* n) const; //returns the node for a given name or NULL if none exists
    void clear(Node *n); // for destructor
    bool insert(string name, double rating, Node *n); // note overloading names for simplicity
    void printPreOrder(Node *n, int depth) const;
    int count(Node *n) const;

    // these should be used by getPredecessor and getSuccessor, and ONE of them should be used by remove
    Node* getSuccessorNode(int value) const;   // returns the Node containing the successor of the given value
    Node* getPredecessorNode(int value) const; // returns the Node containing the predecessor of the given value 
};

#endif
