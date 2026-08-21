#pragma once

#include <vector>

#include "instructions/Instruction.hh"

class SbbInstr : public Instruction {
public:
    SbbInstr(const std::vector<uint8_t> &content, int position);
};
