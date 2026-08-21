#pragma once

#include "instructions/Instruction.hh"

class LoopInstr : public Instruction {
public:
    LoopInstr(const std::vector<uint8_t> &content, int position);
};
