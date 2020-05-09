// Author: Andrew Cassidy
// Date: 4/5/20
// Description: LList object for a program called: wordCount

#include <iostream>
#include "LList.h"

LList::LList() {
	count = 0;
	head = NULL;
}


LList::~LList() {
	if (head != NULL)
		delete head;  // deletes each node using recursion
}


node * LList::search(string d) {
	node * p = head;			// p points to the head node
    while (p != NULL) {
       		// d was found, return true
	       	if (p->data == d)
				return p;
			else
				p = p->next;
	}
	return NULL; // d was not found
} // search()


void LList::insert(string d) {
	// if the data was already there, who cares!
	node * checkNode = search(d);
	if (checkNode != NULL) {
		// increment count since we technically just added a
		// second instance of the same string
		count += 1;
		checkNode->count += 1;
		return;
	}
	// d will be prepended to the LList
	else {
		// make a new node
		node * newNode = new node;
		newNode->data = d;
		newNode->count = 1;
		// place the node into the beginning of the LList
		newNode->next = head;
		head = newNode;
		// increment count
		count += 1;

	}
} // insert()


void LList::sort() {

} // sort()


void LList::print() {
	if (head == NULL)
		return;
	else {
		node * p = head;
		while (p != NULL) {
			p->print();
			p = p->next;
		}
	}
} // print()
