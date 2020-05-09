// Author: Andrew Cassidy
// Date: 3/11/20
// Description: Implements a kd tree (k=4) for Spring 2020 CS 315 Assignment 3

#include <iostream>
#include <vector>
#include "kdNode.h"
#include "kdTree.h"

using namespace std;

int main(int argc, char * argv[]) {
    // title
    cout << "\nCS315 Assignment 3: kd\nBy: Andrew Cassidy\n\n";
    // get values from standard input
    int numPoints, numProbes;
    numPoints = stoi(argv[1]);
    numProbes = stoi(argv[2]);
    cout << "numPoints: " << numPoints << "\nnumProbes: " << numProbes << endl;
	// kd tree to be used for the assignment
	kdTree * tree = new kdTree;
    kdNode * node = new kdNode;
    // populate the vector in the node at the top of the tree
    for (int i = 0; i < numPoints; i++) {
        int d0, d1, d2, d3;
        // get all 4 values for the 4d point
        cin >> d0 >> d1 >> d2 >> d3;
        // put the 4d point into the array
        node->bucket.push_back(d0);
        node->bucket.push_back(d1);
        node->bucket.push_back(d2);
        node->bucket.push_back(d3);
    }
    // node is full and ready to become the top node in the tree. so we make head point to our full node
    tree->head = node;
    // checkBucket() returns true if the main bucket was too big
    // checkBucket() will recursily and offline build the kd tree
    if (tree->head->checkBucket()) {
        cout << "\nBuilding K-D tree...\n\n";
    }
    else {
        cout << "\nK-D tree built with no effort. Size of first bucket is empty or < b.\n\n";
    }
    // now that the tree is built. we search through it with the p probes
    // stored in our probes vector.
    // for p 4d probes, there will be p * 4 values in the probes vector
    if (numProbes > 0) {
        int probes[numProbes][4];
        // read in p * 4 numbers into the probes array
        for (int i = 0;  i < numProbes; i++) {
            for (int j = 0; j < 4; j++) {
                int newVal;
                cin >> newVal;
                probes[i][j] = newVal;
            }
        }
        // search the tree for all nodes
        for (int i = 0; i < numProbes; i++) {
            cout << "probe " << probes[i][0] << " " << probes[i][1] << " " << probes[i][2] << " " << probes[i][3];
            cout << " reaches bucket:" << endl;
            tree->search(probes[i], tree->head);
        }
    }
    else {
        cout << "No probes inputted\n";
    }
	return 0;
}
