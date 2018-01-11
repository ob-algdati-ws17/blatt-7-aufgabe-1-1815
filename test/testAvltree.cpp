#include "testAvltree.h"
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
    //t.generatePic(100);
    EXPECT_TRUE(t.getNode(7)->getDepth() == 3);
    EXPECT_TRUE(t.getNode(9)->getDepth() == 2);
    EXPECT_TRUE(t.getNode(8)->getDepth() == 1);

}


TEST(AvlTreeTest, Insert_Test) {
    AvlTree t;
    t.insert(50);
    //t.generatePic(1);
    t.insert(10);
    //t.generatePic(2);
    t.insert(30);
    //t.generatePic(3);
    t.insert(40);
    //t.generatePic(4);
    t.insert(60);
    //t.generatePic(5);
    t.insert(55);
    //t.generatePic(6);

    //t.generatePic();
    EXPECT_TRUE(t.search(50));
}

TEST(AvlTreeTest, RotateRight_Test){
    AvlTree t;
    t.insert(3);
    t.insert(2);
    t.insert(1);
    //t.generatePic(10);
}

TEST(AvlTreeTest, RotateLeft_Test){
    AvlTree t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    //t.generatePic(11);
}

TEST(AvlTreeTest, RotateLeftRight_Test){
    AvlTree t;
    t.insert(3);
    t.insert(1);
    t.insert(2);
    //t.generatePic(12);
}

TEST(AvlTreeTest, RotateRightLeft_Test){
    AvlTree t;
    t.insert(1);
    t.insert(3);
    t.insert(2);
    //t.generatePic(13);
}


TEST(AvlTreeTest, Big_Test){
    AvlTree t;
    t.insert(1);
    //t.generatePic(21);
    t.insert(9);
    //t.generatePic(22);
    t.insert(8);
    //t.generatePic(23);
    t.insert(3);
    //t.generatePic(24);
    t.insert(5);
    //t.generatePic(25);
    t.insert(12);
    //t.generatePic(26);
    t.insert(4);
    //t.generatePic(27);
    t.insert(6);
    //t.generatePic(28);
    t.insert(2);
    //t.generatePic(29);
    t.insert(7);
    //t.generatePic(30);
    t.insert(11);
    //t.generatePic(31);
    t.insert(10);
    //t.generatePic(32);
}

TEST(AVLTest, SymmetricSuccsor_Test){
    AvlTree *t = new AvlTree;
    t->insert(5);
    t->insert(4);
    t->insert(9);
    t->insert(10);

    EXPECT_TRUE(t->getNode(9)->findSymmetricSuccessor()->key == 9);
    EXPECT_TRUE(t->root->findSymmetricSuccessor()->key == 4);
    EXPECT_TRUE(t->getNode(4)->findSymmetricSuccessor()->key == 4);
}

// for following testcases visualisation see: https://stackoverflow.com/a/13843966

TEST(AVLTest, Left_Right) {
    AvlTree *t= new AvlTree();
    t->insert(20);
    t->insert(4);
    t->insert(15);
    EXPECT_TRUE(t->root->key==15);
    EXPECT_TRUE(t->root->left->key==4);
    EXPECT_TRUE(t->root->right->key==20);
}

TEST(AVLTest, Triple_Rotate_Right) {
    AvlTree *t= new AvlTree();
    t->insert(20);
    t->insert(4);
    t->insert(26);
    t->insert(3);
    t->insert(9);
    t->insert(15);
    EXPECT_TRUE(t->root->key==9);
    EXPECT_TRUE(t->root->left->key==4);
    EXPECT_TRUE(t->root->left->left->key==3);
    EXPECT_TRUE(t->root->right->key==20);
    EXPECT_TRUE(t->root->right->right->key==26);
    EXPECT_TRUE(t->root->right->left->key==15);
}

TEST(AVLTest, Triple_Rotate_Left) {
    AvlTree *t= new AvlTree();
    t->insert(20);
    t->insert(4);
    t->insert(26);
    t->insert(3);
    t->insert(9);
    t->insert(8);
    EXPECT_TRUE(t->root->key==9);
    EXPECT_TRUE(t->root->left->key==4);
    EXPECT_TRUE(t->root->left->left->key==3);
    EXPECT_TRUE(t->root->left->right->key==8);
    EXPECT_TRUE(t->root->right->key==20);
    EXPECT_TRUE(t->root->right->right->key==26);
}

