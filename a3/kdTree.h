// Author: Andrew Cassidy
// Date: 3/11/20
// Description: kd tree object for a program called: kd

#pragma once

#include <iostream>
#include "kdNode.h"

using namespace std;

class kdTree {
public:
	// constructor and decontructor
	kdTree();
	~kdTree();
    void search(int probes[], kdNode * localRoot); // searches the tree and prints the bucket the probes
                                                     // should be if they were to be inserted
	// data members
	kdNode * head;
};
