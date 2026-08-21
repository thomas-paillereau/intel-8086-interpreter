#pragma once

#include "instructions/Instruction.hh"

class StdInstr : public Instruction {
public:
    StdInstr(const std::vector<uint8_t> &content, int position);
};
