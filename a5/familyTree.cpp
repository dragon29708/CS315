//
// Created by andrew on 4/26/20.
//

#include "familyTree.h"
#include "A5queue.h"

using std::cout;
using std::endl;

// index of the dummy family and person in persons[] and families[]
const int DUMMY_LOC = 0;

familyTree::familyTree () {
    numPeople = numFamilies = 0;
    // call the constructors for all the people and families
    for (int i = 0; i < MAX_NUM_PERSONS + 1; i++) {
        auto p = new person;
        persons[i] = p;
        persons[i]->id = i;
    }
    for (int i = 0; i < MAX_NUM_FAMILIES + 1; i++) {
        auto f = new family;
        families[i] = f;
        families[i]->id = i;
    }
} // familyTree()

familyTree::~familyTree () {

} // ~familyTree()

void familyTree::CMDP (int personID, int parentID, int marriageID) {
    // bad command if personID = 0
    if (personID > DUMMY_LOC) {
        // person[personID]'s has parents in  family[parentID]
        persons[personID]->parents = families[parentID];
        // person[personID]'s has a marriage in  family[marriageID]
        persons[personID]->marriage = families[marriageID];
        numPeople++;
        cout << "Person " << personID;
        cout << " has parents " << parentID;
        cout << " and is married in family " << marriageID << endl;
        personsUsed.push_back(personID);
    }
    else {
        cout << "invalid command\n";
    }
} // CMDP()

void familyTree::CMDF (int familyID, int husbandID, int wifeID, person * children[], int numChildren) {
    // bad command if familyID = 0
    if (familyID > DUMMY_LOC) {
        // families[familyID]'s has husband persons[husbandID]
        families[familyID]->husband = persons[husbandID];
        // families[familyID]'s has wife persons[wifeID]
        families[familyID]->wife = persons[wifeID];
        // insert the children
        families[familyID]->insertChildren(children, numChildren);
        numFamilies++;
        cout << "Family " << familyID;
        cout << " has husband, " << husbandID;
        cout << ", wife " << wifeID;
        if (numChildren > 0) {
            cout << ", and children ";
            // loop through the children
            for (int i = 0; i < families[familyID]->numChildren; i++) {
                cout << families[familyID]->children[i]->id;
                if (i == families[familyID]->numChildren - 1) {
                    cout << "." << endl;
                } else {
                    cout << ", ";
                }
            }
        }
        else {
            cout << " and children." << endl;
        }
        familiesUsed.push_back(familyID);
    }
    else {
        cout << "invalid command\n";
    }
} // CMDF()

