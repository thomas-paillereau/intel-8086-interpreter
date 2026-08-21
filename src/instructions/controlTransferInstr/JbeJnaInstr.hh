#pragma once

#include "instructions/Instruction.hh"

class JbeJnaInstr : public Instruction {
public:
    JbeJnaInstr(const std::vector<uint8_t> &content, int position);
};
