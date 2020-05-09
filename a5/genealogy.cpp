// Author: Andrew Cassidy
// Date: 4/22/20
// Description: genealogy program for Spring 2020 CS315 Assignment 5

#include <iostream>
#include <sstream> // for tokenizing the commands. will do same thing as strtok()
#include <string>
// user defined classes
#include "familyTree.h"

using namespace std;

// program command functions
void MakePerson (familyTree * T, stringstream& command, string& token, const char delim);
void MakeFamily (familyTree * T, stringstream& command, string& token, const char delim);
void Verify (familyTree * T);
void Relate (familyTree * T, stringstream& command, string& token, const char delim);

int main() {
    // create the familyTree
    auto T = new familyTree;
    // take the line and place into a string
    string line; getline(cin, line, '\n');
    // tokenize the command
    stringstream command(line);
    string token;
    const char delim = ' ';
    // loop through the input file
    while(getline(command, token, delim) && !cin.fail()) {
        // person command
        if (toupper(token[0]) == 'P') {
            MakePerson(T, command, token, delim);
        }
        // family command
        else if (toupper(token[0]) == 'F') {
            MakeFamily(T, command, token, delim);
        }
        // verify command
        else if (toupper(token[0]) == 'V') {
            Verify(T);
        }
        // relate command
        else if (toupper(token[0]) == 'R'){
            Relate(T, command, token, delim);
        }
        // unknown command
        else {
            cout << "invalid command\n";
        }
        // done with current command
        // get the next line
        getline(cin, line, '\n');
        // clear out stringstream object for reuse
        command.clear();
        command.seekg(0, ios::beg);
        command.str(line);
    }
    // free T's memory back to heap
    delete T;
    return 0;
}

void MakePerson (familyTree * T, stringstream& command, string& token, const char delim) {
    // fill personID, parentID, marriageID using command token function
    int personID, parentID, marriageID;
    getline(command, token, delim); // token = personId
    personID = stoi(token);
    getline(command, token, delim); // token = DONT CARE
    getline(command, token, delim); // token = parentID
    parentID = stoi(token);
    getline(command, token, delim); // token = DONT CARE
    getline(command, token, delim); // token = marriageID
    marriageID = stoi(token);
    // insert the person into the familyTree
    T->CMDP(personID, parentID, marriageID);
} // MakePerson ()

void MakeFamily (familyTree * T, stringstream& command, string& token, const char delim) {
    int familyID, husbandID, wifeID;
    person * children[MAX_NUM_CHILDREN];
    getline(command, token, delim); // token = familyID
    familyID = stoi(token);
    getline(command, token, delim); // token = DONT CARE
    getline(command, token, delim); // token = husbandID
    husbandID = stoi(token);
    getline(command, token, delim); // token = DONT CARE
    getline(command, token, delim); // token = wifeID
    wifeID = stoi(token);
    getline(command, token, delim); // token = DONT CARE
    // get and store the children numbers
    int numChildren = 0;
    while (getline(command, token, delim)) {
        int child = stoi(token);
        children[numChildren] = T->persons[child];
        numChildren++;
        getline(command, token, delim); // token = DONT CARE
    }
    // into the family into the familyTree
    T->CMDF(familyID, husbandID, wifeID, children, numChildren);
} // MakeFamily ()

void Verify (familyTree * T) {
    T->CMDV();
} // Verify ()

void Relate (familyTree * T, stringstream& command, string& token, const char delim) {
    int firstID, secondID;
    getline(command, token, delim); // token = firstID
    firstID = stoi(token);
    getline(command, token, delim); // token = secondID
    secondID = stoi(token);
    // have T relate firstID and secondID
    if(!T->CMDR(firstID, secondID)) {
        cout << "Persons " << firstID << " and " << secondID << " are not related\n";
    }
} // Relate ()