/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Elevator.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * Sumin Kim, Nicholas Galeano, Swetha Chimalakonda, Lola Garcia
 * bellakim, ngaleano, swethakc, lolahgar
 *
 * Final Project - Elevators
 */

#include "Elevator.h"
#include <iostream>

using namespace std;

// moves elevator towards target floor
void Elevator::tick(int currentTime) {
    // checks if it is time to move elevator
    if ((currentTime % TICKS_PER_ELEVATOR_MOVE == 0) && servicing) {
        // elevator is moving in downward direction
        if (currentFloor > targetFloor) {
            // decrease currentFloor by 1
            currentFloor--;
        }
        // elevator is moving in upward direction
        else if (currentFloor < targetFloor) {
            // increase currentFloor by 1
            currentFloor++;
        }
    }
    // elevator has reached targetFloor
    if (currentFloor == targetFloor) {
        // elevator is no longer servicing
        servicing = false;
    }
}

void Elevator::serviceRequest(int floorNum) {
    // sets desired targetFloor
    targetFloor = floorNum;
    // sets elevator to servicing
    servicing = true;
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

void Elevator::print(ostream &outs) {
    outs << currentFloor;
    if (!servicing){
        outs << "w";
    } else {
        outs << "s" << targetFloor;
    }
}

Elevator::Elevator() {
    currentFloor = 0;
    servicing = false;
    targetFloor = 0;
}

void Elevator::setCurrentFloor(int currentFloorIn) {
    currentFloor = currentFloorIn;
}

bool Elevator::isServicing() const {
    return servicing;
}

int Elevator::getCurrentFloor() const {
    return currentFloor;
}

int Elevator::getTargetFloor() const {
    return targetFloor;
}
