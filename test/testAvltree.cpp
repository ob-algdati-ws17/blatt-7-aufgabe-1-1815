//
// Created by S0ras on 04.01.2018.
//
#include "testAvlTree.h"
#include <memory>
#include <avltree/library.h>

using namespace std;

TEST(AvlTreeTest, Insert_Test) {
    AvlTree t;
    t.insert(2);
    EXPECT_TRUE(t.search(2));
}