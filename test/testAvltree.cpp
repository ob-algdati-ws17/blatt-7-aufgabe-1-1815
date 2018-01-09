//
// Created by S0ras on 04.01.2018.
//
#include "testAvlTree.h"
#include <memory>
#include <avltree/library.h>

using namespace std;


TEST(AvlTreeTest, Depth_Test){
    AvlTree t;
    t.insert(7);
    t.insert(5);
    t.insert(9);
    t.insert(4);
    t.insert(8);
    t.insert(6);
    t.generatePic(100);
    EXPECT_TRUE(t.getNode(7)->getDepth() == 3);
    EXPECT_TRUE(t.getNode(9)->getDepth() == 2);
    EXPECT_TRUE(t.getNode(8)->getDepth() == 1);

}


TEST(AvlTreeTest, Insert_Test) {
    AvlTree t;
    t.insert(50);
    t.generatePic(1);
    t.insert(10);
    t.generatePic(2);
    t.insert(30);
    t.generatePic(3);
    t.insert(40);
    t.generatePic(4);
    t.insert(60);
    t.generatePic(5);
    t.insert(55);
    t.generatePic(6);

    t.generatePic();
    EXPECT_TRUE(t.search(50));
}

TEST(AvlTreeTest, RotateRight_Test){
    AvlTree t;
    t.insert(3);
    t.insert(2);
    t.insert(1);
    t.generatePic(10);
}

TEST(AvlTreeTest, RotateLeft_Test){
    AvlTree t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.generatePic(11);
}

TEST(AvlTreeTest, RotateLeftRight_Test){
    AvlTree t;
    t.insert(3);
    t.insert(1);
    t.insert(2);
    t.generatePic(12);
}

TEST(AvlTreeTest, RotateRightLeft_Test){
    AvlTree t;
    t.insert(1);
    t.insert(3);
    t.insert(2);
    t.generatePic(13);
}


TEST(AvlTreeTest, Big_Test){
    AvlTree t;
    t.insert(1);
    t.generatePic(21);
    t.insert(9);
    t.generatePic(22);
    t.insert(8);
    t.generatePic(23);
    t.insert(3);
    t.generatePic(24);
    t.insert(5);
    t.generatePic(25);
    t.insert(12);
    t.generatePic(26);
    t.insert(4);
    t.generatePic(27);
    t.insert(6);
    t.generatePic(28);
    t.insert(2);
    t.generatePic(29);
    t.insert(7);
    t.generatePic(30);
    t.insert(11);
    t.generatePic(31);
    t.insert(10);
    t.generatePic(32);
    t.generatePic(14);
}