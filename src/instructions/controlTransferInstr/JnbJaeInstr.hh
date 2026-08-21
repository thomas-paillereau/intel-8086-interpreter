#pragma once

#include <vector>

#include "instructions/Instruction.hh"

class JnbJaeInstr : public Instruction {
public:
    JnbJaeInstr(const std::vector<uint8_t> &content, int position);
};
