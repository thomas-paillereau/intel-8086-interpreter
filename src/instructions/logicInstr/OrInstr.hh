#pragma once

#include <vector>

#include "instructions/Instruction.hh"


class OrInstr : public Instruction {
public:
    OrInstr(const std::vector<uint8_t> &content, int position);

    bool execute(Cpu &cpu, bool &halt, bool printing) override;
};
