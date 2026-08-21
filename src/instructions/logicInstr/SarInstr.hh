#pragma once

#include "instructions/Instruction.hh"

class SarInstr : public Instruction {
public:
    SarInstr(const std::vector<uint8_t> &content, int position);
};
