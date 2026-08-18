#include "Instruction.hh"

#include <iostream>
#include <ostream>

std::string Instruction::toString() const {
    if (name_ == "UNDEFINED")
        return name_;

    std::string res;
    res += name_;
    if (mod_ != -1 && rm_ != -1) {
    } else if (reg_ != -1) {
    } else if (data_used_) {
    } else if (addr_used_) {
    } else {
    }
    return res;
}

void Instruction::print() const {
    std::cout << toString() << std::endl;
}

int Instruction::getSize() const {
    return size_;
}
