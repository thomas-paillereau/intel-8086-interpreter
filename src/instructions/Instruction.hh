#pragma once
#include <string>

class Instruction {
public:
    Instruction(std::string &name, int type);
    virtual std::string toString();

private:
    std::string name_;
    int type_;
};
