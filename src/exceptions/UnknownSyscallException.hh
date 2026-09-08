#pragma once

#include "Exception.hh"

class UnknownSyscallException : public Exception {
public:
    UnknownSyscallException(const char *message) : Exception(message) {
    }
};
