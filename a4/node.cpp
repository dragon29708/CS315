// Author: Andrew Cassidy
// Date: 4/5/20
// Description: node object for a program called: wordCount

#include <iostream>
#include "node.h"

node::node() {
	data = "";
	next = NULL;
    count = 0;
} // constructor (default)

node::~node() {
	if (next) delete next;
} // destructor

void node::print() {
	// print the data for the current node
	cout << data << " " << count << endl;
} // print()
