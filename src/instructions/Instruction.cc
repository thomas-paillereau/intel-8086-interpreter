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
    } else if (info_byte_type_ == DATA) {
    } else if (info_byte_type_ == ADDR_HL) {
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
