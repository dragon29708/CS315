// Author: Andrew Cassidy
// Date: 3/11/20
// Description: kd tree object implimentation for a program called: kd

#include <iostream>
#include "kdTree.h"

using namespace std;

kdTree::kdTree() {
    // dont point to anything yet. will add on a kdNode after init
    head = NULL;
} // kdTree()

kdTree::~kdTree() {
    // delete the tree if it isnt pointing to null
    if (head) {
        delete head;
    }
} // ~kdTree()

void kdTree::search(int probes[], kdNode * localRoot) {
    // empty tree
    if (head == NULL) {
        cout << "Tree is empty\n";
        return;
    }
    // localRoot is an internal node
    if (localRoot->isLeaf == false) {
        // go to the right if it exists
        int probValue = probes[localRoot->dim];
        if ((localRoot->median < probValue) && (localRoot->rightNode != NULL)) {
            search(probes, localRoot->rightNode);
        }
        // go to the left if it exists
        else if ((localRoot->median >= probValue) && (localRoot->leftNode != NULL)) {
            search(probes, localRoot->leftNode);
        }
        else {
            cout << "ERROR OCCURED IN FINDING BUCKET\n";
        }
    }
    // local root isnt null and must be a leaf
    else {
        localRoot->print();
    }
} // search()
