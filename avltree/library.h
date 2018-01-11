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
        int key;

        ///previous node, left and right child
        Node *left = nullptr;
        Node *right = nullptr;
        Node *previous = nullptr;


        void upin(AvlTree *);
        void upout(AvlTree *);

        ///basic operations
        bool search(const int) const;
        void insert(const int, AvlTree *);

        Node *getNode(const int);
        int getDepth();
        bool checkBalance();
        bool checkBalances();

        void reevaluateBalance();

        ///rotations
        Node* rotateLeft(AvlTree *);
        Node* rotateRight(AvlTree *);
        Node* rotateLeftRight(AvlTree *);
        Node* rotateRightLeft(AvlTree *);

        Node* findSymmetricSuccessor();

    };






public:
    ///root of the tree
    Node *root = nullptr;

    ~AvlTree();

    bool search(const int) const;

    void insert(const int);

    void remove(const int);

    void generatePic();

    void generatePic(const int);

    Node *getNode(const int);

    bool checkBalances();

    friend ostream &operator<<(ostream &, const AvlTree &);

};

#endif