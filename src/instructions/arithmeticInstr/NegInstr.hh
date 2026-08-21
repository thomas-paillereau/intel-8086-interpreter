#pragma once

#include <vector>

#include "instructions/Instruction.hh"

class NegInstr : public Instruction {
public:
    NegInstr(const std::vector<uint8_t> &content, int position);
};
