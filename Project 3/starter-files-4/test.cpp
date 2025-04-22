#include "utility.h"
#include "caesar.h"
#include "vigenere.h"
#include "polybius.h"
#include <iostream>
#include <string>

using namespace std;

void testToUpperCase();
void testRemoveNonAlphas();
void testRemoveDuplicate();
void testCharToInt();
void testShiftAlphaCharacter();
void testCaesarCipher();
void testVigenereCipher();
void testMixKey();
void testFillGrid();
void testFindInGrid();
void testPolybiusSquare();

void startTests() {
    testToUpperCase();
    testRemoveNonAlphas();
    testRemoveDuplicate();
    testCharToInt();
    testShiftAlphaCharacter();
    testCaesarCipher();
    testVigenereCipher();
    testMixKey();
    testFillGrid();
    testFindInGrid();
    testPolybiusSquare();
    return;
}

void testToUpperCase() {
    cout << "Now testing toUpperCase()" << endl;
    cout << "Expected: 'DIAG @ 8 PM', Actual: " << toUpperCase("Diag @ 8 pm") << endl;
    cout << "Expected: 'BE THERE', Actual: " << toUpperCase("BE THERE") << endl;
    cout << "Expected: 'LOLA GARCIA!', Actual: " << toUpperCase("lola garcia!") << endl;
    cout << "Expected: '', Actual: " << toUpperCase("") << endl;
}

void testRemoveNonAlphas() {
    cout << "Now testing removeNonAlphas()" << endl;
    cout << "Expected: 'Diagpm', Actual: " << removeNonAlphas("Diag @ 8 pm") << endl;
    cout << "Expected: 'Bethere', Actual: " << removeNonAlphas("Be there") << endl;
    cout << "Expected: 'LOLAGARCIA', Actual: " << removeNonAlphas("LOLA GARCIA!") << endl;
    cout << "Expected: '', Actual: " << removeNonAlphas("") << endl;
}

void testRemoveDuplicate() {
    cout << "Now testing removeDuplicate()" << endl;
    cout << "Expected: 'HELOWRD', Actual: " << removeDuplicate("HELLOWRLD") << endl;
    cout << "Expected: 'BETHR', Actual: " << removeDuplicate("BETHERE") << endl;
    cout << "Expected: 'LOAGRCI!', Actual: " << removeDuplicate("LOLAGARCIA") << endl;
}

void testCharToInt() {
    cout << "Now testing charToInt()" << endl;
    cout << "Expected: 1, Actual: " << charToInt('1') << endl;
    cout << "Expected: 3, Actual: " << charToInt('3') << endl;
    cout << "Expected: 4, Actual: " << charToInt('4') << endl;
    cout << "Expected: 0, Actual: " << charToInt('0') << endl;
}

void testShiftAlphaCharacter() {
    cout << "Now testing shiftAlphaCharacter()" << endl;
    cout << "Expected: a, Actual: " << shiftAlphaCharacter('a', 0) << endl;
    cout << "Expected: d, Actual: " << shiftAlphaCharacter('b', 2) << endl;
    cout << "Expected: C, Actual: " << shiftAlphaCharacter('X', 5) << endl;
    cout << "Expected: X, Actual: " << shiftAlphaCharacter('C', -5) << endl;
    cout << "Expected: V, Actual: " << shiftAlphaCharacter('X', 50) << endl;
    cout << "Expected: a, Actual: " << shiftAlphaCharacter('y', -50) << endl;
}

void testCaesarCipher() {
    cout << "Now testing caesarCipher()" << endl;
    cout << "Expected: 'Cuuj cu qj jxu Tyqw qj 11 f.c.', Actual: " << caesarCipher("Meet me at the Diag at 11 p.m.", 42, true) << endl;
    cout << "Expected: 'Meet me at the Diag at 11 p.m.', Actual: " << caesarCipher("Cuuj cu qj jxu Tyqw qj 11 f.c.", 42, false) << endl;
    cout << "Expected: 'Jm bpmzm', Actual: " << caesarCipher("Be there", 8, true) << endl;
    cout << "Expected: 'HELLOWORLD', Actual: " << caesarCipher("NKRRUCUXRJ", 32, false) << endl;
}

void testVigenereCipher() {
    cout << "Now testing vigenereCipher()" << endl;
    cout << "Expected: 'Euyb dv ee lxy Lzrk ll 11 f.g.', Actual: " << vigenereCipher("Meet me at the Diag at 11 p.m.", "Squirrel!", true) << endl;
    cout << "Expected: 'Meet me at the Diag at 11 p.m.', Actual: " << vigenereCipher("Euyb dv ee lxy Lzrk ll 11 f.g.", "Squirrel!", false) << endl;
    cout << "Expected: 'Ii essns', Actual: " << vigenereCipher("Be there", "Hello World :)", true) << endl;
    cout << "Expected: 'Be there', Actual: " << vigenereCipher("Ii essns", "Hello World :)", false) << endl;
}

void testMixKey() {
    cout << "Now testing mixKey()" << endl;
    cout << "Expected: POLYBIUSACDEFGHJKMNQRTVWXZ0123456789, Actual: " << mixKey("POLYBIUS") << endl;
}

void testFillGrid() {
    cout << "Now testing fillGrid()" << endl;
    char grid[SIZE][SIZE];
    fillGrid(grid, ALNUM);
    printGrid(grid);
}

void testFindInGrid() {
    cout << "Now testing findInGrid()" << endl;
    char grid[SIZE][SIZE];
    fillGrid(grid, ALNUM);
    cout << "Expected: '00', Actual: " << findInGrid('A', grid) << endl;
    cout << "Expected: '53', Actual: " << findInGrid('7', grid) << endl;
}

void testPolybiusSquare() {
    cout << "Now testing polybiusSquare()" << endl;
    char grid[SIZE][SIZE];
    cout << "Expected: '11110533 000102 1533 341411 04113334', Actual: " << polybiusSquare(grid, "183", "EECS 183 IS THE BEST", true) << endl;
    cout << "Expected: 'EECS 183 IS THE BEST', Actual: " << polybiusSquare(grid, "183", "11110533 000102 1533 341411 04113334", false) << endl;
}
