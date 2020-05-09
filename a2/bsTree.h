// Author: Andrew Cassidy
// Date: 1/30/20
// Description: binary search tree object for a program called: trees

#pragma once

#include<iostream>
#include "treeNode.h"

using namespace std;

class bsTree {
public:
	// constructor and de-constructor
	bsTree();
	~bsTree();
	// insert node into tree sorting on X
	void insertLeftVal(treeNode * newNode, treeNode * localRoot);
	// insert node into tree sorting on Y
	void insertMiddleVal(treeNode * newNode, treeNode * localRoot);
	// head pointer to top treeNode and num of nodes in the tree
	treeNode * head;
	int numNodes;
};
