#ifndef BLATT_7_AUFGABE_1_1815_LIBRARY_H
#define BLATT_7_AUFGABE_1_1815_LIBRARY_H

#include <ostream>

using namespace std;

class AvlTree {

private:

    struct Node {
        ///Constructors and Destructor
        Node(const int);
        Node(const int, Node *, Node *);
        ~Node();

        ///balance and key of the node
        int balance = 0;
        const int key;

        ///previous node, left and right child
        Node *left = nullptr;
        Node *right = nullptr;
        Node *previous = nullptr;


        void upin();

        ///basic operations
        bool search(const int) const;
        void insert(const int);
        Node *remove(const int);

        //rotations
        Node* rotateLeft();
        Node* rotateRight();
        Node* rotateLeftRight();
        Node* rotateRightLeft();
    };



    ///root of the tree
    Node *root = nullptr;


public:
    ~AvlTree();

    bool search(const int) const;

    void insert(const int);

    void remove(const int);



    friend ostream &operator<<(ostream &, const AvlTree &);

};

#endif