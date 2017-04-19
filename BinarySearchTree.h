#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED

#include <fstream>
#include <algorithm>
using namespace std;


class SequenceMap;
template<class Comparable>
struct BinaryNode;


template<class Comparable>
class BinarySearchTree
{
	private:
		BinaryNode<Comparable> *root;
		int size;
	public:

		BinarySearchTree();
		BinaryNode<Comparable>* getRoot();
		BinaryNode<Comparable>* findMin	(BinaryNode<Comparable>*& node);

		int getSize();
		int insert(Comparable x);
		int insert(int count, Comparable x, BinaryNode<Comparable>*& node);
		int remove(Comparable x);
		int remove(int count, Comparable x, BinaryNode<Comparable>*& node);
		int lazyDelete(Comparable x);
		int lazyDelete(int count, Comparable x, BinaryNode<Comparable>*& node);
		Comparable getseq(Comparable x);
		Comparable getseq(Comparable x, BinaryNode<Comparable>*& node);
		int contains(Comparable x);
		int contains(int count, Comparable x, BinaryNode<Comparable>*& node);
		int parse(char* rebFil);
		int treeDepth();
		int treeDepth(int depth, BinaryNode<Comparable>*& node);
		void printTree();
		void printTree(BinaryNode<Comparable>* node);

};


#endif // BINARYSEARCHTREE_H_INCLUDED
