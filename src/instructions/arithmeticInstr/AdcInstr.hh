#pragma once

#include "instructions/Instruction.hh"

class AdcInstr : public Instruction {
public:
    AdcInstr(const std::vector<uint8_t> &content, int position);
};
