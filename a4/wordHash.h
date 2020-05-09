// Author: Andrew Cassidy
// Date: 3/31/20
// Description: hash data strucuture definition

#pragma once
#include "LList.h"

const int MAX_SIZE = 10000;

class wordHash {
public:
    // constructor and deconstructor
    wordHash();
    ~wordHash();
    // hash function. given a string, returns an index to put the string into
    int hashify(string d);
    // inserts a string into the hash table
    void insert(string d);
    // prints the hash table
    void print();
    // returns the count in the hash table given a string
    int findCount(string d);
    // the hash table
    LList * table[MAX_SIZE];
};
