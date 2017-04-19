#ifndef TREENODES_H_INCLUDED
#define TREENODES_H_INCLUDED
#include <iostream>
using namespace std;
//AvlTree Node
template <class Comparable>
struct AvlNode{

    Comparable seq;
    AvlNode *left;
    AvlNode *right;
    int tree_height;
    bool isLazyDelete;
    AvlNode(){
        tree_height=0;
        left=0;
        right=0;
        isLazyDelete=false;

    }





};



#endif // TREENODES_H_INCLUDED
