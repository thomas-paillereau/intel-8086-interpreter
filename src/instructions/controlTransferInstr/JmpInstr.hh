#pragma once

#include <vector>

#include "instructions/Instruction.hh"

class JmpInstr : public Instruction {
public:
    JmpInstr(const std::vector<uint8_t> &content, int position);

    bool execute(Cpu &cpu, bool &halt, bool printing) override;
};
