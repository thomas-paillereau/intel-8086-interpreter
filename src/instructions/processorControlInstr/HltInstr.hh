#pragma once

#include <vector>

#include "instructions/Instruction.hh"

class HltInstr : public Instruction {
public:
    HltInstr(const std::vector<uint8_t> &content, int position);

    bool execute(Cpu &cpu, bool &halt, bool printing) override;
};
