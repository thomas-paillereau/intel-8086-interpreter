#pragma once

#include "instructions/Instruction.hh"

class MulInstr : public Instruction {
public:
    MulInstr(const std::vector<uint8_t> &content, int position);

    bool execute(Cpu &cpu, bool &halt, bool printing) override;
};
