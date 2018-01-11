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
    if(value < key  && this->left != nullptr)return this->left->getNode(value);
    if(value > key  && this->right != nullptr)return this->right->getNode(value);
    return nullptr;
}


///Insert
void AvlTree::insert(const int value) {
    //case: empty tree
    if(root == nullptr)root = new Node(value);
    else root->insert(value, this);
    checkBalances();
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
    return x;
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
    return x;
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


    //fix balances
    x->reevaluateBalance();
    z->reevaluateBalance();

    return y;
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

    //fix balances
    x->reevaluateBalance();
    z->reevaluateBalance();
    return y;
}


///Remove
void AvlTree::remove(const int value) {
    auto toRemove = getNode(value);
    if(toRemove == nullptr)return;

    //both succesors are leaves
    if(toRemove->left == nullptr && toRemove->right == nullptr){
        auto prev = toRemove->previous;
        Node* q;
        if(prev->left != nullptr && prev->left->key == toRemove->key){ // toRemove is left successor
            prev->left = nullptr;
            q = prev->right;

            if(q == nullptr){ // q has depth 0
                prev->balance = 0;
                prev->upout(this);
            }
            else if( q->getDepth() == 1){ // q has depth 1
                prev->balance = 1;
            }
            else { // q has depth 2
                if(q->balance == 0) // q has 2 succs
                {
                    q->rotateLeft(this)->upout(this);
                } else if(q->balance = 1){ // q has right succ
                    q->rotateLeft(this)->upout(this);
                }else { // q has left succ
                    q->rotateRightLeft(this)->upout(this);
                }
            }

        }else { // toRemove is right successor
            prev->right = nullptr;
            q = prev->left;

            if(q == nullptr){ // q has depth 0
                prev->balance = 0;
                prev->upout(this);
            }
            else if( q->getDepth() == 1){ // q has depth 1
                prev->balance = -1;
            }
            else { // q has depth 2
                if(q->balance == 0) // q has 2 succs
                {
                    q->rotateRight(this)->upout(this);
                } else if(q->balance = 1){ // q has right succ
                    q->rotateLeftRight(this)->upout(this);
                }else { // q has left succ
                    q->rotateRight(this)->upout(this);
                }
            }
        }
        delete toRemove;



    }//both are inner knots
    else if(toRemove->right != nullptr && toRemove->left != nullptr){
        auto symsucc = toRemove->right->findSymmetricSuccessor();
        ///should instead refactor the remove method into two, one to remove nodes
        int tmp = toRemove->key;
        toRemove->key = symsucc->key;
        symsucc->key = tmp;
        remove(tmp);
    }//one is a leaf
    else {
        if(toRemove->right != nullptr){
            toRemove->key = toRemove->right->key;
            toRemove->right = nullptr;
        }
        else {
            toRemove->key = toRemove->left->key;
            toRemove->left = nullptr;
        }
        toRemove->upout(this);
    }


}

//finds symmetric succesor, needs to be called with the root of the right part of the tree
AvlTree::Node *AvlTree::Node::findSymmetricSuccessor() {
    auto smallest = this;
    if(left != nullptr){
        auto l = left->findSymmetricSuccessor();
        if(l->key < smallest->key)smallest = l;
    }
    if(right != nullptr){
        auto r = right->findSymmetricSuccessor();
        if(r->key < smallest->key)smallest =r ;
    }
    return smallest;
}

//upout
void AvlTree::Node::upout(AvlTree *tree) {
    if(previous== nullptr)return;
    auto prev = this->previous;
    if(prev->left != nullptr && prev->left->key == key){ //p is left successor
        switch(prev->balance){
            case -1:
                prev->balance = 0;
                prev->upout(tree);
                break;
            case 0:
                prev->balance = 1;
                break;
            case 1: //right tree was higher than left
                if(prev->right->balance == 0){ //1.3.1
                    prev->rotateLeft(tree);
                }
                else if (prev->right->balance == 1){ //1.3.2
                    prev->rotateLeft(tree)->upout(tree);
                }
                else { // 1.3.3
                    prev->rotateLeftRight(tree)->upout(tree);
                }
                break;
        }
    }
    else { // p is right successor
        switch(prev->balance){
            case 1:
                prev->balance = 0;
                prev->upout(tree);
                break;
            case 0:
                prev->balance = -1;
                break;
            case -1: //left tree was higher than right
                if(prev->left->balance == 0){ //1.3.1 rev
                    prev->rotateRight(tree);
                }
                else if (prev->left->balance == 1){ //1.3.3 rev
                    prev->rotateRightLeft(tree)->upout(tree);
                }
                else { // 1.3.2 rev
                    prev->rotateRight(tree)->upout(tree);
                }
                break;
        }
    }

}


//
void AvlTree::Node::reevaluateBalance() {
    int ld, rd;
    if(left != nullptr)ld = left->getDepth();
    else ld = 0;
    if(right != nullptr)rd = right->getDepth();
    else rd = 0;

    balance = rd -ld;
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


///Debug methods


bool AvlTree::checkBalances() {
    return root->checkBalances();

}

bool AvlTree::Node::checkBalances() {
    checkBalance();
    if(left != nullptr)left->checkBalances();
    if(right != nullptr)right->checkBalances();
    return true;
}

bool AvlTree::Node::checkBalance() {
    int l;
    int r;
    if(left != nullptr)l= left->getDepth();
    else l = 0;
    if(right != nullptr)r= right->getDepth();
    else r = 0;
    int expected = r - l ;
    if(expected != balance ){
        cout << "Balance of " << key << " at depth " << getDepth() << " is " << balance << " but should be " << expected << endl;
        return false;
    }
    return true;
}

int AvlTree::Node::getDepth() {
    if(left == nullptr){
        if(right == nullptr){
            return 1;
        }
        return right->getDepth()+1;
    }else {
        if(right == nullptr){
            return left->getDepth() +1;
        }
        else {
            int r = right->getDepth();
            int l = left->getDepth();
            if(r > l)return r +1;
            return l +1;
        }
    }
}
