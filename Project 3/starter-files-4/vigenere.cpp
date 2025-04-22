/*
 * vigenere.cpp
 * Project UID e98fd45ccce9d7195e89e6171a5451f2
 *
 * Sumin Kim, Lola Garcia
 * bellakim, lolahgar
 *
 * EECS 183: Project 3
 * Winter 2025
 *
 * Implementing Vigenère cipher function
 */

#include "utility.h"
#include "caesar.h"
#include "vigenere.h"
#include <iostream>

//************************************************************************
// Implement the functions below this line.
//************************************************************************

string vigenereCipher(string original, string keyword, bool encrypt) {
    // Convert the keyword all uppercase and strip all non-alphabetic characters
    keyword = toUpperCase(removeNonAlphas(keyword));
    
    // Ensure keyword has the same length as original (only alphabets)
    while (removeNonAlphas(original).size() > keyword.size()) {
            keyword += keyword;
        }
        if (original.size() < keyword.size()) {
            keyword = keyword.substr( 0, removeNonAlphas(original).size());
        }
    
    string cipherText = "";
    int j = 0;

    for (int i = 0; i < original.size(); ++i) {
        // Check if the character is an alphabet
        if (isalpha(original.at(i))) {
            // Find how much the character is away from a
            int vigenereKey = keyword.at(j) - 'A';
            // A negative key is used for decrypt
            if (!encrypt) {
                vigenereKey = -vigenereKey;
            }
            // Shift the character by vigenereKey
            cipherText += shiftAlphaCharacter(original.at(i), vigenereKey);
            // Update j
            ++j;
        }
        // If the character isn't an alphabet don't shift but keep it as it is
        else {
            cipherText += original.at(i);
        }
    }

    return cipherText;
}

