#include "library.h"

#include <iostream>
#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>


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

///Get

AvlTree::Node *AvlTree::getNode(const int value) {
    if(root == nullptr)return nullptr;
    return root->getNode(value);
}

AvlTree::Node *AvlTree::Node::getNode(const int value) {
    if(this->key == value)return this;
    if(value < key  && this->left == nullptr)return this->left->getNode(value);
    if(value > key  && this->right == nullptr)return this->right->getNode(value);
    return nullptr;
}


///Insert
void AvlTree::insert(const int value) {
    //case: empty tree
    if(root == nullptr)root = new Node(value);
    else root->insert(value, this);
}

void AvlTree::Node::insert(const int value, AvlTree *tree) {
    //normal binary search and insertion
    if(value == key)return;
    if(value < key){
        if(left == nullptr){
            left = new Node(value);
            left->previous = this;
        }
        else {
            left->insert(value, tree);
            return;
        }
    }
    else if(value > key){
        if(right == nullptr){
            right = new Node(value);
            right->previous = this;
        }
        else {
            right->insert(value, tree);
            return;
        }

    }

    //Update, can be shortened
    //should only be called once
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
            upin(tree);
            break;
    }
}

///upin
void AvlTree::Node::upin(AvlTree *tree){
    //check if root is reached
    if(previous== nullptr)return;

    ///Fall 1: p ist linker Nachfolger von φp
    if(previous->left != nullptr  && previous->left->key == key) {
        switch (previous->balance) {
            case 1:
                previous->balance = 0;
                break;
            case 0:
                previous->balance = -1;
                previous->upin(tree);
                break;
            case -1:
                ///the left part of the tree was already bigger
                if(balance == -1){ ///case 1.3.1
                    rotateRight(tree);
                }
                else if(balance == 1){ ///case 1.3.2
                    rotateLeftRight(tree);
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
                previous->upin(tree);
                break;
            case 1:
                ///the left part of the tree was already bigger
                if(balance == 1){ ///case 1.3.1
                    rotateLeft(tree);
                }
                else if(balance == -1){ ///case 1.3.2
                    rotateRightLeft(tree);
                }
                break;
        }
    }



};


///Rotations!
AvlTree::Node *AvlTree::Node::rotateLeft(AvlTree *tree) {
    auto ypre = previous->previous;
    auto y = previous;
    auto x = this;
    auto t1 = y->left;
    auto t2 = left;
    auto t3 = right;


    //find out if y is left or right child, update root if needed
    if(ypre != nullptr){
        if(ypre->left != nullptr  &&ypre->left->key == y->key) { //left child
            ypre->left = x;
        }else { //right child
            ypre->right = x;
        }
    }else {
        tree->root = x;
    }
    x->balance = 0;
    x->previous = ypre;

    y->balance = 0;
    x->left = y;
    y->previous = x;

    y->left = t1;
    if(t1 != nullptr)t1->previous = y;

    y->right = t2;
    if(t2 != nullptr)t2->previous = y;
    return nullptr;
}

AvlTree::Node *AvlTree::Node::rotateRight(AvlTree *tree) {
    auto ypre = previous->previous;
    auto y = previous;
    auto x = this;
    auto t1 = left;
    auto t2 = right;
    auto t3 = y->right;

    //find out if y is left or right child, update root if needed
    if(ypre != nullptr){
        if(ypre->left != nullptr  &&ypre->left->key == y->key) { //left child
            ypre->left = x;
        }else { //right child
            ypre->right = x;
        }
    }else {
        tree->root = x;
    }
    x->balance = 0;
    x->previous = ypre;

    y->balance = 0;
    x->right = y;
    y->previous = x;

    y->left = t2;
    if(t2 != nullptr)t2->previous = y;

    y->right = t3;
    if(t3 != nullptr)t3->previous = y;
    return nullptr;
}

AvlTree::Node *AvlTree::Node::rotateLeftRight(AvlTree *tree) {
    auto zpre = previous->previous;
    auto z = previous;
    auto x = this;
    auto y = right;
    auto t1 = left;
    auto t2 = y->left;
    auto t3 = y->right;
    auto t4 = z->right;
    int h = y->balance;

    //find out if z is left or right child
    if(zpre != nullptr){
        if(zpre->left != nullptr  && zpre->left->key == z->key) { //left child
            zpre->left = y;
        }else { //right child
            zpre->right = y;
        }
    }else { //update root
        tree->root = y;
    }
    y->balance = 0;
    y->previous = zpre;

    //x and childs
    y->left = x;
    x->previous = y;
    x->balance = h;

    x->left = t1;
    if(t1 != nullptr)t1->previous = x;

    x->right = t2;
    if(t2 != nullptr)t2->previous = x;

    //z and childs
    y->right = z;
    z->previous = y;
    z->balance = h;

    z->left = t3;
    if(t3 != nullptr)t3->previous = z;

    z->right = t4;
    if(t4 != nullptr)t4->previous = z;

    return nullptr;
}

AvlTree::Node *AvlTree::Node::rotateRightLeft(AvlTree *tree) {
    auto zpre = previous->previous;
    auto z = previous;
    auto x = this;
    auto y = left;
    auto t4 = right;
    auto t3 = y->right;
    auto t2 = y->left;
    auto t1 = z->left;
    int h = y->balance;

    //find out if z is left or right child
    if(zpre != nullptr){
        if(zpre->left != nullptr  && zpre->left->key == z->key) { //left child
            zpre->left = y;
        }else { //right child
            zpre->right = y;
        }
    }else { //update root
        tree->root = y;
    }
    y->balance = 0;
    y->previous = zpre;

    //x and childs
    y->right = x;
    x->previous = y;
    x->balance = h;

    x->left = t1;
    if(t1 != nullptr)t1->previous = x;

    x->right = t2;
    if(t2 != nullptr)t2->previous = x;

    //z and childs
    y->left = z;
    z->previous = y;
    z->balance = h;

    z->left = t3;
    if(t3 != nullptr)t3->previous = z;

    z->right = t4;
    if(t4 != nullptr)t4->previous = z;
    return nullptr;
}


///Remove
void AvlTree::remove(const int value) {

}

AvlTree::Node *AvlTree::Node::remove(const int value) {
    return nullptr;
}



/********************************************************************
 * operator<<
 *******************************************************************/
std::ostream &operator<<(std::ostream &os, const AvlTree &tree) {
    function<void(std::ostream &, const int, const AvlTree::Node *, const string)> printToOs
            = [&](std::ostream &os, const int value, const AvlTree::Node *node, const string l) {

                static int nullcount = 0;

                if (node == nullptr) {
                    os << "    null" << nullcount << "[shape=point];" << endl;
                    os << "    " << value << " -> null" << nullcount
                       << " [label=\"" << l << "\"];" << endl;
                    nullcount++;
                } else {
                    os << "    " << value << " -> " << node->key
                       << " [label=\"" << l << "\"];" << endl;

                    printToOs(os, node->key, node->left, "l");
                    printToOs(os, node->key, node->right, "r");
                }
            };
    os << "digraph tree {" << endl;
    if (tree.root == nullptr) {
        os << "    null " << "[shape=point];" << endl;
    } else {
        printToOs(os, tree.root->key, tree.root->left, "l");
        printToOs(os, tree.root->key, tree.root->right, "r");
    }
    os << "}" << endl;
    return os;
}

void AvlTree::generatePic() {
    ofstream myfile;
    myfile.open("tree.dot");
    myfile << *this;
    myfile.close();
    system("dot -Tpng tree.dot -o tree.png");
}

void AvlTree::generatePic(const int n) {
    ofstream myfile;
    std::stringstream tmp;
    tmp << "tree" << n << ".dot";
    myfile.open(tmp.str());
    myfile << *this;
    myfile.close();
    std::stringstream tmp2;
    tmp2 << "dot -Tpng tree" << n << ".dot" << " -o tree" << n << ".png";
    system(tmp2.str().c_str());
}
