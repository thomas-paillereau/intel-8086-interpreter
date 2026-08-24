#pragma once

#include <vector>

#include "instructions/Instruction.hh"

class JneJnzInstr : public Instruction {
public:
    JneJnzInstr(const std::vector<uint8_t> &content, int position);

    bool execute(Cpu &cpu, bool printing) override;
};
