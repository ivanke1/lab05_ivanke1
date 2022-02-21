// intbst.cpp
// Implements class IntBST
// Ivan Ke, 2/5/22

#include <iostream>
using std::cout;

// constructor sets up empty tree
template<class T>
IntBST<T>::IntBST() : root(nullptr) { }

// destructor deletes all nodes
template<class T>
IntBST<T>::~IntBST() {
    clear(root);
}

// recursive helper for destructor
template<class T>
void IntBST<T>::clear(Node *n) {
    if (n) {
	clear(n->left);
	clear(n->right);
	delete n;
    }
}

// insert value in tree; return false if duplicate
template<class T>
bool IntBST<T>::insert(T value) {
    // handle special case of empty tree first
    if (!root) {
	root = new Node(value);
	return true;
    }
    // otherwise use recursive helper
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
template<class T>
bool IntBST<T>::insert(T value, Node *n) {
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
template<class T>
void IntBST<T>::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
template<class T>
void IntBST<T>::printPreOrder(Node *n) const {
    if (n) {
	cout << n->info << " ";
	printPreOrder(n->left);
	printPreOrder(n->right);
    }
}

// print tree data in-order, with helper
template<class T>
void IntBST<T>::printInOrder() const {
    printInOrder(root);
}
template<class T>
void IntBST<T>::printInOrder(Node *n) const {
    // IMPLEMENT HERE
    if(n){
        printInOrder(n->left);
        cout<<n->info << " ";
        printInOrder(n->right);
    }
}

// prints tree data post-order, with helper
template<class T>
void IntBST<T>::printPostOrder() const {
    printPostOrder(root);
}

template<class T>
void IntBST<T>::printPostOrder(Node *n) const {
    // IMPLEMENT HERE
    if(n){
        printPostOrder(n->left);
        printPostOrder(n->right);
        cout<<n->info << " ";
    }
}

// return sum of values in tree
template<class T>
int IntBST<T>::sum() const {
    return sum(root);
}

// recursive helper for sum
template<class T>
int IntBST<T>::sum(Node *n) const {
    int total = 0;
    if(n){
        total += n->info;
        total += sum(n->left);
        total += sum(n->right);
    }
    return total; // REPLACE THIS NON-SOLUTION
}

// return count of values
template<class T>
int IntBST<T>::count() const {
    return count(root);
}

// recursive helper for count
template<class T>
int IntBST<T>::count(Node *n) const {
    int total = 0;
    if(n){
        total++;
        total+= count(n->left);
        total+= count(n->right);
    }
    return total;
}

// IMPLEMENT THIS FIRST: returns the node for a given value or nullptr if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
template<class T>
typename IntBST<T>::Node* IntBST<T>::getNodeFor(T value, Node* n) const{
    if(n){
        if(n->info == value){
            return n;
        }else if(value < n->info){
            return getNodeFor(value, n->left);
        }else if(value > n->info){
            return getNodeFor(value, n->right);
        }
    }
    return nullptr;
}

// returns true if value is in the tree; false if not
template<class T>
bool IntBST<T>::contains(T value) const {
    return bool(getNodeFor(value, root)); // REPLACE THIS NON-SOLUTION
}

// returns the Node containing the predecessor of the given value
template<class T>
typename IntBST<T>::Node* IntBST<T>::getPredecessorNode(T value) const{
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
            return nullptr;
        } else {
            while(node->parent){
                node = node->parent;
                if(node->info < value){
                    return node;
                }
            }
            return nullptr;
        }
    }else{
        return nullptr;
    }
}

// returns the predecessor value of the given value or 0 if there is none
template<class T>
T IntBST<T>::getPredecessor(T value) const{
    Node *node = getPredecessorNode(value);
    if(node){
        return node->info;
    }else{
        return 0;
    }
}

// returns the Node containing the successor of the given value
template<class T>
typename IntBST<T>::Node* IntBST<T>::getSuccessorNode(T value) const{
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
            return nullptr;
        } else {
            while(node->parent){
                node = node->parent;
                if(node->info > value){
                    return node;
                }
            }
            return nullptr;
        }
    }else{
        return nullptr;
    }
}

// returns the successor value of the given value or 0 if there is none
template<class T>
T IntBST<T>::getSuccessor(T value) const{
    Node *node = getSuccessorNode(value);
    if(node){
        return node->info;
    }else{
        return 0;
    }
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
template<class T>
bool IntBST<T>::remove(T value){
    Node* n = getNodeFor(value, root);
    if(n){
        if(!n->left && !n->right){//0 children
            if(n == root){
                root = nullptr;
                return true;
            }
            if(n == n->parent->left){
                n->parent->left = nullptr;
            }else if(n == n->parent->right){
                n->parent->right = nullptr;
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
            T tempval = getSuccessor(value);
            bool result = remove(tempval);
            n->info = tempval;
            return result;
        }
        return true;
    }else{
        return false;
    }
}
