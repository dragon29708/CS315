//
// Created by andrew on 4/22/20.
//

#include "family.h"

using std::cout;
using std::endl;

family::family (int newID, person *newHusband, person *newWife) {
    id = newID;
    husband = newHusband;
    wife = newWife;
    numChildren = 0;
} // family()

family::~family () {
    
} // ~family()

void family::print () {
    cout << "family: " << id << endl;
    cout << "husband: "; husband->print();
    cout << "wife: "; wife->print();
    cout << "children: \n";
    // print the children
    for (int i = 0; i < numChildren; i++) {
        children[i]->print();
    }
} // print()

void family::insertChildren(person * newChildren[], int num) {
     // loop through the children and insert the newChildren
     // i = children[] iterator
     // j = newChildren[] iterator
     if (num > 0) {
         for (int i = numChildren, j = 0; i < MAX_NUM_CHILDREN && j < num; i++, j++) {
             children[i] = newChildren[j];
             numChildren++;
             // throw a error message if we maxed out the size of children[]
             if (numChildren >= MAX_NUM_CHILDREN) {
                 cout << "Max number of children reached in family " << id << endl;
                 break;
             }
         }
     }
} // insertChildren()