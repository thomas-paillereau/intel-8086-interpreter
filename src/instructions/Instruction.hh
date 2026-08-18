#pragma once
#include <string>

class Instruction {
public:
    virtual std::string toString();

    void print();

    int getSize();

    // TODO exec

protected:
    int size_;
};
