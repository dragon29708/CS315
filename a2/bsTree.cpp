// Author: Andrew Cassidy
// Date: 1/30/20
// Description: binary search tree object for a program called: trees

#include<iostream>
#include "bsTree.h"

using namespace std;

bsTree::bsTree() {
	numNodes = 0;
	head = NULL;
} // binarySearchTree()

bsTree::~bsTree() {
	if (head)
		delete head;
} // ~binarySearchTree()

void bsTree::insertLeftVal(treeNode * newNode, treeNode * localRoot) {
	// empty tree. insert at top
	if (head == NULL) {
		head = newNode;
	}
	// new leftVal is equal or less to local Root leftVal
	else if (newNode->leftVal <= localRoot->leftVal) {
		// localRoot has no left! insert the newNode!
		if (localRoot->left == NULL) {
			localRoot->left = newNode;
		}
		// lets look at the next left node to see if we can insert
		else {
			insertLeftVal(newNode, localRoot->left);
		}
	}
	// new middleVal is greater than local root middleVal
	else {
		// localRoot has no right! insert the newNode!
		if (localRoot->right == NULL) {
			localRoot->right = newNode;	
		}
		// lets look at the next right node to see if we can insert
		else {
			insertLeftVal(newNode, localRoot->right);
		}
	}
	// 1 more node added to tree!
	numNodes += 1;
} // insertLeftVal()

void bsTree::insertMiddleVal(treeNode * newNode, treeNode * localRoot) {
	// empty tree. insert at top
	if (head == NULL) {
		 head = newNode;
	}
	// new middleVal is equal or less to local Root MiddleVal
	else if (newNode->middleVal <= localRoot->middleVal) {
		// localRoot has no left! insert the newNode!
		if (localRoot->left == NULL) {
			localRoot->left = newNode;
		}
		// lets look at the next left node to see if we can insert
		else {
			insertMiddleVal(newNode, localRoot->left);
		}
	}
	// new middleVal is greater than local root middleVal
	else{
		// localRoot has no right! insert the newNode!
		if (localRoot->right == NULL) {
			localRoot->right = newNode;
		}
		// lets look at the next right node to see if we can insert
		else {
			insertMiddleVal(newNode, localRoot->right);
		}
	}
	// 1 more node added to tree!
	numNodes += 1;
} // insertMiddleVal()
