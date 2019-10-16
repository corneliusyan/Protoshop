#ifndef PROTOSHOP_UTIL_READER
#define PROTOSHOP_UTIL_READER

#include <iostream>

/**
 * return true if the character is number (0-9)
 */
bool isNumber(const char& c);

/**
 * return true if the character is whitespace (space
 * or newline)
 */
bool isWhitespace(const char& c);

bool isNewline(const char& c);

bool isSpace(const char& c);

bool isComment(const char& c);

/**
 * return true if the character is printable ascii
 * character, non whitespace (has ascii dec value 33 - 126)
 */
bool isPrintableCharacter(const char& c);

/**
 * return the next ascii integer found starting from pointer
 * update the pointer to the next pointer
 * the bytes will be read until size only
 */
int nextInt(char* bytes, int size, int* pointer);

/**
 * return the next string found starting from pointer
 * update the pointer to the next pointer
 * the bytes will be read until size only
 */
std::string nextString(char* bytes, int size, int* pointer);

/**
 * return the 2 byte starting from pointer as 16-bit integer
 * update the pointer to the next pointer
 * the bytes will be read until size only
 */
int nextInt16(char* bytes, int size, int* pointer);

/**
 * return the 4 byte starting from pointer as 32-bit integer
 * update the pointer to the next pointer
 * the bytes will be read until size only
 */
int nextInt32(char* bytes, int size, int* pointer);

#endif
