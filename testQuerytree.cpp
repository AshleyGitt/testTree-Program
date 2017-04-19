#include <iostream>
#include <string>
#include "TreeNodes.h"
#include "SequenceMap.h"
#include "BinarySearchTree.cpp"
#include <cstring>
#include "nodeBinary.h"
#include "AvlTree.cpp"


using namespace std;

class SequenceMap;

void Trees(char* rebFil, char* TreeType);
template<class Comparable>
void Queries(char* rebFil, Comparable tree);


void Trees(char* rebFil, char* TreeType) //Binary Search Tree
{
	if(strcmp(TreeType,"BST")==0)
	{
		BinarySearchTree<SequenceMap> tree;
		Queries(rebFil, tree);
	}

	else if(strcmp(TreeType,"AVL")==0) //AVL tree
	{
		AvlTree<SequenceMap> tree;
		Queries(rebFil, tree);
	}
	else if(strcmp(TreeType,"LazyAVL")==0)    //LazyAVL tree
	{
		AvlTree<SequenceMap> tree;
		Queries(rebFil, tree);
	}
	else
	     cout<<"Did not enter appropriate tree."<<endl;
}


template<class Comparable>
void Queries(char* rebFil, Comparable tree)
{
	cout<<"Enter sequences in captial letters"<<endl;
	tree.parse(rebFil);
	string cont="Continue";
	while(cont=="Continue")
	{

		string seq="";
		cout<<"Enter a recognition sequence to find corresponding enzymes";
		cin>>seq;

		SequenceMap query(seq,"");
		SequenceMap result=tree.getseq(query);          //Find enzymes
		if(result.getrecogSeq()!="")
		{
			cout<<"	The recognition sequence found."<<endl;
			cout<<"	The corresponding enzymes are:"<<endl;
			result.printEnzymes();              //Print corresponding Enzymes
		}
		else
		{
			cout<<"	The recognition sequence not found."<<endl;
		}
		cout<<endl;
		cout<<"Type 'Continue' to search again or 'EXIT' to exit: ";
		cin>>cont;
		while(cont!="Continue"&&cont!="EXIT")
		{
			cout<<"Please enter 'Continue' to search again or 'EXIT' to quit: ";
			cin>>cont;
		}
		cout<<endl;
	}
}


int main(int argc, char** argv){
    //Runs with the command arguments
    //rebase210.txt AVL, BST or LazyAVL
    Trees(argv[1], argv[2]);
    return 0;
}
