#pragma once

#include <cstdint>
#include <vector>

#include "../Instruction.hh"

class AddInstr : public Instruction {
public:
    AddInstr(const std::vector<uint8_t> &content, int position);

    bool execute(Cpu &cpu, bool printing) override;
};
