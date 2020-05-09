// Author: Andrew Cassidy
// Date: 1/20/2020
// Description: Node class for a doubly-linked list being used
// to simulate a card in a hand (pile) of cards.

#pragma once

using namespace std;

class node {
	friend class LList;
public:
	~node();
	node();
	int getKey() {return key;}
	void setKey(int newKey) {key = newKey;}
private:
	int key;	// value of the card in the pile
	node * next;	// pointer to next node in LList
	node * prev;    // pointer to prev node in LList
};