TEST(AVLTest, Remove_Rotate) {
    AvlTree *t= new AvlTree();
    t->insert(2);
    t->insert(4);
    t->insert(1);
    t->insert(3);
    t->insert(5);
    t->remove(1);
    EXPECT_TRUE(t->root->key==4);
    EXPECT_TRUE(t->root->left->key==2);
    EXPECT_TRUE(t->root->left->right->key==3);
    EXPECT_TRUE(t->root->right->key==5);
}

TEST(AVLTest, Remove_Multi_Rotate) {
    AvlTree *t= new AvlTree();
    t->insert(5);
    t->insert(2);
    t->insert(8);
    t->insert(1);
    t->insert(3);
    t->insert(7);
    t->insert(10);
    t->insert(4);
    t->insert(6);
    t->insert(9);
    t->insert(11);
    t->insert(12);
    //t->generatePic(1234);
    t->remove(1);
    //t->generatePic(1235);

    EXPECT_TRUE(t->root->key==8);
    EXPECT_TRUE(t->root->left->key==5);
    EXPECT_TRUE(t->root->left->left->key==3);
    EXPECT_TRUE(t->root->left->left->left->key==2);
    EXPECT_TRUE(t->root->left->left->right->key==4);
    EXPECT_TRUE(t->root->left->right->key==7);
    EXPECT_TRUE(t->root->left->right->left->key==6);

    EXPECT_TRUE(t->root->right->key==10);
    EXPECT_TRUE(t->root->right->left->key==9);
    EXPECT_TRUE(t->root->right->right->key==11);
    EXPECT_TRUE(t->root->right->right->right->key==12);
}

TEST(AVLTest, Remove_1L){
    AvlTree *t = new AvlTree();
    t->insert(2);
    t->insert(1);
    t->insert(3);
    t->insert(4);
    t->remove(1);
    EXPECT_TRUE(t->root->key == 3);
    EXPECT_TRUE(t->root->left->key == 2);
    EXPECT_TRUE(t->root->right->key == 4);
}

TEST(AVLTest, Remove_1R){
    AvlTree *t = new AvlTree();
    t->insert(3);
    t->insert(4);
    t->insert(2);
    t->insert(1);
    t->remove(4);
    EXPECT_TRUE(t->root->key == 2);
    EXPECT_TRUE(t->root->left->key == 1);
    EXPECT_TRUE(t->root->right->key == 3);
}

TEST(AVLTest, Remove_2L){
    AvlTree *t = new AvlTree();
    t->insert(2);
    t->insert(1);
    t->insert(4);
    t->insert(3);
    t->remove(1);
    EXPECT_TRUE(t->root->key == 3);
    EXPECT_TRUE(t->root->left->key == 2);
    EXPECT_TRUE(t->root->right->key == 4);
}


//More complex cases

TEST(AVLTest, Remove_1_req_1L_at_3){
    AvlTree *t = new AvlTree();
    t->insert(3);
    t->insert(2);
    t->insert(5);
    t->insert(1);
    t->insert(4);
    t->insert(6);
    t->insert(7);
    t->remove(1);
    EXPECT_TRUE(t->root->key == 5);
    EXPECT_TRUE(t->root->left->key == 3);
    EXPECT_TRUE(t->root->right->key == 6);
    EXPECT_TRUE(t->root->left->left->key == 2);
    EXPECT_TRUE(t->root->left->right->key == 4);
    EXPECT_TRUE(t->root->right->right->key == 7);
}

TEST(AVLTest, Remove_7_req_1R_at_5){
    AvlTree *t = new AvlTree();
    t->insert(5);
    t->insert(3);
    t->insert(6);
    t->insert(2);
    t->insert(4);
    t->insert(7);
    t->insert(1);
    t->remove(7);
    EXPECT_TRUE(t->root->key == 3);
    EXPECT_TRUE(t->root->left->key == 2);
    EXPECT_TRUE(t->root->right->key == 5);
    EXPECT_TRUE(t->root->left->left->key == 1);
    EXPECT_TRUE(t->root->right->left->key == 4);
    EXPECT_TRUE(t->root->right->right->key == 6);
}





