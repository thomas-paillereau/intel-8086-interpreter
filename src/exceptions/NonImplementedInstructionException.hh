#pragma once

#include "Exception.hh"

class NonImplementedInstructionException : public Exception {
public:
    NonImplementedInstructionException(const char *message) : Exception(message) {
    }
};
