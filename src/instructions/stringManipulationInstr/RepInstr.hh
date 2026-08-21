#pragma once

#include "instructions/Instruction.hh"

class RepInstr : public Instruction {
public:
    RepInstr(const std::vector<uint8_t> &content, int position);
};
