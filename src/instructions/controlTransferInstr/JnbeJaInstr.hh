#pragma once

#include "instructions/Instruction.hh"

class JnbeJaInstr : public Instruction {
public:
    JnbeJaInstr(const std::vector<uint8_t> &content, int position);
};
