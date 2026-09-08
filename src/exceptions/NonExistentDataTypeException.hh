#pragma once

#include "Exception.hh"

class NonExistentDataTypeException : public Exception {
public:
    NonExistentDataTypeException(const char *message) : Exception(message) {
    }
};
