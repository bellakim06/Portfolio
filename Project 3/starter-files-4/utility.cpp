/*
 * utility.cpp
 * Project UID e98fd45ccce9d7195e89e6171a5451f2
 *
 * Sumin Kim, Lola Garcia
 * bellakim, lolahgar
 *
 * EECS 183: Project 3
 * Winter 2025
 *
 * Write functions which will serve as helper functions at caesar.cpp,
   vigenere.cpp, and polybius.cpp
 */

#include "utility.h"
#include <iostream>

//************************************************************************
// Implement the functions below this line.
//************************************************************************

string toUpperCase(string original) {
    for (int i = 0; i < original.size(); ++i) {
        // check if the character is alphabet
        if (isalpha(original.at(i))) {
        // check if the character is lower and uppercase it if it is
               if (islower(original.at(i))) {
                   original.at(i) = toupper(original.at(i));
               }
           }
       }
    
       return original;
}


string removeNonAlphas(string original) {
    string noAlphaOriginal = "";
       for (int i = 0; i < original.size(); ++i) {
           // check if the character is alphabet and combine those characters that are
           if (isalpha(original.at(i))) {
               noAlphaOriginal += original.at(i);
           }
       }
    
       return noAlphaOriginal;
}


int charToInt(char original) {
    // Converts the character original into its ASCII integer value and subtract '0''s ASCII integer value
    return static_cast<int>(original) - static_cast<int>('0');
}


string removeDuplicate(string original) {
    string noDuplicates;
    for (int i = 0; i < original.size(); ++i) {
        char a = original.at(i);
        // Only add 'a' if it is not already in noDuplicates
        if (noDuplicates.find(a) == string::npos) {
            noDuplicates += a;
        }
    }
    
        return noDuplicates;
}

////////////////////////////////////////////////////////////////////////////////
// Do not touch code below. ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void printGrid(const char grid[SIZE][SIZE]) {
    for (int col = 0; col < SIZE; col++) {
        cout << " ---";
    }
    cout << endl;
    for (int row = 0; row < SIZE; row++) {
        cout << "| ";
        for (int col = 0; col < SIZE; col++) {
            cout << string(1, grid[row][col]) + " | ";
        }
        cout << endl;
        for (int col = 0; col < SIZE; col++) {
            cout << " ---";
        }
        cout << endl;
    }
}
