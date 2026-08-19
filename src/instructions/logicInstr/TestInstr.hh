#pragma once

#include <vector>

#include "instructions/Instruction.hh"

class TestInstr : public Instruction {
public:
    TestInstr(const std::vector<uint8_t> &content, int position);
};
