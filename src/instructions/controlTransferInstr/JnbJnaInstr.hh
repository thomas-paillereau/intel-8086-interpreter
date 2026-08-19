#pragma once

#include <vector>

#include "instructions/Instruction.hh"

class JnbJnaInstr : public Instruction {
public:
    JnbJnaInstr(const std::vector<uint8_t> &content, int position);
};
