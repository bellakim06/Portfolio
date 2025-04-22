/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * Sumin Kim, Nicholas Galeano, Swetha Chimalakonda, Lola Garcia
 * bellakim, ngaleano, swethakc, lolahgar
 *
 * Final Project - Elevators
 */
 
#include <cmath>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "Move.h"

using namespace std;

Move::Move(string commandString) : Move() {
    if (commandString == "") {
        isPass = true;
    }
    else if (commandString == "Q" || commandString == "q") {
        isQuit = true;
    }
    else if (commandString == "S" || commandString == "s") {
        isSave = true;
    }
    else if (commandString.at(2) == 'p' || commandString.at(2) == 'P') {
        isPickup = true;
        elevatorId = commandString.at(1) - '0';
    }
    else if (commandString.at(2) == 'f' || commandString.at(2) == 'F') {
        elevatorId = commandString.at(1) - '0';
        targetFloor = commandString.at(3) - '0';
    }
}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    if (isPassMove() || isQuitMove() || isSaveMove()) {
        return true;
    }
    if (elevators[elevatorId].isServicing()) {
        return false;
    }
    if (elevatorId < 0 || elevatorId >= NUM_ELEVATORS) {
        return false;
    }
    if (!isPickupMove()) {
        if (targetFloor < 0 || targetFloor >= NUM_FLOORS ||
            targetFloor == elevators[elevatorId].getCurrentFloor()) {
            return false;
        }
    }
    return true;
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor,
                             const Floor& pickupFloor) {
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    targetFloor = currentFloor;
    for (int i = 0; i < pickupList.length(); i++) {
        int index = pickupList.at(i) - '0';
        peopleToPickup[i] = index;
        numPeopleToPickup++;
        int angerLevel = pickupFloor.getPersonByIndex(index).getAngerLevel();
        totalSatisfaction += (MAX_ANGER - angerLevel);
        int floor = pickupFloor.getPersonByIndex(index).getTargetFloor();
        if (abs(floor - currentFloor) > abs(targetFloor - currentFloor)) {
            targetFloor = floor;
        }
    }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
    return isPass;
}

bool Move::isSaveMove() const {
    return isSave;
}

bool Move::isQuitMove() const {
    return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}
