#pragma once

#include "Exception.hh"

class NonExistentRegisterException : public Exception {
public:
    NonExistentRegisterException(const char *message) : Exception(message) {
    }
};
