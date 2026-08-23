#pragma once

#include "Exception.hh"

class UnknownInstructionException : public Exception {
public:
    UnknownInstructionException(const char *message) : Exception(message) {
    }
};
