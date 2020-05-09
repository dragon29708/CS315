// Author: Andrew Cassidy
// Date: 1/30/20
// Description: Node object to be used for a tree object

#pragma once

#include<iostream>

using namespace std;

class treeNode {
public:
	// constructor and deconstructor
	treeNode() {
		leftVal = middleVal = rightVal = 0;
		left = right = NULL;
	}
	~treeNode() {
		if (left) {
			delete left;
		}
		if (right) {
			delete right;
		}
	}
	// print the contents of the node
	void print() {
		cout << "(" << leftVal << ", " << middleVal << ", " << rightVal << ")\n";
	}
	// each nodes has 3 values, and pointers to nodes on left and right
	int leftVal, middleVal, rightVal;
	treeNode * left;
	treeNode * right;
};
