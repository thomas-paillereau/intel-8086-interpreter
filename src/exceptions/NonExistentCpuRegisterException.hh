#pragma once

#include "Exception.hh"

class NonExistentCpuRegisterException : public Exception {
public:
    NonExistentCpuRegisterException(const char *message) : Exception(message) {
    }
};
