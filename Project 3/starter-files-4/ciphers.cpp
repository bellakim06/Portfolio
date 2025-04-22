/*
 * ciphers.cpp
 * Project UID e98fd45ccce9d7195e89e6171a5451f2
 *
 * Sumin Kim, Lola Garcia
 * bellakim, lolahgar
 *
 * EECS 183: Project 3
 * Winter 2025
 *
 * Creating a program that lets the user select a cipher, choose to encrypt or decrypt a message, input the message and key, and display the resulting message.
 */

#include "utility.h"
#include "caesar.h"
#include "vigenere.h"
#include "polybius.h"
#include <iostream>
#include <string>

using namespace std;

//************************************************************************
// Implement the functions below this line.
//************************************************************************


/*
 * Requires: Nothing.
 * Modifies: Nothing.
 * Effects:  Returns true if cipher matches "CAESAR" or "C"         (case-insensitive), otherwise returns false
 */
bool checkCaesar(string cipher);

/*
 * Requires: Nothing.
 * Modifies: Nothing.
 * Effects:  Returns true if cipher matches "VIGENERE" or "V"
 *           (case-insensitive), otherwise returns false
 */
bool checkVigenere(string cipher);

/*
 * Requires: Nothing
 * Modifies: Nothing.
 * Effects:  Returns true if cipher matches "POLYBIUS" or "P"
 *           (case-insensitive), otherwise returns false
 */
bool checkPolybius(string cipher);

/*
 * Requires: Nothing.
 * Modifies: Nothing.
 * Effects:  Returns true if mode matches "ENCRYPT" or "E" (case-insensitive),
 *           otherwise returns false.
 */
bool checkEncrypt(string mode);

/*
 * Requires: Nothing.
 * Modifies: Nothing.
 * Effects:  Returns true if mode matches "DECRYPT" or "D" (case-insensitive),
 *           otherwise returns false.
 */
bool checkDecrypt(string mode);

/*
 * Requires: Nothing.
 * Modifies: cout, cin
 * Effects:  Prompts the user to enter a key and returns the entered key.
 */
string getKey();


void ciphers() {
    // Ask user for cipher (Caesar, Vigenere, or Polybius)
    string cipher;
    cout << "Choose a cipher (Caesar, Vigenere, or Polybius): ";
    getline(cin, cipher);

    // Validate cipher
    if (!checkCaesar(cipher) && !checkVigenere(cipher) && !checkPolybius(cipher)) {
        cout << "Invalid cipher!" << endl;
        return;
    }

    // Ask user for mode (encrypt or decrypt)
    string mode;
    cout << "Encrypt or decrypt: ";
    getline(cin, mode);

    
    // Validate mode
    if (!checkEncrypt(mode) && !checkDecrypt(mode)) {
        cout << "Invalid mode!" << endl;
        return;
    }
    
    // Ask user for message
    string message;
    cout << "Enter a message: ";
    getline(cin, message);

    // Determine encryption mode
    bool encrypt = false;
    if (checkEncrypt(mode)) {
        encrypt = true;
    }
    if (checkDecrypt(mode)) {
        encrypt = false;
    }


    // Declare variable to store the final message
    string finalMessage;

    // Encrypt or decrypt message using selected cipher and key(word)
    int keyValue = 0;
    
    // If Caesar cipher is chosen
    if (checkCaesar(cipher)) {
        // Ask for key
        string key = getKey();
        // An integer that should be multiplied to shift a value left by one decimal place
        const int DECIMAL_BASE = 10;
        // Convert key string to integer
        for (int i = 0; i < key.size(); i++) {
            // Shift the keyValue left by one decimal place before adding the next digit from the string
            keyValue *= DECIMAL_BASE;
            keyValue += charToInt(key.at(i));
        }
        // Do Caesar cipher encryption or decryption
        finalMessage = caesarCipher(message, keyValue, encrypt);
    }

    // If Vigenere cipher is chosen
    if (checkVigenere(cipher)) {
        // Ask for key
        string key = getKey();
        // Validate if key contains at least one alphabetic character
        if (removeNonAlphas(key) == "") {
            cout << "Invalid key!" << endl;
            return;
        }
        else {
            // Do Vigenere cipher encryption or decryption
            finalMessage = vigenereCipher(message, key, encrypt);
        }
    }

    // If Polybius cipher is chosen
    char grid[SIZE][SIZE];
    if (checkPolybius(cipher)) {
        
        // Convert the message to uppercase
        message = toUpperCase(message);
        
        // Validate if message contains only alphanumeric characters and spaces
        for (int k = 0; k < message.size(); k++) {
            if (!isalpha(message.at(k)) && !isdigit(message.at(k)) &&
                message.at(k) != ' '){
                    cout << "Invalid message!" << endl;
                    return;
                }
        }
        
        // Ask for key
        string key = getKey();

        // Validate if key contains only alphabetic characters
        for (int j = 0; j < key.size(); j++) {
            if (!isalpha(key.at(j)) && !isdigit(key.at(j))) {
                cout << "Invalid key!" << endl;
                return;
            }
        }

        // Convert the key to uppercase and remove duplicates
        key = toUpperCase(key);
        key = removeDuplicate(key);

        // Do Polybius square encryption or decryption
        finalMessage = polybiusSquare(grid, key, message, encrypt);
    }

    // Determine whether message was encrypted or decrypted
    string modetype;
    if (checkEncrypt(mode)) {
        modetype = "encrypted";
    }
    if (checkDecrypt(mode)) {
        modetype = "decrypted";
    }

    // Print the encrypted or decrypted message
    cout << "The " << modetype << " message is: " << finalMessage << endl;

    return;
}



bool checkCaesar(string cipher) {
    if (toUpperCase(cipher) == "CAESAR" ||
        toUpperCase(cipher) == "C") {
        return true;
    }
    else {
        return false;
    }
}


bool checkVigenere(string cipher) {
    if (toUpperCase(cipher) == "VIGENERE" ||
        toUpperCase(cipher) == "V") {
        return true;
    }
    else {
        return false;
    }
}


bool checkPolybius(string cipher) {
    if (toUpperCase(cipher) == "POLYBIUS"  ||
        toUpperCase(cipher) == "P") {
        return true;
    }
    else {
        return false;
    }
}


bool checkEncrypt(string mode) {
    if (toUpperCase(mode) == "ENCRYPT" ||
        toUpperCase(mode) == "E") {
        return true;
    }
    else {
        return false;
    }
}


bool checkDecrypt(string mode) {
    if (toUpperCase(mode) == "DECRYPT" ||
        toUpperCase(mode) == "D") {
        return true;
    }
    else {
        return false;
    }
}


string getKey() {
    string key;
    cout << "What is your key: ";
    getline(cin, key);
    return key;
}
