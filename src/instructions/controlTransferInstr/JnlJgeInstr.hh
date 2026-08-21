#pragma once

#include <vector>

#include "instructions/Instruction.hh"

class JnlJgeInstr : public Instruction {
public:
    JnlJgeInstr(const std::vector<uint8_t> &content, int position);
};
