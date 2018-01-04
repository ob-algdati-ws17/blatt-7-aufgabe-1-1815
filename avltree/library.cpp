#include "library.h"

#include <iostream>


AvlTree::Node::Node(const int value): key(value) {

}

AvlTree::Node::Node(const int value, AvlTree::Node *l, AvlTree::Node *r): key(value), left(l), right(r) {

}

///Destructors
AvlTree::Node::~Node() {
    if(left != nullptr)delete left;
    if(right != nullptr)delete right;
}


AvlTree::~AvlTree() {

}



///Search
bool AvlTree::search(const int value) const {
    if(root == nullptr)return false;
    return root->search(value);
}

bool AvlTree::Node::search(const int value) const {
    if(this->key == value)return true;
    if(value < key  && this->left == nullptr)return this->left->search(value);
    if(value > key  && this->right == nullptr)return this->right->search(value);
    return false;
}



///Insert
void AvlTree::insert(const int value) {
    //case: empty tree
    if(root == nullptr)root = new Node(value);
    else root->insert(value);
}

void AvlTree::Node::insert(const int value) {
    //normal binary search and insertion
    if(value == key)return;
    if(value < key){
        if(left == nullptr){
            left = new Node(value);
            left->previous = this;
        }
        else left->insert(value);
    }
    else if(value > key){
        if(right == nullptr){
            right = new Node(value);
            right->previous = this;
        }
        else right->insert(value);
    }

    //Update, can be shortened
    switch(balance){
        case +1:
            balance = 0;
            break;
        case -1:
            balance = 0;
            break;
        case 0:
            if(value > key){
                balance = 1;
            }else {
                balance = -1;
            }
            upin();
            break;
    }
}

///upin
void AvlTree::Node::upin(){
    //check if root is reached
    if(previous== nullptr)return;

    ///Fall 1: p ist linker Nachfolger von φp
    if(previous->left->key == key) {
        switch (previous->balance) {
            case 1:
                previous->balance = 0;
                break;
            case 0:
                previous->balance = -1;
                previous->upin();
                break;
            case -1:
                ///the left part of the tree was already bigger
                if(key == -1){ ///case 1.3.1
                    rotateRight();
                }
                else if(key == 1){ ///case 1.3.2
                    rotateLeftRight();
                }
                break;
        }
    }
    ///Fall 2: p ist rechter Nachfolger von φp
    else{
        switch (previous->balance) {
            case -1:
                previous->balance = 0;
                break;
            case 0:
                previous->balance = +1;
                previous->upin();
                break;
            case 1:
                ///the left part of the tree was already bigger
                if(key == 1){ ///case 1.3.1
                    rotateLeft();
                }
                else if(key == -1){ ///case 1.3.2
                    rotateRightLeft();
                }
                break;
        }
    }



};


///Rotations!
AvlTree::Node *AvlTree::Node::rotateLeft() {
    return nullptr;
}

AvlTree::Node *AvlTree::Node::rotateRight() {
    return nullptr;
}

AvlTree::Node *AvlTree::Node::rotateLeftRight() {
    return nullptr;
}

AvlTree::Node *AvlTree::Node::rotateRightLeft() {
    return nullptr;
}


///Remove
void AvlTree::remove(const int value) {

}

AvlTree::Node *AvlTree::Node::remove(const int value) {
    return nullptr;
}



ostream &operator<<(ostream &outputstream, const AvlTree &tree) {
    return outputstream;
}
