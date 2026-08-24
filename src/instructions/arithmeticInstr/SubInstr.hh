#pragma once

#include <vector>

#include "instructions/Instruction.hh"

class SubInstr : public Instruction {
public:
    SubInstr(const std::vector<uint8_t> &content, int position);

    bool execute(Cpu &cpu, bool printing) override;
};
