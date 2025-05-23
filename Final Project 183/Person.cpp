/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Person.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * Sumin Kim, Nicholas Galeano, Swetha Chimalakonda, Lola Garcia
 * bellakim, ngaleano, swethakc, lolahgar
 *
 * Final Project - Elevators
 */

#include "Person.h"
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

Person::Person(string inputString) {
    // create stringstream using input
    stringstream personSS(inputString);
    // variable to store unneccessary characters
    char junk;
    // parse inputString to set member variables
    personSS >> turn >> junk >> currentFloor >> junk >> targetFloor
        >> junk >> angerLevel;
}

bool Person::tick(int currentTime) {
    if (currentTime % TICKS_PER_ANGER_INCREASE == 0) {
        angerLevel++;
    }
    if (angerLevel == MAX_ANGER) {
        return true;
    }
    return false;
}

void Person::print(ostream& outs) {
    // prints infoString of person without turn
    outs << "f" << currentFloor << "t" << targetFloor << "a" << angerLevel;
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Person::Person() {
    turn = 0;
    currentFloor = 0;
    targetFloor = 0;
    angerLevel = 0;
}

int Person::getTurn() const {
    return turn;
}

int Person::getCurrentFloor() const {
    return currentFloor;
}

int Person::getTargetFloor() const {
    return targetFloor;
}

int Person::getAngerLevel() const {
    return angerLevel;
}

ostream& operator<< (ostream& outs, Person p)
{
    p.print(outs);
    return outs;
}
