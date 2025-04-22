/*
 * Copyright 2023 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * Final Project - Elevators
 */
 
////////////////////////////////////////////////
// You will submit test.cpp to the autograder //
// FOR LAB 8, but NOT the final project Core  //
////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include "AI.h"
#include "Building.h"
#include "BuildingState.h"
#include "Elevator.h"
#include "Floor.h"
#include "Game.h"
#include "Move.h"
#include "Person.h"
#include "SatisfactionIndex.h"
#include "Utility.h"


using namespace std;

// declare your test functions here
void test_floor();

void start_tests() {
    test_floor();
    
    return;
}

// write test functions here
void test_floor() {
    int indicesToRemove[MAX_PEOPLE_PER_FLOOR] = {0, 2, 4, 6, 8, };
    Person Person1("0f0t0a1");
    Person Person2("0f0t1a1");
    Person Person3("0f0t2a0");
    Person  Person4("0f0t3a0");
    Person Person5("0f0t4a0");
    Person Person6("0f0t5a0");
    Person Person7("0f0t6a1");
    Person Person8("0f0t7a1");
    Person Person9("0f0t8a1");
    Person Person10("0f0t9a1");
    Floor testFloor;
    testFloor.addPerson(Person1, 1);
    testFloor.addPerson(Person2, 1);
    testFloor.addPerson(Person3, 1);
    testFloor.addPerson(Person4, 1);
    testFloor.addPerson(Person5, 1);
    testFloor.addPerson(Person6, 1);
    testFloor.addPerson(Person7, 1);
    testFloor.addPerson(Person8, 1);
    testFloor.addPerson(Person9, 1);
    testFloor.addPerson(Person10, 1);
    testFloor.removePeople(indicesToRemove, 5);
    testFloor.printFloorPickupMenu(cout);
    
   
}
