#ifndef NODEBINARY_H_INCLUDED
#define NODEBINARY_H_INCLUDED

#include <iostream>
using namespace std;
//BinarySearchTreeNode
template <class Comparable>
struct BinaryNode{

    Comparable seq;
    BinaryNode *left;
    BinaryNode *right;
    int tree_height;
    bool isLazyDelete;
    BinaryNode(){
        tree_height=0;
        left=0;
        right=0;
        isLazyDelete=false;

    }





};


#endif // NODEBINARY_H_INCLUDED
