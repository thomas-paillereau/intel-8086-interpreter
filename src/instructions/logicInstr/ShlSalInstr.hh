#pragma once

#include <vector>

#include "instructions/Instruction.hh"

class ShlSalInstr : public Instruction {
public:
    ShlSalInstr(const std::vector<uint8_t> &content, int position);
};
