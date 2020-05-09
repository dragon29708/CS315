//
// Created by andrew on 4/24/20.
//

#include <iostream>
#include "person.h"

using std::cout;
using std::endl;

person::person (int newID, family *newParents, family *newMarriage) {
    id = newID;
    parents = newParents;
    marriage = newMarriage;
} // person()

person::~person () {

} // ~person()

void person::print () {
    cout << "person " << id << endl;
} // print()
