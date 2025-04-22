/*
 * polybius.cpp
 * Project UID e98fd45ccce9d7195e89e6171a5451f2
 *
 * Sumin Kim, Lola Garcia
 * bellakim, lolahgar
 *
 * EECS 183: Project 3
 * Winter 2025
 *
 * Implementing functions that use Polybius Square to encrypt and decrypt
 */


#include "polybius.h"
#include <string>
using namespace std;

//************************************************************************
// Implement the functions below this line.
//************************************************************************

string mixKey(string key) {
    // Put key first before ALNUM
    key += ALNUM;
    // Remove any duplicates after ALNUM
    key = removeDuplicate(key);

    return key;
}

void fillGrid(char grid[SIZE][SIZE], string content) {
    int j = 0;
    // Iterate through each row and column of the grid
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            // Assign character from content to grid
            grid[row][col] = content.at(j);
            j++;
        }
    }
    return;
}

string findInGrid(char c, char grid[SIZE][SIZE]) {
    string rowpluscol;
    // Iterate through each row and column of the grid
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            // Check if c matches up with the one in the grid
            if (grid[row][col] == c) {
                // Convert row and col into a string representation and put them together 
                rowpluscol = to_string(row) + to_string(col);
            }
        }
    }
    
    return rowpluscol;
}

string polybiusSquare(char grid[SIZE][SIZE], string key, 
                      string original, bool encrypt) {
    string content = mixKey(key);
    fillGrid(grid, content);
    string ciphertext;
    
    // Encrypt the original message
    if (encrypt) {
        for (int i = 0; i < original.size(); i++) {
            // If there is a space on the original put a space on the ciphertext
            if (original.at(i) == ' ') {
                ciphertext += " ";
            }
            // Otherwise find the coordinates of the character and append to ciphertext
            else {
                ciphertext += findInGrid(original.at(i), grid);
            }
        }
    }
    
    // Decrypt the original message
    else if (!encrypt) {
        for (int j = 0; j < original.size(); j++) {
            // If there is a space on the original put a space on the ciphertext
            if (original.at(j) == ' ') {
                ciphertext += " ";
            }
            // Othersie convert the coordinates back to the character
            else {
                int row = charToInt(original.at(j));
                int col = charToInt(original.at(j+1));
                ciphertext += grid[row][col];
                j ++;
            }
        }
    }
            
                   
    return ciphertext;
}