void familyTree::CMDV () {
    // loop through all the persons and check for consistency
    bool pepsGood = true;
    for (int j = 0, i = personsUsed[j]; j < personsUsed.size(); j++, i = personsUsed[j]) {
        // check parents
        if (persons[i]->parents->numChildren) {
            bool found = false;
            for (int k = 0; k < persons[i]->parents->numChildren; k++) {
                if (persons[i]->parents->children[k] == persons[i]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Person " << i << " points to parent family " << persons[i]->parents->id;
                cout << " but there is no back pointer\n";
                pepsGood = false;
            }
        }
        else {
            if (persons[i]->parents->id > DUMMY_LOC) {
                cout << "Person " << i << " points to parent family " << persons[i]->parents->id;
                cout << " but there is no back pointer\n";
                pepsGood = false;
            }
        }
        // check marriage
        if ((persons[i]->marriage->husband != persons[i] && persons[i]->marriage->wife != persons[i])
        && persons[i]->marriage->id > DUMMY_LOC) {
            cout << "Person " << i << " points to marriage family " << persons[i]->marriage->id;
            cout << " but there is no back pointer\n";
            pepsGood = false;
        }
    }
    // loop through all the families and check for consistency
    bool famGood = true;
    for (int j = 0, i = familiesUsed[j]; j < familiesUsed.size(); j++, i = familiesUsed[j]) {
        // check the husband
        if (families[i]->husband->marriage != families[i] && families[i]->husband->id > DUMMY_LOC) {
            cout << "Family " << i << " points to husband person " << families[i]->husband->id;
            cout << " but there is no back pointer\n";
            famGood = false;
        }
        // check the wife
        if (families[i]->wife->marriage != families[i] && families[i]->wife->id > DUMMY_LOC) {
            cout << "Family " << i << " points to wife person " << families[i]->wife->id;
            cout << " but there is no back pointer\n";
            famGood = false;
        }
        // check the kids
        if (families[i]->numChildren > 0) {
            for (int k = 0; k < families[i]->numChildren; k++) {
                if (families[i]->children[k]->parents != families[i]) {
                    cout << "Family " << i << " points to child person " << families[i]->children[k]->id;
                    cout << " but there is no back pointer\n";
                    famGood = false;
                }
            }
        }
    }
    // everything checked out
    if (famGood && pepsGood) {
        cout << "The data are consistent\n";
    }
} // CMDV()

// return the family or person index number
// this function to be used for familyTree::CMDR()
int visitedIndexToRegularIndex (int i) {
    // family
    if (i < 99) {
        return i + 1;
    }
    // person
    else {
        return ((i % 99) + 1);
    }
} // visitedIndexToRegularIndex()

// return the visited[] index for a person
// this function to be used for familyTree::CMDR()
int personIndexToVisitedIndex (int i) {
    return (i + 98);
} // personIndexToVisitedIndex()

// return the visited[] index for a family
// this function to be used for familyTree::CMDR()
int familyIndexToVisitedIndex (int i) {
    return (i - 1);
} // familyIndexToVisitedIndex()

void printShortestPath(int pred[], int secondID) {
    std::vector<int> shortestPath;
    int next = personIndexToVisitedIndex(secondID);
    shortestPath.push_back(next);
    // place all predecessors of secondID into shortestPath
    while(pred[next] != -1) {
        shortestPath.push_back(pred[next]);
        next = pred[next];
    }
    // print the shortest path
    for (int i = shortestPath.size() - 1; i >= 0; i--) {
        // check if shortestPath[i] is a family node or not
        int value = visitedIndexToRegularIndex(shortestPath[i]);
        std::string title;
        if (shortestPath[i] >= 99) {
            title = "person";
        }
        else {
            title = "family";
        }
        if (i != 0)
            cout << title << " " << value << " -> ";
        else
            cout << title << " " << value << endl;
    }
} // printShortestPath()

bool familyTree::CMDR (int firstID, int secondID) {
    // list of all nodes and if they're visited or not. families first and persons after
    // visted[i] (i  < 99) is  family i + 1
    // visted[i] (i >= 99) is  person i % 99 + 1
    bool visited[MAX_NUM_FAMILIES + MAX_NUM_PERSONS];
    // list of predecessors to nodes
    // pred[i] = a  -> a precedes i
    int pred[MAX_NUM_FAMILIES + MAX_NUM_PERSONS];
    // fill with false bools for visited[] and -1 for pred[]
    for (int i = 0; i < MAX_NUM_FAMILIES + MAX_NUM_PERSONS; i++) {
        visited[i] = false;
        pred[i] = -1;
    }
    // fill the adj vector of all currently used nodes
    fillAdj();
    // queue of nodes
    A5queue<int> Q;
    visited[personIndexToVisitedIndex(firstID)] = true;
    Q.push(personIndexToVisitedIndex(firstID));
    // perform BFS on the tree
    while(!Q.empty()) {
        int current = Q.front();
        Q.pop();
        // loop through all nodes that current points to
        for (int i = 0; i < adj[current].size(); i++) {
            // adj[current][i] = -1 means that nodes pointed to one of the dummy nodes
            if (!visited[adj[current][i]] && adj[current][i] != -1) {
                visited[adj[current][i]] = true;
                pred[adj[current][i]] = current;
                Q.push(adj[current][i]);
                // we got to the end
                if (adj[current][i] == personIndexToVisitedIndex(secondID)) {
                    printShortestPath(pred, secondID);
                    return true;
                }
            }
        }
    }
    return false;
} // CMDR()

void familyTree::fillAdj() {
    // loop through all families and place all their adjacent node's id's in a vector
    // then place that vector into the adj[] vector
    for (int i = 1; i < MAX_NUM_FAMILIES + 1; i++) {
        std::vector<int> famAdj;
        // put the husband in
        if (families[i]->husband != NULL)
            famAdj.push_back(personIndexToVisitedIndex(families[i]->husband->id));
        else
            famAdj.push_back(-1);
        // put the wife in
        if (families[i]->wife != NULL)
            famAdj.push_back(personIndexToVisitedIndex(families[i]->wife->id));
        else
            famAdj.push_back(-1);
        // put the children PERSONS in
        for (int j = 0; j < families[i]->numChildren; j++) {
            famAdj.push_back(personIndexToVisitedIndex(families[i]->children[j]->id));
        }
        adj.push_back(famAdj);
    }
    for (int i = 1; i < MAX_NUM_PERSONS + 1; i++) {
        std::vector<int> persAdj;
        // put the parents in
        if (persons[i]->parents != NULL)
            persAdj.push_back(familyIndexToVisitedIndex(persons[i]->parents->id));
        else
            persAdj.push_back(-1);
        // put the marriage in
        if (persons[i]->marriage != NULL)
            persAdj.push_back(familyIndexToVisitedIndex(persons[i]->marriage->id));
        else
            persAdj.push_back(-1);
        adj.push_back(persAdj);
    }
}