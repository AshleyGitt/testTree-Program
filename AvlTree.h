#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

#include <fstream>

using namespace std;


class SequenceMap;
template<class Comparable>
struct AvlNode;


template<class Comparable>
class AvlTree
{
	private:
		AvlNode<Comparable> *root;
		int size;
	public:
		AvlTree();
		AvlNode<Comparable>* getRoot();
		AvlNode<Comparable>* findMin(AvlNode<Comparable>*& node);
		int  getSize();
		int tree_height(AvlNode<Comparable>* node) const;
		void balance(AvlNode<Comparable>*& node);
		void rotateWithLeftChild(AvlNode<Comparable>*& k2);
		void doubleWithLeftChild(AvlNode<Comparable>*& k3);
		void rotateWithRightChild(AvlNode<Comparable>*& k2);
		void doubleWithRightChild(AvlNode<Comparable>*& k3);
		int  insert(Comparable x);
		void insert(Comparable x, AvlNode<Comparable>*& node);
		int remove(Comparable x);
		void remove(Comparable x, AvlNode<Comparable>*& node);
		int  lazyDelete(Comparable x);
		int lazyDelete(int count, Comparable x, AvlNode<Comparable>*& node);
		Comparable getseq(Comparable x);
		Comparable getseq(Comparable x, AvlNode<Comparable>*& node);
		int  contains(Comparable x);
		int  contains(int count, Comparable x, AvlNode<Comparable>*& node);
		int  parse(char* rebFil);
		int treeDepth();
		int treeDepth(int depth, AvlNode<Comparable>*& node);
		void printTree();
		void printTree(AvlNode<Comparable>* node);


};


#endif // AVLTREE_H_INCLUDED
