#pragma once

#include "instructions/Instruction.hh"

class IncInstr : public Instruction {
public:
    IncInstr(const std::vector<uint8_t> &content, int position);
};
