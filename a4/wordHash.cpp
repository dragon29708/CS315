// Author: Andrew Cassidy
// Date: 3/31/20
// Description: hash data strucuture implementation

#include <iostream>
#include "wordHash.h"

wordHash::wordHash() {
    for (int i = 0; i < 10000; i++) {
        LList * newList = new LList;
        table[i] = newList;
    }
} // wordHash()

wordHash::~wordHash() {
    for (int i = 0; i < 10000; i++) {
        delete table[i];
    }
} // ~wordHash()

int wordHash::hashify(string d) {
    int sumOfASCII = 0;
    // sum the ascii values of each char of the string
    for (int i = 0; i < d.size(); i++) {
        sumOfASCII += d[i];
    }
    // index where the hashed string will go
    int index = sumOfASCII % 10000;
    return index;
} // hashify()

void wordHash::insert(string d) {
    // insert the string into the LList at index = hashify(d)
    table[hashify(d)]->insert(d);
} // insert()

void wordHash::print() {
    for (int i = 0; i < 10000; i++) {
        table[i]->print();
    }
} // print()

int wordHash::findCount(string d) {
    // index of the string
    int whereIsD = hashify(d);
    // find the count of d in the table
    node * heresD = table[whereIsD]->search(d);
    return heresD->count;
} // findCount()
