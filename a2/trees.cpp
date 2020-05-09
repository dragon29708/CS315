// Author: Andrew Cassidy
// Date: 1/31/20
// Description: Implements binary search trees while printing the contents
// of the trees using different traveral techniques (CS 315: Assignment 2)

#include <iostream>
#include "bsTree.h"

using namespace std;

// these four functions are written after the main function

// traverses a tree in sym order and prints its contents
void traverseSym(treeNode * localRoot);
// copies nodes from 1 tree to another using preorder traversal
void traversePreInsert(bsTree * tree, treeNode * localRoot);
// traverses a tree in post order and prints its contents
void traversePostPrint(treeNode * localRoot);
// searches a tree's middleVal's, prints last node that = probe or is closest
void searchMiddle(int probe, treeNode * tree);

int main(int argc, char * argv[]) {
	cout << "Trees by Andrew Cassidy\nNode values in the form: (X,Y,Z)\n\n";
	// 1. get numNodes to place in T1
	const int numNodes= stoi(argv[1]);
	// make a new bsTree called T1
	bsTree * T1 = new bsTree;
	cout << "BST T1 made and sorted on X\n\n";
	// populate tree
	int LVal, MVal, RVal;
	for (int i = 0; i < numNodes; i++) {
		// make a new empty treeNode
		treeNode * newNode = new treeNode;
		// 2. get its value from random num gen
		cin >> LVal >> MVal >> RVal;
		// place values into newNode
		newNode->leftVal = LVal;
		newNode->middleVal = MVal;
		newNode->rightVal = RVal;
		// 3. insert the newNode into the bsTree
		T1->insertLeftVal(newNode, T1->head);
	}
	// 4. print out the contents of the tree in sym, pre and post orders
	cout << "Traversing T1 symmetrically:\n";
	traverseSym(T1->head);
	// new bsTree T2
	bsTree * T2 = new bsTree;
	cout << "\nBST T2 made by copy and pasting nodes from T1 in pre order and sorted on Y\n";
	// 5. traverse the contents of T1 in pre order and place them in T2
	traversePreInsert(T2, T1->head);
	// 6. print contents of T2 in post order
	cout << "\nTraversing T2 in post order:\n";
	traversePostPrint(T2->head);
	// 7. get an integer from stdin, treat this as a middleVal. Search for
	// it (or the thing closest to it) in T2
	int probe; cin >> probe;
	cout << "\nLooking for node in T2 with Y value equal or closest to: " << probe << endl;
	// if T2 is empty, dont even search.
	if (T2->head == NULL) {
		cout << "Tree is empty. Nothing to search for.\n";
	}
	// else search in T2
	else {
		searchMiddle(probe, T2->head);
	}
	// end of program
	return 0;
}

void traverseSym(treeNode * localRoot) {
	// return once we have hit a leaf node
 	if (localRoot == NULL) {
		return;
	}
	// keep going down tree!
	else {
		// go left
		traverseSym(localRoot->left);
		// print contents of curr node
		localRoot->print();
		// go right
		traverseSym(localRoot->right);
	}
} // traverseSym()

void traversePreInsert(bsTree * tree, treeNode * localRoot) {
	// return once we have hit a leaf node
	if (localRoot == NULL) {
		return;
	}
	// keep going down tree!
	else {
		// make a copy of localRoot for insertion
		treeNode * newNode = new treeNode;
		newNode->leftVal = localRoot->leftVal;
		newNode->middleVal = localRoot->middleVal;
		newNode->rightVal = localRoot->rightVal;
		// insert node into tree
		tree->insertMiddleVal(newNode, tree->head);
		// go left
		traversePreInsert(tree, localRoot->left);
		// go right
		traversePreInsert(tree, localRoot->right);
	}
} // traversePre()

void traversePostPrint(treeNode * localRoot) {
	// return once we have hit a leaf node
	if (localRoot == NULL) {
		return;
	}
	// keep going down tree!
	else {
		// go left
		traversePostPrint(localRoot->left);
		// go right
		traversePostPrint(localRoot->right);
		// print contents of curr node
		localRoot->print();
	}
} // traversePost()

void searchMiddle(int probe, treeNode * tree) {
	if (tree == NULL) {
		return;
	}
	// probe was found. print the node
	else if (probe == tree->middleVal) {
		tree->print();
	}
	// probe was not found. go left
	else if (probe <= tree->middleVal) {
		// if tree is not a leaf, keep going
		if (tree->left != NULL) {
			searchMiddle(probe, tree->left);
		}
		// if tree is a leaf, close enough!
		else {
			tree->print();
		}
	}
	// probe was not found. go right
	else {
		// if tree is not a leaf, keep going
		if (tree->right != NULL) {
			searchMiddle(probe, tree->right);
		}
		// if tree is a leaf, close enough
		else {
			tree->print();
		}
	}
} // searchMiddle()
