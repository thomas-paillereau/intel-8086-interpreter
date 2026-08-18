#include "Instruction.hh"

#include <iostream>
#include <ostream>

std::string Instruction::toString() {
    return "UNDEFINED";
}

void Instruction::print() {
    std::cout << toString() << std::endl;
}

int Instruction::getSize() {
    return size_;
}
