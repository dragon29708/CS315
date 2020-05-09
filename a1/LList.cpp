// Author: Andrew Cassidy
// Date: 1/21/20
// Description: LList class implementation to simulate a hand (pile)
// of cards with cards being node objects.

#include<iostream>
#include "LList.h"

using namespace std;

LList::LList() {
	head = tail = NULL;    // head and prev are NULL when first made
	weight = length = 0;   // pile is empty so weight and length are zero
} // LList()

LList::~LList() {
	if (head != NULL)
		delete head;
} // ~LList()

void LList::insertTop(node * p){
	if (head == NULL) {
		head = p; // empty list so new node is only node
		tail = p;
		p->prev = p->next = NULL; // first node in list has no pointers
		length = 1; // length should be 1 but set to 1 just in case
	}
	else {
		p->next = head; // node pointed to by head = next node after p
		p->prev = NULL; // first node in list should have no prev node
		
		// node pointed to by head's prev points to new node
		head->prev = p;
		head = p; // head now points to new node
		length += 1;
	}
	calcWeight();
} // insertTop()

node * LList::removeTop(){
	node * answer = head;    // make pointer to node that will be returned
	// if deck has more than one card
	if (head->next != NULL) {
		head->next->prev = NULL; // new top node's prev points to NULL
		head = head->next;       // make the 2nd node the new top node
		answer->next = answer->prev = NULL; // clear answer's pointers
	}
	// if deck has one card
	else {
		head = tail = NULL; // list is now empty
		answer->next = NULL;     
		answer->prev = NULL;	 // clear out removed node's pointers
	}
	length -= 1;             // length is 1 less now
	calcWeight(); // recalc the weight of the list after node is gone
	return answer;
} // removeTop()

node * LList::removeBot(){
	node * answer = tail;    // make pointer to node that will be returned
	// if deck has more than one card
	if (head->next != NULL) {
		tail->prev->next = NULL; // new tail node's next points to NULL
		tail = tail->prev;       // make the 2nd to last node the new bot node
		answer->next = answer->prev = NULL; // clear answer's pointers
	}
	// if deck has one card
	else {
		head = tail = NULL; // list is now empty
		answer->next = NULL;
		answer->prev = NULL;     // clear out removed node's pointers
	}
	length -= 1;		 // length is 1 less now
	calcWeight(); // recalc the weight of the list after node is gone
	return answer;
} // removeBot()

void LList::calcWeight(){
	if (head == NULL)
		weight = 0;
	else {
		// sum up (weight) * (depth) of each node/card in list/deck
		node * finger = head;
		weight = 0;
		for (int i = 0; i < length && finger!= NULL;  i++) {
			weight = weight + (i + 1) * (finger->key);
			finger = finger->next;
		}
	}
} // calcWeight()
