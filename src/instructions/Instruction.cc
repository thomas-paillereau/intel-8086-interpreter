#include "Instruction.hh"

#include <iostream>
#include <ostream>

std::string Instruction::toString() const {
    return "UNDEFINED";
}

void Instruction::print() const {
    std::cout << toString() << std::endl;
}

int Instruction::getSize() const {
    return size_;
}
