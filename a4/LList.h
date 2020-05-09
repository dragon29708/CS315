// Author: Andrew Cassidy
// Date: 4/5/20
// Description: LList object for a program called: wordCount

#pragma once
#include "node.h"

class LList {
public:
	// constructor and deconstructor
	LList();
	~LList();
	// functions
	void print();
	void insert(string d);
	void sort();
	node * search(string d);
	// data members
	node * head;
	int count;
};
