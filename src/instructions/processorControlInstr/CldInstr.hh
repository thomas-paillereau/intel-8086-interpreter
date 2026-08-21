#pragma once

#include "instructions/Instruction.hh"

class CldInstr : public Instruction {
public:
    CldInstr(const std::vector<uint8_t> &content, int position);
};
