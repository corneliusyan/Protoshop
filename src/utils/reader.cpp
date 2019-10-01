#include <iostream>

bool isNumber(const char& c) {
  return '0' <= c && c <= '9';
}

bool isWhitespace(const char& c) {
  return c == ' ' || c == '\n';
}

bool isPrintableCharacter(const char& c) {
  return '!' <= c && c <= '~';
}

int nextInt(char* bytes, int size, int* pointer) {
  int result = 0;
  while (*pointer < size && isNumber(bytes[*pointer])) {
    result *= 10;
    result += bytes[*pointer] - '0';
    (*pointer)++;
  }
  // set pointer to ignore whitespace
  while (*pointer < size && isWhitespace(bytes[*pointer])) {
    (*pointer)++;
  }
  return result;
}

std::string nextString(char* bytes, int size, int* pointer) {
  std::string result = "";
  while (*pointer < size && isPrintableCharacter(bytes[*pointer])) {
    result += bytes[*pointer];
    (*pointer)++;
  }
  // set pointer to ignore whitespace
  while (*pointer < size && isWhitespace(bytes[*pointer])) {
    (*pointer)++;
  }
  return result;
}

int nextInt16(char* bytes, int size, int* pointer) {
  int result = 0;
  for (int i = 0; i < 2; i++) {
    result |= (bytes[*pointer] << (i * 8));
    if (*pointer + 1 < size) {
      (*pointer)++;
    }
  }
  return result;
}

int nextInt32(char* bytes, int size, int* pointer) {
  int result = 0;
  for (int i = 0; i < 4; i++) {
    result |= (bytes[*pointer] << (i * 8));
    if (*pointer + 1 < size) {
      (*pointer)++;
    }
  }
  return result;
}
