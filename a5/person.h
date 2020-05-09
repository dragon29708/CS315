//
// Created by andrew on 4/24/20.
//

#ifndef A5_PERSON_H
#define A5_PERSON_H

#include <iostream>

// IRL can have > 2 but we go with 2 for this assignment
const int MAX_NUM_PARENTS = 2;

// removes cyclical problems. tells person that family is defined later.
class family;

class person {
public:
    // constructor and deconstructor
    person (int newID = 0, family * newParents = NULL, family * newMarriage = NULL);
    ~person ();
    // functions
    void print (); // prints data members of a person
    // data members
    int id;
    family * parents;
    family * marriage;
};

#endif //A5_PERSON_H