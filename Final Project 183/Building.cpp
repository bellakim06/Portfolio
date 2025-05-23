/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Building.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * Sumin Kim, Nicholas Galeano, Swetha Chimalakonda, Lola Garcia
 * bellakim, ngaleano, swethakc, lolahgar
 *
 * Final Project - Elevators
 */

#include "Building.h"

using namespace std;

void Building::spawnPerson(Person newPerson){
    int request = newPerson.getTargetFloor() - newPerson.getCurrentFloor();
            
            floors[newPerson.getCurrentFloor()].addPerson(newPerson, request);
        }

void Building::update(Move move){
    if (move.isPassMove() || move.isQuitMove() || move.isSaveMove()) {
            return;
        }
        else if (move.isPickupMove()) {
            int elevatorId = move.getElevatorId();
            int targetFloor = move.getTargetFloor();

            // Obtain the current floor from the elevator
            int currentFloor = elevators[elevatorId].getCurrentFloor();

            // Obtain the list of people to pick up from the move
            int indicesToRemove[MAX_PEOPLE_PER_FLOOR];
            move.copyListOfPeopleToPickup(indicesToRemove);

            // Remove the people from the floor
            floors[currentFloor].removePeople(indicesToRemove, move.getNumPeopleToPickup());

            // Send the elevator to the target floor
            elevators[elevatorId].serviceRequest(targetFloor);
        }
        else {
            int elevatorId = move.getElevatorId();
            int targetFloor = move.getTargetFloor();
            elevators[elevatorId].serviceRequest(targetFloor);
        }
    }

int Building::tick(Move move){
    update(move);
            int explodedPeople = 0;
            
            time++;
            
            for (int i = 0; i < NUM_ELEVATORS; i++) {
                elevators[i].tick(time);
            }
            for (int i = 0; i < NUM_FLOORS; i++) {
                explodedPeople += floors[i].tick(time);
            }
            return explodedPeople;
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Building::Building() {
    time = 0;
}

void Building::setElevator(string elevatorInfo, int elevatorId) {
    int i = 0;
    string currPosString = "";
    string destPosString = "";

    while(elevatorInfo[i] != 's' && elevatorInfo[i] != 'w'){
        currPosString += elevatorInfo[i];
        i++;
    }
    elevators[elevatorId] = Elevator();

    elevators[elevatorId].setCurrentFloor(stoi(currPosString));

    if (elevatorInfo[i] == 's') {
        i++;
        while (i < (int)elevatorInfo.size()) {
            destPosString += elevatorInfo[i];
            i++;
        }
        elevators[elevatorId].serviceRequest(stoi(destPosString));
    }
}

int Building::getTime() const {
    return time;
}

void Building::setTime(int timeIn) {
    time = timeIn;
}

void Building::prettyPrintBuilding(ostream& outs) const {
    for (int i = NUM_FLOORS - 1; i >= 0; --i) {
            outs << "   ";
            for (int j = 0; j < 2 * NUM_ELEVATORS + 1; ++j) {

                outs << '-';
            }

            outs << endl << "   ";

            for (int j = 0; j <  NUM_ELEVATORS; ++j) {
                char floorIndicatorIcon = ' ';

                if (elevators[j].getCurrentFloor() == i &&
                    elevators[j].isServicing()) {

                    char floorServiceIndicator = ('0'
                                               + elevators[j].getTargetFloor());
                    floorIndicatorIcon = floorServiceIndicator;
                }

                outs << "|" << floorIndicatorIcon;
            }
            outs << "|";

            floors[i].prettyPrintFloorLine1(outs);
            outs << i << "  ";
            for (int j = 0; j <  NUM_ELEVATORS; ++j) {

                outs << "|" << (elevators[j].getCurrentFloor() == i ? 'E' : ' ');
            }
            outs << "|";

            floors[i].prettyPrintFloorLine2(outs);
        }
        outs << "   ";
        for (int j = 0; j < 2 * NUM_ELEVATORS + 1; ++j) {
            outs << '-';
        }
        outs << endl << "   ";
        for (int j = 0; j < NUM_ELEVATORS; ++j) {
            outs << " " << j;
        }
        outs << endl;
}

Elevator Building::getElevatorById(int elevatorId) const {
    return elevators[elevatorId];
}

Floor Building::getFloorByFloorNum(int floorNum) const {
    return floors[floorNum];
}

BuildingState Building::getBuildingState() const {
    BuildingState buildingState;
    buildingState.turn = time;

    for (int i = 0; i < NUM_FLOORS; ++i) {
        buildingState.floors[i].floorNum = i;
        buildingState.floors[i].hasDownRequest = floors[i].getHasDownRequest();
        buildingState.floors[i].hasUpRequest = floors[i].getHasUpRequest();

        int & np = buildingState.floors[i].numPeople;

        for (int j = 0; j < floors[i].getNumPeople(); ++j) {

            Person p = floors[i].getPersonByIndex(j);
            buildingState.floors[i].people[np++].angerLevel = p.getAngerLevel();
        }
    }

    for (int i = 0; i < NUM_ELEVATORS; ++i) {
        Elevator e = elevators[i];

        buildingState.elevators[i].elevatorId = i;
        buildingState.elevators[i].targetFloor = e.getTargetFloor();
        buildingState.elevators[i].currentFloor = e.getCurrentFloor();
        buildingState.elevators[i].isServicing = e.isServicing();
    }

    return buildingState;
}
