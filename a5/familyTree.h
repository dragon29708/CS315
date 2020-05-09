//
// Created by andrew on 4/26/20.
//

#ifndef A5_FAMILYTREE_H
#define A5_FAMILYTREE_H

#include <vector>
#include "person.h"
#include "family.h"

const int MAX_NUM_PERSONS = 99;
const int MAX_NUM_FAMILIES = 99;

class familyTree {
public:
    // constructor and deconstructor
    familyTree ();
    ~familyTree ();
    // command functions
    void CMDP (int personID, int parentID, int marriageID);                                       // Person command
    void CMDF (int familyID, int husbandID, int wifeID, person * children[], int numChildren);    // Family command
    void CMDV ();                                                                                 // Verify command
    bool CMDR (int firstID, int secondID);                                                        // Relate command
    // storage containers for the families and persons
    // family/person[i] is a pointer to the ith family/person
    // family/person[0] will act as a dummy node
    int numPeople;   // number of person vertices actually in use
    std::vector<int> personsUsed;
    std::vector<int> familiesUsed;
    int numFamilies; // number of family vertices actually in use
    person * persons[MAX_NUM_PERSONS + 1];
    family * families[MAX_NUM_FAMILIES + 1];
    // vector of all adjacent nodes to every node
    // adj[i] (i  < 99) is  family i + 1
    // adj[i] (i >= 99) is  person i % 99 + 1
    std::vector<std::vector<int>> adj;
    // fill adj
    void fillAdj();
};

#endif //A5_FAMILYTREE_H