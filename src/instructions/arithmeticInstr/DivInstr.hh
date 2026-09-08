#pragma once

#include "instructions/Instruction.hh"

class DivInstr : public Instruction {
public:
    DivInstr(const std::vector<uint8_t> &content, int position);

    bool execute(Cpu &cpu, bool &halt, bool printing) override;
};
