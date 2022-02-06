// intbst.cpp
// Implements class IntBST
// Ivan Ke, 2/5/22

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() : root(0) { }

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (n) {
	clear(n->left);
	clear(n->right);
	delete n;
    }
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    // handle special case of empty tree first
    if (!root) {
	root = new Node(value);
	return true;
    }
    // otherwise use recursive helper
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (value == n->info)
	return false;
    if (value < n->info) {
	if (n->left)
	    return insert(value, n->left);
	else {
	    n->left = new Node(value);
	    n->left->parent = n;
	    return true;
	}
    }
    else {
	if (n->right)
	    return insert(value, n->right);
	else {
	    n->right = new Node(value);
	    n->right->parent = n;
	    return true;
	}
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (n) {
	cout << n->info << " ";
	printPreOrder(n->left);
	printPreOrder(n->right);
    }
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    // IMPLEMENT HERE
    if(n){
        printInOrder(n->left);
        cout<<n->info << " ";
        printInOrder(n->right);
    }
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    // IMPLEMENT HERE
    if(n){
        printPostOrder(n->left);
        printPostOrder(n->right);
        cout<<n->info << " ";
    }
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    int total = 0;
    if(n){
        total += n->info;
        total += sum(n->left);
        total += sum(n->right);
    }
    return total; // REPLACE THIS NON-SOLUTION
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    int total = 0;
    if(n){
        total++;
        total+= count(n->left);
        total+= count(n->right);
    }
    return total;
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if(n){
        if(n->info == value){
            return n;
        }else if(value < n->info){
            return getNodeFor(value, n->left);
        }else if(value > n->info){
            return getNodeFor(value, n->right);
        }
    }
    return NULL;
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    return bool(getNodeFor(value, root)); // REPLACE THIS NON-SOLUTION
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* node = getNodeFor(value,root);
    if(node){
        if(node->left){
            node = node->left;
            while(node){
                if(node->right){
                    node = node->right;
                }else{
                    return node;
                }
            }
            return NULL;
        } else {
            while(node->parent){
                node = node->parent;
                if(node->info < value){
                    return node;
                }
            }
            return NULL;
        }
    }else{
        return NULL;
    }
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node *node = getPredecessorNode(value);
    if(node){
        return node->info;
    }else{
        return 0;
    }
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node* node = getNodeFor(value,root);
    if(node){
        if(node->right){
            node = node->right;
            while(node){
                if(node->left){
                    node = node->left;
                }else{
                    return node;
                }
            }
            return NULL;
        } else {
            while(node->parent){
                node = node->parent;
                if(node->info > value){
                    return node;
                }
            }
            return NULL;
        }
    }else{
        return NULL;
    }
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node *node = getSuccessorNode(value);
    if(node){
        return node->info;
    }else{
        return 0;
    }
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    Node* n = getNodeFor(value, root);
    if(n){
        if(!n->left && !n->right){//0 children
            if(n == root){
                n->info = 0;
                return true;
            }
            if(n == n->parent->left){
                n->parent->left = NULL;
            }else if(n == n->parent->right){
                n->parent->right = NULL;
            }
            delete n;
        }else if(!n->right){//l child
            if(n == n->parent->left){
                n->parent->left = n->left;
            }else if(n == n->parent->right){
                n->parent->right = n->left;
            }
            delete n;
        }else if(!n->left){//r child
            if(n == n->parent->left){
                n->parent->left = n->right;
            }else if(n == n->parent->right){
                n->parent->right = n->right;
            }
            delete n;
        }else if(n->left && n->right){//2 children, successor
            int tempval = getSuccessor(value);
            bool result = remove(tempval);
            n->info = tempval;
            return result;
        }
        return true;
    }else{
        return false;
    }
}
