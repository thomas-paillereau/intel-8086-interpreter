#pragma once

#include "instructions/Instruction.hh"

class ShrInstr : public Instruction {
public:
    ShrInstr(const std::vector<uint8_t> &content, int position);
};
