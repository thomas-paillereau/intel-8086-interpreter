#pragma once

#include "instructions/Instruction.hh"

class XchgInstr : public Instruction {
public:
    XchgInstr(const std::vector<uint8_t> &content, int position);
};
