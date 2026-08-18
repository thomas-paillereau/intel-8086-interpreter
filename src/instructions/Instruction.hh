#pragma once
#include <string>

class Instruction {
public:
    Instruction() = default;

    virtual std::string toString() const;

    void print() const;

    int getSize() const;

    // TODO virtual void exec();

protected:
    int size_ = 1;
};
