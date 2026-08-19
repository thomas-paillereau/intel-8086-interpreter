#pragma once

#include <vector>

#include "instructions/Instruction.hh"

class AndInstr : public Instruction {
public:
    AndInstr(const std::vector<uint8_t> &content, int position);
};
