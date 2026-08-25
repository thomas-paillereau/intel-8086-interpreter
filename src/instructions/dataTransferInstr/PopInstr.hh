#pragma once

#include <cstdint>
#include <vector>

#include "../Instruction.hh"

class PopInstr : public Instruction {
public:
    PopInstr(const std::vector<uint8_t> &content, int position);

    bool execute(Cpu &cpu, bool &halt, bool printing) override;
};
