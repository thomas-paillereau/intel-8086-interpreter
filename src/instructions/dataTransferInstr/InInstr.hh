#pragma once

#include <vector>

#include "instructions/Instruction.hh"

class InInstr : public Instruction {
public:
    InInstr(const std::vector<uint8_t> &content, int position);
};
