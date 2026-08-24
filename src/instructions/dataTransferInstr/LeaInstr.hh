#pragma once

#include <vector>

#include "instructions/Instruction.hh"

class LeaInstr : public Instruction {
public:
    LeaInstr(const std::vector<uint8_t> &content, int position);

    bool execute(Cpu &cpu, bool printing) override;
};
