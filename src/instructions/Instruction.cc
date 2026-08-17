#include "Instruction.hh"

Instruction::Instruction(std::string &name, int type) : name_(name), type_(type) {
}

std::string Instruction::toString() {
    return "None";
}
