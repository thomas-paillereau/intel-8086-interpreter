#pragma once

#include "instructions/Instruction.hh"

class JbJnaeInstr : public Instruction {
public:
    JbJnaeInstr(const std::vector<uint8_t> &content, int position);
};
