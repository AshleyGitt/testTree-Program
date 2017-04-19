#include <iostream>
#include <fstream>
#include "AvlTree.h"
using namespace std;

static const int ALLOWED_IMBALANCE = 1;


static int insertCount=0;		//count number of recursive calls for insert and delete
static int deleteCount=0;

template<class Comparable>
AvlTree<Comparable>::AvlTree()
{
	root=NULL;
	size=0;
}

/*Returns the root of the tree*/
template<class Comparable>
AvlNode<Comparable>* AvlTree<Comparable>::getRoot()
{
	return root;
}


/*Internal method to find the smallest item in a subtree t.
Return node containing the smallest item.*/
template<class Comparable>
AvlNode<Comparable>* AvlTree<Comparable>::findMin(AvlNode<Comparable>*& node)
{
	if( node == NULL )
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


/*Returns the number of nodes of the tree*/
template<class Comparable>
int AvlTree<Comparable>::getSize()
{
	return size;
}


/* Return the height of node or -1 if nullptr.*/
template<class Comparable>
int AvlTree<Comparable>::tree_height(AvlNode<Comparable>* node ) const
{

	return node == 0 ? -1 : node->tree_height;
}


/* Assume node is balanced or within one of being balanced*/
template<class Comparable>
void  AvlTree<Comparable>::balance(AvlNode<Comparable>*& node)
{
	if(node==0)
	{
		return;
	}
	if(( tree_height(node->left)-tree_height(node->right) )>ALLOWED_IMBALANCE)
	{
		if(tree_height(node->left->left)>=tree_height(node->left->right))
		{
			rotateWithLeftChild(node);
		}
		else
		{
			doubleWithLeftChild(node);
		}
	}
	else if(tree_height(node->right)-tree_height(node->left)>ALLOWED_IMBALANCE )
	{
		if(tree_height(node->right->right)>=tree_height( node->right->left ))
		{
			rotateWithRightChild(node);
		}
		else
		{
			doubleWithRightChild(node);
		}
	}
	int n=max(tree_height(node->left), tree_height(node->right)) + 1;
	node->tree_height=n;
}

/* Rotate binary tree node with left child.
For AVL trees, this is a single rotation for case 1.
Update tree heights, then set new root.*/
template<class Comparable>
void AvlTree<Comparable>::rotateWithLeftChild(AvlNode<Comparable>*& k2)
{
	AvlNode<Comparable>* k1=k2->left;
	k2->left=k1->right;
	k1->right=k2;
	k2->tree_height=max(tree_height(k2->left), tree_height(k2->right)) + 1;
	k1->tree_height=max(tree_height(k1->left), k2->tree_height) + 1;
	k2=k1;
}

 /* Double rotate binary tree node: first left child.
 with its right child; then node k3 with new left child.
For AVL trees, this is a double rotation for case 2.
Update heights, then set new root.*/
template<class Comparable>
void AvlTree<Comparable>::doubleWithLeftChild(AvlNode<Comparable>*& k3)
{
	rotateWithRightChild(k3->left);
	rotateWithLeftChild(k3);
}
/*Rotate binary tree node with right child.
For AVL trees, this is a single rotation for case 4.
Update heights, then set new root.*/
template<class Comparable>
void AvlTree<Comparable>::rotateWithRightChild(AvlNode<Comparable>*& k2)
{
	AvlNode<Comparable>* k1=k2->right;
	k2->right=k1->left;
	k1->left=k2;
	k2->tree_height=max(tree_height(k2->right), tree_height(k2->left)) + 1;
	k1->tree_height=max(tree_height(k1->right), k2->tree_height) + 1;
	k2=k1;
}

/*Double rotate binary tree node: first right child.
with its left child; then node k3 with new right child.
For AVL trees, this is a double rotation for case 3.
Update heights, then set new root.*/
template<class Comparable>
void AvlTree<Comparable>::doubleWithRightChild(AvlNode<Comparable>*& k3)
{
	rotateWithLeftChild(k3->right);
	rotateWithRightChild(k3);
}


/*Returns the number of recursive calls when inserting an seq */
template<class Comparable>
int AvlTree<Comparable>::insert(Comparable x)
{
	insert(x, root);
	return insertCount;
}

 /* Internal method to insert into a subtree.
x is the item to insert.
node is the node that roots the subtree.
Set the new root of the subtree.*/
template<class Comparable>
void AvlTree<Comparable>::insert(Comparable x, AvlNode<Comparable>*& node)
{
	insertCount++;
	if(node == 0)
	{
		node = new AvlNode<Comparable>;
		node->seq=x;
		size++;
	}
	else if(x < node->seq)
	{

		insert(x, node->left);
	}
	else if(x > node->seq)
	{
		insert(x, node->right);
	}
	else							// duplicate found
	{
		node->seq.merge(x);
	}
	balance(node);
}


/*Returns the number of recursive calls when removing a given seq
Returns a negative number if the seq does not exist in the tree*/
template<class Comparable>
int AvlTree<Comparable>::remove(Comparable x)
{
	deleteCount=0;
	remove(x, root);
	return deleteCount;
}

/*Internal method to remove from a subtree.
x is the item to remove.
node is the node that roots the subtree.
Set the new root of the subtree.*/
template<class Comparable>
void AvlTree<Comparable>::remove(Comparable x, AvlNode<Comparable>*& node)
{
	deleteCount++;
	if(node==0)
	{
		deleteCount= (deleteCount)*(-1);						// negate count if seq does not exist in tree
		return;
	}
	if(x<node->seq)
	{
		remove(x,node->left);
	}
	else if(x>node->seq)
	{
		remove(x,node->right);
	}
	else if(node->left!=0&&node->right!=0)			// if node has two children
	{
		node->seq = findMin( node->right )->seq;
		remove( node->seq, node->right );
	}
	else													// if node has one child
	{
		AvlNode<Comparable>* oldAvlNode = node;
		node= (node->left!=0)? node->left : node->right;
		delete oldAvlNode;
		size--;
	}
	balance(node);
}

/*LAZY DELETE

Returns the number of recursive calls when removing an seq*/

template<class Comparable>
int AvlTree<Comparable>::lazyDelete(Comparable x)
{
	return lazyDelete(0, x, root);
}


template<class Comparable>
int AvlTree<Comparable>::lazyDelete(int count, Comparable x, AvlNode<Comparable>*& node)
{
	if(node==0)
	{
		return (count+1)*(-1);									// return negative count if seq is not found
	}
	else if(x<node->seq)
	{
		return lazyDelete(count+1, x, node->left);
	}
	else if(x>node->seq)
	{
		return lazyDelete(count+1, x, node->right);
	}
	else if(node->isLazyDelete==true)				// if we find the node, but we already "deleted" it
	{
		return (count+1)*(-1);
	}
	else
	{
		node->isLazyDelete=true;				// if we find the node, lazily mark as deleted
		return count+1;
	}
}


/*Returns a given seq if it exists in the tree
Returns a dummy seq if it does not exist in the tree*/
template<class Comparable>
Comparable AvlTree<Comparable>::getseq(Comparable x)
{
	return getseq(x, root);
}


template<class Comparable>
Comparable AvlTree<Comparable>::getseq(Comparable x, AvlNode<Comparable>*& node)
{
	if(node==0)									// seq not found in tree
	{
		SequenceMap fail("","");				// return dummy seq if seq does not exist in the tree
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
	else													// seq found
	{
		return node->seq;
	}
}


template<class Comparable>
int AvlTree<Comparable>::contains(Comparable x)
{
	return contains(0, x, root);
}


/*Returns the number of recursive calls when checking if an seq exists in the tree
Returns a negative number if the seq does not exist in the tree*/
template<class Comparable>
int AvlTree<Comparable>::contains(int count, Comparable x, AvlNode<Comparable>*& node)
{
	if(node==0)											// seq not found in tree
	{
		return (count+1)*(-1);									// return negative count if seq does not exist
	}
	else if(x<node->seq)
	{
		return contains(count+1, x, node->left);
	}
	else if(x>node->seq)
	{
		return contains(count+1, x, node->right);
	}
	else													// seq found
	{
		return count+1;
	}

}


/*Returns the number of recursive calls when inserting seqs read from an input file*/
template<class Comparable>
int AvlTree<Comparable>::parse(char* rebFil)
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
				string seq="";
				for(i++; line[i]!='/'; i++)
				{
					seq+=line[i];
				}
				SequenceMap map(seq,enzyme);
				insert(map);

			}

		}
	}
	database.close();
	return insertCount;
}


/*Returns the total depth of the tree (the sum of the depths of all the nodes in the tree)*/
template<class Comparable>
int AvlTree<Comparable>::treeDepth()
{
	return treeDepth(0, root);
}

template<class Comparable>
int AvlTree<Comparable>::treeDepth(int depth, AvlNode<Comparable>*& node)
{
	if(node==0)
	{
		return 0;
	}
	return depth + treeDepth(depth+1, node->left) + treeDepth(depth+1, node->right);
}


/*Print the tree contents in sorted order.*/
template<class Comparable>
void AvlTree<Comparable>::printTree()
{	if( root==NULL )
            cout << "Empty tree" << endl;
	else
		printTree(root);
}

 /*Internal method to print a subtree rooted at t in sorted order.*/
template<class Comparable>
void AvlTree<Comparable>::printTree(AvlNode<Comparable>* node)
{
	if(node!=0)
	{
		printTree(node->left);
		node->seq.printKey();
		printTree(node->right);
	}
}

