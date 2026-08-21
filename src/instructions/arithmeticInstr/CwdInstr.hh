#pragma once

#include "instructions/Instruction.hh"

class CwdInstr : public Instruction {
public:
    CwdInstr(const std::vector<uint8_t> &content, int position);
};
