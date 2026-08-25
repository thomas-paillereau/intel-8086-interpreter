#pragma once

#include <vector>

#include "instructions/Instruction.hh"

class JlJngeInstr : public Instruction {
public:
    JlJngeInstr(const std::vector<uint8_t> &content, int position);

    bool execute(Cpu &cpu, bool &halt, bool printing) override;
};
