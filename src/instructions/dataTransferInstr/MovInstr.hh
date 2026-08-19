#pragma once

#include <cstdint>
#include <vector>

#include "../Instruction.hh"

class MovInstr : public Instruction {
public:
    MovInstr(const std::vector<uint8_t> &content, int position);
};
