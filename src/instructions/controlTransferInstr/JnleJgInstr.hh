#pragma once

#include "instructions/Instruction.hh"

class JnleJgInstr : public Instruction {
public:
    JnleJgInstr(const std::vector<uint8_t> &content, int position);

    bool execute(Cpu &cpu, bool &halt, bool printing) override;
};
