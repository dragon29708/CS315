// Author: Andrew Cassidy
// Date: 4/5/20
// Description: node object for a program called: wordCount

#pragma once

#include <string>

using namespace std;

class node {
public:
	~node();
	node();
	node(string d);
	void print();
	string data;	// data of the node
	node * next;	// pointer to next node in list
    int count;
};
