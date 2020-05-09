// Author: Andrew Cassidy
// Date: 1/20/2020
// Description: LList class to simulate a hand (pile) of cards with cards
// being node objects.

#pragma once
#include "node.h"

class LList {
public:
	LList();
	~LList();
	int getWeight() {return weight;}
	void setWeight(int newWeight) {weight = newWeight;}
	int getLength() {return length;}
	void insertTop(node * p); // insert node p points to at front of pile
	node * removeTop();
	node * removeBot();
	void calcWeight();
private:
	int weight;  // weight of the pile
	int length;  // length of the pile
	node * head; // pointer to the first node in pile
	node * tail; // pointer to the last node in pile
};
