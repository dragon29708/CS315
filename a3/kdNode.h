// Author: Andrew Cassidy
// Date: 3/11/20
// Description: kd tree node object for a program called: kd

#pragma once

#include <iostream>
#include <vector>

using namespace std;

class kdNode {
public:
	// constructor and deconstructor
	kdNode();
	~kdNode();
	// member functions
	bool checkBucket(); // will return true and will alter the tree if bucket too big
	void getKthSmallest(int lowIndex, int highIndex, int k); // finds the kth smallest point (median for us)
															 // in the bucket and places it there by partitioning
															 // the bucket based on the median
	void discriminate(); // pick the dim. then find median value by partitioning the bucket
	void breakBucket();  // split the bucket to the left and right
	void print(); // prints the contents of the node

	// data members
	int dim; // dimension the node is discriminating on
	int median; // value in the dim dimension the node is discriminating on
	int medianIndex; // index in the bucket where the median point starts
	bool isLeaf; // true is node is a leaf node in tree, false if not
	vector<int> bucket; // vector of 4d points. each "point" is every 4 values in the vector
						// length of the vector != number of points.
						// num points = size/4 since each point has 4 values.
						// size = 0 if isLeaf = false.
	// left and right nodes
	kdNode * leftNode;
	kdNode * rightNode;
};
