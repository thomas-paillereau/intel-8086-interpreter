#pragma once

#include "instructions/Instruction.hh"

class CbwInstr : public Instruction {
public:
    CbwInstr(const std::vector<uint8_t> &content, int position);

    bool execute(Cpu &cpu, bool &halt, bool printing) override;
};
