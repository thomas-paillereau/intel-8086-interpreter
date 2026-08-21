#pragma once
#include "instructions/Instruction.hh"

class JlejngInstr : public Instruction {
public:
    JlejngInstr(const std::vector<uint8_t> &content, int position);
};
