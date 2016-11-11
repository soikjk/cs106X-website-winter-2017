#include "StringSet.h"

// constructor
StringSet::StringSet(){
    root = NULL; // empty set
    count = 0; // no nodes yet
}

// destructor
StringSet::~StringSet(){
    postOrderClear(root);
    root = NULL; // no more tree!
}

void StringSet::postOrderClear(Node *node) {
    // perform a post-order delete to remove each node
    // base case
    if (node == NULL) {
        return;
    }
    postOrderClear(node->left);
    postOrderClear(node->right);
    delete node;
}

// adds a string to the BST
void StringSet::add(string s){
    add(s, root);
}

// overloaded add helper for recursion
// Note: this uses a "reference to a pointer,"
//       which can be tricky to understand!
//       You would be wise to spend time walking through it
//       with drawings!
void StringSet::add(string s, Node *&node) {
    if (node == NULL) {
        node = new Node(s);
        count++;
    } else if (node->str > s) {
        add(s, node->left);
    } else if (node->str < s) {
        add(s, node->right);
    }
}

// returns the string earliest  in the alphabet (empty string if not found)
string StringSet::findMin(){
    if (root == NULL) {
        return ""; // empty tree
    }
    return findMin(root);
}

// overloaded findMin helper for recursion
string StringSet::findMin(Node *node) {
    // base case
    if (node->left == NULL) {
        return node->str;
    }
    return findMin(node->left);
}

// returns the string farthest in the alphabet (throws error if empty)
string StringSet::findMax(){
    if (root == NULL) {
        return ""; // empty tree
    }
    return findMax(root);
}

// overloaded findMax helper for recursion
string StringSet::findMax(Node *node) {
    // base case
    if (node->right == NULL) {
        return node->str;
    }
    return findMax(node->right);
}

bool StringSet::contains(string s) {
    if (root == NULL) {
        return false;
    }
    return contains(s, root);
}

// overloaded contains helper for recursion
bool StringSet::contains(string &s, Node *node) {
    // base cases
    if (node == NULL) {
        return false;
    }
    if (node->str == s) {
        return true;
    }
    return contains(s,node->left) || contains(s,node->right);
}

// removes string from the set
void StringSet::remove(string s){
    if (root != NULL) {
        Node *removedNode;
        if (root->str == s) { // root holds value to remove
            // create dummy node, and set root to its left
            Node dummyNode("");
            dummyNode.left = root;
            removedNode = remove(s,root,&dummyNode);
        }
        else {
            removedNode = remove(s,root,NULL);
        }
        if (removedNode != NULL) {
            delete removedNode;
            count--;
        }
    }
}

// overloaded remove helper for recursion
Node *StringSet::remove(string &s, Node *node, Node *parent) {
    if (s < node->str) {
        if (node->left != NULL) {
            return remove(s,node->left,node);
        } else {
            return NULL;
        }
    } else if (s > node->str) {
        if (node->right != NULL) {
            return remove(s,node->right,node);
        }
        else {
            return NULL;
        }
    } else { // we found the node to remove
        if (node->left != NULL && node->right != NULL) {
            // two children
            node->str = findMin(node->right);
            return remove(node->str,node->right,node);
        } else if (parent->left == node) {
            parent->left = (node->left != NULL) ? node->left : node->right;
            return node;
        } else if (parent->right == node) {
            parent->right = (node->left != NULL) ? node->left : node->right;
            return node;
        }
    }
    return NULL;
}

// returns the number of nodes in the tree
int StringSet::size() {
    return count;
}

// returns true if the tree is empty
bool StringSet::isEmpty() {
    return root == NULL;
    // also could return count == 0
}

// overloads << to print set in order
ostream &operator<<(ostream &out, StringSet &set){
    string max = set.findMax();
    out << "[";
    set.inOrderTraversal(out,set.root,max);
    out << "]";
    return out;
}

// Traverses the tree in order and adds each node's value to the stream
// Note: needs "max" so we don't print a comma after the last node's value
//       (because we want it to be pretty!)
void StringSet::inOrderTraversal(ostream &out, Node *node, string &max) {
    if (node == NULL) {
        return;
    }
    inOrderTraversal(out, node->left, max);
    out << node->str;
    if (node->str != max) {
        out << ", ";
    }
    inOrderTraversal(out, node->right, max);
}
