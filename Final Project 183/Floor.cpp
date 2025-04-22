/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Floor.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * Sumin Kim, Nicholas Galeano, Swetha Chimalakonda, Lola Garcia
 * bellakim, ngaleano, swethakc, lolahgar
 *
 * Final Project - Elevators
 */


#include "Floor.h"

using namespace std;

int Floor::tick(int currentTime) {
    int numExploded = 0;
    int exploded[MAX_PEOPLE_PER_FLOOR] = {};
    int explodedIndex = 0;
    for (int i = 0; i < numPeople; i++) {
        if (people[i].tick(currentTime)) {
            exploded[explodedIndex] = i;
            numExploded++;
            explodedIndex++;
        }
    }
    removePeople(exploded, numExploded);
    return numExploded;
}

void Floor::addPerson(Person newPerson, int request) {
    if (numPeople < MAX_PEOPLE_PER_FLOOR) {
        people[numPeople] = newPerson;
        numPeople++;
        if (request > 0) {
            hasUpRequest = true;
        }
        else if (request < 0) {
            hasDownRequest = true;
        }
    }
}

void Floor::removePeople(const int indicesToRemove[MAX_PEOPLE_PER_FLOOR],
                         int numPeopleToRemove) {
    // List of bools to keep track of which indices to remove
    bool toRemove[MAX_PEOPLE_PER_FLOOR] = {false};
    for (int i = 0; i < numPeopleToRemove; ++i) {
        toRemove[indicesToRemove[i]] = true;
    }
    // Temporary list of people updated according to toRemove true values
    Person newPeople[MAX_PEOPLE_PER_FLOOR];
    int newNumPeople = 0;
    for (int i = 0; i < numPeople; ++i) {
        if (!toRemove[i]) {
            newPeople[newNumPeople++] = people[i];
        }
    }
    for (int i = 0; i < newNumPeople; ++i) {
        people[i] = newPeople[i];
    }
    numPeople = newNumPeople;
    resetRequests();
}

void Floor::resetRequests() {
    hasUpRequest = false;
    hasDownRequest = false;
    for (int i = 0; i < numPeople; i++) {
        if (people[i].getCurrentFloor() > people[i].getTargetFloor()) {
            hasDownRequest = true;
        }
        else if (people[i].getCurrentFloor() < people[i].getTargetFloor()) {
            hasUpRequest = true;
        }
    }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Floor::Floor() {
    hasDownRequest = false;
    hasUpRequest = false;
    numPeople = 0;
}

void Floor::prettyPrintFloorLine1(ostream& outs) const {
    string up = "U";
    outs << (hasUpRequest ? up : " ") << " ";
    for (int i = 0; i < numPeople; ++i){
        outs << people[i].getAngerLevel();
        outs << ((people[i].getAngerLevel() < MAX_ANGER) ? "   " : "  ");
    }
    outs << endl;
}

void Floor::prettyPrintFloorLine2(ostream& outs) const {
    string down = "D";
    outs << (hasDownRequest ? down : " ") << " ";
    for (int i = 0; i < numPeople; ++i) {
        outs << "o   ";
    }
    outs << endl;
}

void Floor::printFloorPickupMenu(ostream& outs) const {
    cout << endl;
    outs << "Select People to Load by Index" << endl;
    outs << "All people must be going in same direction!";
    /*  O   O
    // -|- -|-
    //  |   |
    // / \ / \  */
    outs << endl << "              ";
    for (int i = 0; i < numPeople; ++i) {
        outs << " O   ";
    }
    outs << endl << "              ";
    for (int i = 0; i < numPeople; ++i) {
        outs << "-|-  ";
    }
    outs << endl << "              ";
    for (int i = 0; i < numPeople; ++i) {
        outs << " |   ";
    }
    outs << endl << "              ";
    for (int i = 0; i < numPeople; ++i) {
        outs << "/ \\  ";
    }
    outs << endl << "INDEX:        ";
    for (int i = 0; i < numPeople; ++i) {
        outs << " " << i << "   ";
    }
    outs << endl << "ANGER:        ";
    for (int i = 0; i < numPeople; ++i) {
        outs << " " << people[i].getAngerLevel() << "   ";
    }
    outs << endl << "TARGET FLOOR: ";
    for (int i = 0; i < numPeople; ++i) {
        outs << " " << people[i].getTargetFloor() << "   ";
    }
}

void Floor::setHasUpRequest(bool hasRequest) {
    hasUpRequest = hasRequest;
}

bool Floor::getHasUpRequest() const {
    return hasUpRequest;
}

void Floor::setHasDownRequest(bool hasRequest) {
    hasDownRequest = hasRequest;
}

bool Floor::getHasDownRequest() const {
    return hasDownRequest;
}

int Floor::getNumPeople() const {
    return numPeople;
}

Person Floor::getPersonByIndex(int index) const {
    return people[index];
}
