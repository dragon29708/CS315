// Author: Andrew Cassidy
// Date: 1/20/2020
// Description: Node class implementation for a doubly-linked list
// being used to simulate a card in a  hand (pile) of cards.

#include<iostream>
#include"node.h"

node::~node() {
	if (next) {
		delete next;
	}
} // ~node()

node::node() {
	key = 0;             // set card value to zero
	next = prev = NULL;  // set prev and next pointers to NULL
} // node()
