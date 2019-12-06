// movies.cpp
// Implements class IntBST
// Jiahao Zhu, 2019/11/7

#include "movies.h"

#include <iostream>
#include <vector>
using std::cout;

// constructor sets up empty tree
Movies::Movies() : root(0) { }

// destructor deletes all nodes
Movies::~Movies() {
    clear(root);
}

// recursive helper for destructor
void Movies::clear(Node *n) {
    if (n) {
	clear(n->left);
	clear(n->right);
	delete n;
    }
}

// insert value in tree; return false if duplicate
bool Movies::insert(string name, double rating) {
    // handle special case of empty tree first
    if (!root) {
	root = new Node(name, rating);
	return true;
    }
    // otherwise use recursive helper
    return insert(name, rating, root);
}

// recursive helper for insert (assumes n is never 0)
bool Movies::insert(string name, double rating, Node *n) {
    //if (name == n->name)
	//return false;
    for (int i = 0; i < n->name.length() && i < name.length(); i++) {
        if ((int)name[i] == 32 && (int)n->name[i] == 32) {
            continue;
        }
        if (name[i] < n->name[i] && (int)name[i] < 0) {
	        if (n->left)
	            return insert(name, rating, n->left);
	        else {
	            n->left = new Node(name, rating);
	            n->left->parent = n;
	            return true;
	        }
        }
        else if (name[i] > n->name[i] || (int)name[i] < 0){
	        if (n->right)
	            return insert(name, rating, n->right);
        	else {
	            n->right = new Node(name, rating);
	            n->right->parent = n;
	            return true;
	        }
        }
    }
    if (name.length() < n->name.length()) {
        if (n->left)
            return insert(name, rating, n->left);
        else {
            n->left = new Node(name, rating);
            n->left->parent = n;
            return true;
        }
    }
    else if (name.length() > n->name.length()){
        if (n->right)
            return insert(name, rating, n->right);
        else {
            n->right = new Node(name, rating);
            n->right->parent = n;
            return true;
        }
    }
    return false;
}

// print tree data pre-order
void Movies::printPreOrder() const {
    int depth = 0;
    printPreOrder(root, depth);
}

// recursive helper for printPreOrder()
void Movies::printPreOrder(Node *n, int depth) const {
    if (n) {
	    cout << n->name << ", " << n->rating << ", " << depth << endl;
	    printPreOrder(n->left, depth + 1);
	    printPreOrder(n->right, depth + 1);
    }
}

//return count of movies
int Movies::count() const {
    return count(root);
}

// recursive helper for count
int Movies::count(Node *n) const {
    if (n) {
        return count(n->left) + count(n->right) + 1;
    }
    return 0;
}

// Parameters:
// string name: the movie name to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
Movies::Node* Movies::getNodeFor(string prefix, Node* n) const{;
    Node* movie = NULL;
    if (n) {
        for (int i = 0; i < n->name.length() && i < prefix.length(); i++) {
            if (&n->name[i] == " " && &prefix[i] == " ") {
                continue;
            }
            else if (n->name[i] > prefix[i]) {
                return getNodeFor(prefix, n->left);
            }
            else if (n->name[i] < prefix[i]) {
                return getNodeFor(prefix, n->right);
            }
        }
        if (prefix.length() <= n->name.length()) {
            if (!movie || n->rating > movie->rating) {
                movie = n;
            }
        }
    }
    return movie;
}

// returns true if value is in the tree; false if not
void Movies::bestMovie(string prefix) const {
    Node* movie = getNodeFor(prefix,root);
    if (movie) {
        cout << endl << "Best movie is " << movie->name << " with rating " << movie->rating << endl;
    }
    else {
        cout << endl;
    }
}

/*

// returns the Node containing the predecessor of the given value
Movies::Node* Movies::getPredecessorNode(int value) const{
    Node* n = getNodeFor(value, root);
    if (n) {
        if (n->left) {
            n = n->left;
            while(n->right) {
                n = n->right;
            }
        }
        else if (n->parent->right == n) {
            n = n->parent;
        }
        else if (n->parent->left == n) {
            Node* temp = n;
            while (temp != root && temp->parent->left == temp) {
                temp = temp->parent;
            }
            if (temp == root) {
                return NULL;
            }
            else {
                n = temp->parent;
            }
        }
        else {
            return NULL;
        }
    }
    return n;
}

// returns the predecessor value of the given value or 0 if there is none
int Movies::getPredecessor(int value) const{
    Node* n = getPredecessorNode(value);
    if (n) {
        return n->info;
    }
    return 0;
}

// returns the Node containing the successor of the given value
Movies::Node* Movies::getSuccessorNode(int value) const{
    Node* n = getNodeFor(value, root);
    if (n) {
        if (n->right) {
            n = n->right;
            while(n->left) {
                n = n->left;
            }
        }
        else if (n->parent->left == n) {
            n = n->parent;
        }
        else if ( n->parent->right == n) {
            Node* temp = n;
            while (temp != root && temp->parent->right == temp) {
                temp = temp->parent;
            }
            if (temp == root) {
                return NULL;
            }
            else {
            n = temp->parent;
            }
        }
        else {
            return NULL;
        }
    }
    return n;
}

// returns the successor value of the given value or 0 if there is none
int Movies::getSuccessor(int value) const{
    Node* n = getSuccessorNode(value);
    if (n) {
        return n->info;
    }
    return 0;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool Movies::remove(int value){
    Node* n = getNodeFor(value, root);
    Node* succ;
    if (n) {
        if (n->left == NULL && n->right == NULL) {
            if (n == root) {
                root = NULL;
            }
            else if (n->parent->right == n) {
                n->parent->right = NULL;
            }
            else if (n->parent->left == n) {
                n->parent->left = NULL;
            }
        }
        else if (n->right == NULL) {
            if (n == root) {
                root = n->left;
                n->left->parent = NULL;
            }
            else if (n->parent->right == n) {
                n->parent->right = n->left;
            }
            else if (n->parent->left == n) {
                n->parent->left = n->left;
            }
        }
        else if (n->left == NULL) {
            if (n == root) {
                root = n->right;
                n->right->parent = NULL;
            }
            else if (n->parent->right == n) {
                n->parent->right = n->right;
            }
            else if (n->parent->left == n) {
                n->parent->left = n->right;
            }
        }
        else if (n->right) {
            succ = n->right;
            if (succ->left == NULL) {
                n->info = succ->info;
                n->right = succ->right;
                n = succ;
            }
            else {
                while(succ->left) {
                    succ = succ->left;
                }
                n->info = succ->info;
                succ->parent->left = succ->right;
                n = succ;
            }
        }
        delete n;
        return true;
    }
    return false;
}

*/
