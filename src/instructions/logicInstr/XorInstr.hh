#pragma once

#include <vector>

#include "instructions/Instruction.hh"

class XorInstr : public Instruction {
public:
    XorInstr(const std::vector<uint8_t> &content, int position);
};
