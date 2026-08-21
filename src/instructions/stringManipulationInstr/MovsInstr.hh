#pragma once

#include "instructions/Instruction.hh"

class MovsInstr : public Instruction {
public:
    MovsInstr(const std::vector<uint8_t> &content, int position);
};
