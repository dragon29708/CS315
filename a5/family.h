//
// Created by andrew on 4/22/20.
//

#ifndef A5_FAMILY_H
#define A5_FAMILY_H

#include <iostream>
#include "person.h"

const int MAX_NUM_CHILDREN = 10;

class family {
public:
    // constructor and deconstructor
    family (int newID = 0, person * newHusband = NULL, person * newWife = NULL);
    ~family ();
    // member functions
    void print (); // prints the data members of a family
    void insertChildren (person * newChildren[], int num);
    // data members
    int id;
    person * husband;
    person * wife;
    int numChildren;
    person * children[MAX_NUM_CHILDREN];
};

#endif //A5_FAMILY_H