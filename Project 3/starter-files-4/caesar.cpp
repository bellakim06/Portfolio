/*
 * caesar.cpp
 * Project UID e98fd45ccce9d7195e89e6171a5451f2
 *
 * Sumin Kim, Lola Garcia
 * bellakim, lolahgar
 *
 * EECS 183: Project 3
 * Winter 2025
 *
 * Implementing Caesar cipher functions
 */

#include "caesar.h"
#include <iostream>

//************************************************************************
// Implement the functions below this line.
//************************************************************************

char shiftAlphaCharacter(char c, int n) {
    // Make n to be within the range [0, 25]
    if (n > 26) {
        n = n % 26;
    }
    if (n < 0) {
       n = (n % 26 + 26) % 26;
    }
    
    // Shift the character by n
    int cVal = c + n;
    if (islower(c)) {
        // Go around if it goes past 'z'
        if (cVal > 'z') {
            cVal -= 26;
        }
    }
    if (isupper(c)) {
        // Go around if it goes past 'Z'
        if (cVal > 'Z') {
            cVal -= 26;
        }
    }
    
    // Convert back to char
    c = static_cast<char>(cVal);
    
    return c;
}

    
string caesarCipher(string original, int key, bool encrypt) {
    string caesarResult;
    
    // A negative key would shift the letters back (decrypt)
    if (!encrypt) {
        key = -key;
    }
    
    for (int i = 0; i < original.size(); ++i) {
        char a = original.at(i);
        // Only shift when a is an alphabet
        if (isalpha(a)) {
            a = shiftAlphaCharacter(original.at(i), key);
        }
        caesarResult += a;
    }
    
    return caesarResult;
}
