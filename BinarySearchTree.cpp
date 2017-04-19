#include <fstream>
#include <iostream>
#include "BinarySearchTree.h"
template<class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree()
{
	root=0;
	size=0;
}

/*Returns the root of the tree*/
template<class Comparable>
BinaryNode<Comparable>* BinarySearchTree<Comparable>::getRoot()
{
	return root;
}

/*Internal method to find the smallest item in a subtree t.
Return node containing the smallest item.*/
template<class Comparable>
BinaryNode<Comparable>* BinarySearchTree<Comparable>::findMin(BinaryNode<Comparable>*& node)
{	 if( node == NULL )
            return NULL;
	if(node->left==NULL)
	{
		return node;
	}
	else
	{
		return findMin(node->left);
	}
}


/*returns the number of nodes of the tree*/
template<class Comparable>
int BinarySearchTree<Comparable>::getSize()
{
	return size;
}

 /*Insert x into the tree. Returns the number of recursive
 calls when inserting an seq*/
template<class Comparable>
int BinarySearchTree<Comparable>::insert(Comparable x)
{
	int count= insert(0, x, root);
	return count;
}
/*Internal method to insert into a subtree.
x is the item to insert.
node is the node that roots the subtree.
Set the new root of the subtree.*/
template<class Comparable>
int BinarySearchTree<Comparable>::insert(int count, Comparable x, BinaryNode<Comparable>*& node)
{
	if(node==0)						// if no duplicate sequence is found
	{
		node=new BinaryNode<Comparable>;
		node->seq=x;
		node->left=0;
		node->right=0;
		size++;
		return count+1;
	}
	else if(x<node->seq)
	{
		return insert(count+1, x, node->left);
	}
	else if(x>node->seq)
	{
		return insert(count+1, x, node->right);
	}
	else				// if duplicate sequence is found
	{
		node->seq.merge(x);
		return count+1;
	}
}


/*Returns the number of recursive calls when removing a given seq,
Returns a negative number if the seq does not exist in the tree*/
template<class Comparable>
int BinarySearchTree<Comparable>::remove(Comparable x)
{
	int count= remove(0, x, root);
	return count;
}

/* Internal method to remove from a subtree.
x is the item to remove.
node is the node that roots the subtree.
Set the new root of the subtree.
*/
template<class Comparable>
int BinarySearchTree<Comparable>::remove(int count, Comparable x, BinaryNode<Comparable>*& node)
{
	if(node==0)
	{
		return (count+1)*(-1);		// return negative count if seq is not found
	}
	else if(x<node->seq)
	{
		return remove(count+1, x, node->left);
	}
	else if(x>node->seq)
	{
		return remove(count+1, x, node->right);
	}
	else if((node->left!=0)&&(node->right!=0))		// if node has two children
	{
		node->seq=findMin(node->right)->seq;
		return remove(count+1, node->seq, node->right);
	}
	else							// if node has one child
	{
		BinaryNode<Comparable> *oldBinaryNode=node;
		node= (node->left!=0)? node->left : node->right;
		delete oldBinaryNode;
		size--;
		return count+1;
	}
}


/*LAZY DELETE

Returns the number of recursive calls when removing an seq
Returns a negative number if the seq does not exist in the tree*/
template<class Comparable>
int BinarySearchTree<Comparable>::lazyDelete(Comparable x)
{
	return lazyDelete(0, x, root);
}

template<class Comparable>
int BinarySearchTree<Comparable>::lazyDelete(int count, Comparable x, BinaryNode<Comparable>*& node)
{
	if(node==0)
	{
		return (count+1)*(-1);					// return negative count if seq is not found
	}
	else if(x<node->seq)
	{
		return lazyDelete(count+1, x, node->left);
	}
	else if(x>node->seq)
	{
		return lazyDelete(count+1, x, node->right);
	}
	else if(node->isLazyDelete==true)	// if we find the node, but we already "deleted" it
	{
		return (count+1)*(-1);
	}
	else									// if we find the node, lazily mark as deleted
	{
		node->isLazyDelete=true;
		return count+1;
	}
}


/*Returns a given seq if it exists in the tree*/
template<class Comparable>
Comparable BinarySearchTree<Comparable>::getseq(Comparable x)
{
	return getseq(x, root);
}

template<class Comparable>
Comparable BinarySearchTree<Comparable>::getseq(Comparable x, BinaryNode<Comparable>*& node)
{
	if(node==0)											// sequence not found in tree
	{
		SequenceMap fail("","");
		return fail;
	}
	else if(x<node->seq)
	{
		return getseq(x, node->left);
	}
	else if(x>node->seq)
	{
		return getseq(x, node->right);
	}
	else													// sequence found
	{
		return node->seq;
	}
}


/*Returns the number of recursive calls when checking if an seq exists in the tree*/
template<class Comparable>
int BinarySearchTree<Comparable>::contains(Comparable  x)
{
	return contains(0, x, root);
}

template<class Comparable>
int BinarySearchTree<Comparable>::contains(int count, Comparable x, BinaryNode<Comparable>*& node)
{
	if(node==0)						// sequence not found in tree
	{
		return (count+1)*(-1);
	}
	else if(x<node->seq)
	{
		return contains(count+1, x, node->left);
	}
	else if(x>node->seq)
	{
		return contains(count+1, x, node->right);
	}
	else						// sequence found in tree
	{
		return count+1;
	}
}


/*Returns the number of recursive calls when inserting sequences read from the input file*/
template<class Comparable>
int BinarySearchTree<Comparable>::parse(char* rebFil)
{
	int count=0;
	ifstream database;
	database.clear();
	database.open(rebFil);
	string line;
	while(getline(database,line))
	{
		if(line[line.length()-2]=='/')
		{
			int i=0;
			string enzyme="";
			for(i; line[i]!='/'; i++)
			{
				enzyme+=line[i];
			}
			while(line[i+1]!='/')
			{
				string sequence="";
				for(i++; line[i]!='/'; i++)
				{
					sequence+=line[i];
				}
				SequenceMap map(sequence,enzyme);
			   	count+=insert(map);
			}
		}
	}
	database.close();
	return count;
}


/*Returns the total depth of the tree (the sum of the depths of all the nodes in the tree)*/
template<class Comparable>
int BinarySearchTree<Comparable>::treeDepth()
{
	return treeDepth(0, root);
}

template<class Comparable>
int BinarySearchTree<Comparable>::treeDepth(int depth, BinaryNode<Comparable>*& node)
{
	if(node==0)
	{
		return 0;
	}
	return depth + treeDepth(depth+1, node->left) + treeDepth(depth+1, node->right);
}


/*Prints sequences of the tree in order*/
template<class Comparable>
void BinarySearchTree<Comparable>::printTree()
{	if( root==NULL )
            cout << "Empty tree" << endl;
        else
	printTree(root);
}

template<class Comparable>
void BinarySearchTree<Comparable>::printTree(BinaryNode<Comparable>* node)
{
	if(node!=0)
	{
		printTree(node->left);
		node->seq.printKey();
		printTree(node->right);
	}
}

