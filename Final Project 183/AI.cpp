/*
 * Copyright 2023 University of Michigan EECS183
 *
 * AI.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * <#Sumin Kim, Lola Garcia, Nicolas Galeano, Swetha Chimalakonda#>
 * <#bellakim, lolahgar, ngaleano, swethakc#>
 *
 * Final Project - Elevators
 */

#include "AI.h"
#include <cassert>
#include <cmath>

string getAIMoveString(const BuildingState& buildingState) {
    // check if there are any people at all
    int totalNumPeople = 0;
    for (int i = 0; i < NUM_FLOORS; i++) {
        totalNumPeople += buildingState.floors[i].numPeople;
    }
    if (totalNumPeople == 0) {
        return "";
    }

    // check if all elevators are busy
    int numBusy = 0;
    for (int i = 0; i < NUM_ELEVATORS; i++) {
        if (buildingState.elevators[i].isServicing) {
            numBusy++;
        }
    }

    // if at least one elevator is idle
    if (numBusy < NUM_ELEVATORS) {
        for (int i = 0; i < NUM_ELEVATORS; i++) {
            _Elevator elevator = buildingState.elevators[i];

            // if elevator is idle
            if (!elevator.isServicing) {
                int floor = elevator.currentFloor;
                int peopleHere = buildingState.floors[floor].numPeople;

                // if there are people on the same floor → pickup
                if (peopleHere > 0) {
                    return "e" + to_string(i) + "p";
                }
            }
        }

        // if no pickups possible → send idle elevator to most needed floor
        int mostPeople = 0;
        int mostAnger = 0;
        int targetFloor = -1;

        for (int i = 0; i < NUM_FLOORS; i++) {
            _Floor floor = buildingState.floors[i];
            if (floor.numPeople > mostPeople) {
                mostPeople = floor.numPeople;
                targetFloor = i;
                mostAnger = 0;
                for (int j = 0; j < floor.numPeople; j++) {
                    mostAnger += floor.people[j].angerLevel;
                }
            }
            else if (floor.numPeople == mostPeople && floor.numPeople > 0) {
                int angerSum = 0;
                for (int j = 0; j < floor.numPeople; j++) {
                    angerSum += floor.people[j].angerLevel;
                }
                if (angerSum > mostAnger) {
                    mostAnger = angerSum;
                    targetFloor = i;
                }
            }
        }

        // choose the closest idle elevator to send
        int chosenElevator = -1;
        int minDistance = NUM_FLOORS;
        for (int i = 0; i < NUM_ELEVATORS; i++) {
            _Elevator elevator = buildingState.elevators[i];
            if (!elevator.isServicing) {
                int dist = abs(elevator.currentFloor - targetFloor);
                if (dist < minDistance) {
                    minDistance = dist;
                    chosenElevator = i;
                }
            }
        }

        if (chosenElevator != -1 && targetFloor != -1) {
            return "e" + to_string(chosenElevator) + "f" + to_string(targetFloor);
        }
    }

    // no valid move → pass
    return "";
}

string getAIPickupList(const Move& move, const BuildingState& buildingState,
                       const Floor& floorToPickup) {
    int numElevator = move.getElevatorId();
    _Elevator elevatorToUse = buildingState.elevators[numElevator];
    
    int peopleAngerLevels[MAX_PEOPLE_PER_FLOOR];
    bool peopleDirection[MAX_PEOPLE_PER_FLOOR];
    int numPeople = floorToPickup.getNumPeople();

    // loop to extract anger levels and direction for each person
    for (int i = 0; i < numPeople; ++i) {
        Person person = floorToPickup.getPersonByIndex(i);
        peopleAngerLevels[i] = person.getAngerLevel();
        peopleDirection[i] = person.getTargetFloor() > person.getCurrentFloor();
    }

    int upAnger = 0;
    int downAnger = 0;

    // sum up total anger based on direction
    for (int j = 0; j < numPeople; ++j) {
        if (peopleDirection[j]) {
            upAnger += peopleAngerLevels[j];
        }
        else {
            downAnger += peopleAngerLevels[j];
        }
    }

    string pickupList;

    // if more anger going up, pick people going up
    if (upAnger > downAnger) {
        for (int i = 0; i < floorToPickup.getNumPeople(); ++i) {
            if (peopleDirection[i] == true) {
                pickupList += to_string(i);
            }
        }
    }
    // if more anger going down, pick people going down
    else if (downAnger > upAnger) {
        for (int i = 0; i < floorToPickup.getNumPeople(); ++i) {
            if (peopleDirection[i] == false) {
                pickupList += to_string(i);
            }
        }
    }
    // equal anger, choose based on number of people waiting
    else {
        int numUpWaiting = 0;
        int numDownWaiting = 0;

        for (int i = 0; i < floorToPickup.getNumPeople(); ++i) {
            if (peopleDirection[i] == true) {
                numUpWaiting++;
            } else {
                numDownWaiting++;
            }
        }

        // if more people going up, pick them
        if (numUpWaiting > numDownWaiting) {
            for (int i = 0; i < floorToPickup.getNumPeople(); ++i) {
                if (peopleDirection[i] == true) {
                    pickupList += to_string(i);
                }
            }
        }
        // otherwise pick people going down
        else {
            for (int i = 0; i < floorToPickup.getNumPeople(); ++i) {
                if (peopleDirection[i] == false) {
                    pickupList += to_string(i);
                }
            }
        }
    }

    return pickupList;
}
