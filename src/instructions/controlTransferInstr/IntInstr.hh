#pragma once

#include <cstdint>
#include <vector>

#include "../Instruction.hh"

class IntInstr : public Instruction {
public:
    IntInstr(const std::vector<uint8_t> &content, int position);

    bool execute(Cpu &cpu, bool printing) override;
};
