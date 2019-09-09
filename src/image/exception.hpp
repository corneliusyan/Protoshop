#ifndef PROTOSHOP_IMAGE_EXCEPTION
#define PROTOSHOP_IMAGE_EXCEPTION

#include "../utils/exception.hpp"
#include <iostream>

class ImageLoadException : public Exception {
public:
  ImageLoadException(const char* message) : Exception(message) {}
  ImageLoadException(const std::string message) : Exception(message) {}
};

#endif
