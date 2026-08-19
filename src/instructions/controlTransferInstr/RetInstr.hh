#pragma once

#include <vector>

#include "instructions/Instruction.hh"

class RetInstr : public Instruction {
public:
    RetInstr(const std::vector<uint8_t> &content, int position);
};
