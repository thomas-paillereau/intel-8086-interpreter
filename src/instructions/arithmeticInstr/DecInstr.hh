#pragma once

#include <vector>

#include "instructions/Instruction.hh"

class DecInstr : public Instruction {
public:
    DecInstr(const std::vector<uint8_t> &content, int position);
};
