#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <cstring>
#include "TreeNodes.h"
#include "SequenceMap.h"
#include "BinarySearchTree.cpp"
#include "nodeBinary.h"
#include "AvlTree.cpp"


using namespace std;

template<class Comparable>
void runTests(char* rebFil, char* seqFil, Comparable tree, bool isLazy);


void testTrees(char* rebFil, char* seqFil, char* TreeType)
{
	if(strcmp(TreeType,"BST")==0)                   //If command argument is BST
	{
		cout<<"Stats for Binary Search Tree"<< endl;
		BinarySearchTree<SequenceMap> tree;
		runTests(rebFil, seqFil, tree,0 );
	}

	else if(strcmp(TreeType,"AVL")==0)              //If command argument is AVL
	{
		cout<<"Stats for AVL"<<endl;
		AvlTree<SequenceMap> tree;
		runTests(rebFil, seqFil, tree,0);
	}
	else if(strcmp(TreeType,"LazyAVL")==0)          //If command argument is LazyAVL
	{
		cout<<"Stats for LazyAVL"<<endl;
		AvlTree<SequenceMap> tree;
		runTests(rebFil, seqFil, tree,1);
	}
}


template<class Comparable>
void PrintCalculations(Comparable& tree)
{
	int TotalNodes = tree.getSize(); //Number of node in tree
	double avgDepth = tree.treeDepth()*1.0 / TotalNodes*1.0; //Average depth of tree
	double depth_ratio = avgDepth / (log(TotalNodes) / log(2));  //Ratio of average depth to log2n

	cout<<endl;
	cout<<"Total Nodes in the tree are: "<< TotalNodes<<endl;
	cout<<"The average depth of the tree is: "<< avgDepth<< endl;
	cout<<"depth_ratio: "<< depth_ratio<< endl;
}

//Search tree for each sequence in sequences.txt
template<class Comparable>
void searchSequences(char* seqFil, Comparable& tree)
{
	int TotalCalls=0;
	int TotalQueries=0;
	ifstream queries;
	queries.clear();
	queries.open(seqFil);
	string line;
	string seq;
	while(getline(queries,line))  //Search tree for each sequence in sequences.txt
	{
		seq="";

		if(!line.empty())
		{
			for(int i=0; i<line.length()-1; i++)
			{
				seq+=line[i];
			}
			SequenceMap map(seq, "");
			int CountCalls= tree.contains(map);  //Get total number of calls to the contains function

			if(CountCalls>0)
			{
				TotalQueries++;                     //Get total number of successful queries

				TotalCalls+=CountCalls;
			}

			else
			{
				CountCalls=CountCalls*(-1);
				TotalCalls+=CountCalls;
			}
		}
	}
	queries.close();
	cout<<endl;
	cout<<"Successful queries: "<<TotalQueries<<endl;
	cout<<"Number of calls to contains function: "<<TotalCalls<<endl;

}

//Remove every other sequence in sequences.txt
template<class Comparable>
void removeSequences(char* seqFil, Comparable& tree,bool isLazy)
{
	int TotalCalls=0;
	int TotalRemoves=0;
	ifstream queries;
	queries.clear();
	queries.open(seqFil);
	string line;
	string seq;
	int lineNum=0;
	while(getline(queries,line))
	{
		if((lineNum%2==1)&&(!line.empty()))
		{
			seq="";
			for(int i=0; i<line.length()-1; i++)
			{
				seq+=line[i];
			}
			SequenceMap map(seq, "");
			int CountCalls;
			if(isLazy==0){
			CountCalls=tree.remove(map);}       //Get total number of successful removes
			else{
			CountCalls=tree.lazyDelete(map);}
			if(CountCalls>0)
			{

				TotalRemoves++;
				TotalCalls+=CountCalls;
			}
			else
			{
				CountCalls=CountCalls*(-1);
				TotalCalls+=CountCalls;        //Get total number of calls to the remove function
			}
		}

		lineNum++;
	}
	queries.close();
	cout<<endl;
	cout<<"Successful removes: "<<TotalRemoves<<endl;
	cout<<"Number of calls to delete function: "<<TotalCalls<<endl;
}


template<class Comparable>
void runTests(char* rebFil, char* seqFil, Comparable tree, bool isLazy)
{
	int TotalInserts = tree.parse(rebFil);         //Total number of recursive calls to insert
	cout<<"Number of calls to insert function: "<< TotalInserts<<endl;
	PrintCalculations(tree);
	searchSequences(seqFil, tree);

	cout<<endl;
	cout<<endl;
	cout<<"Removing every other Recognition sequence......"<<endl;
	cout<<endl;
	removeSequences(seqFil, tree, isLazy);
	PrintCalculations(tree);
	searchSequences(seqFil, tree);

}

int main (int argc, char**argv){

    //Takes in the command arguments rebase210.txt sequences.txt Treetype:AVL, BST or LazyAVL
  testTrees(argv[1], argv[2],argv[3]);
  return 0;


}
