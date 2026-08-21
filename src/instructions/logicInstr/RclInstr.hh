#pragma once

#include "instructions/Instruction.hh"

class RclInstr : public Instruction {
public:
    RclInstr(const std::vector<uint8_t> &content, int position);
};
