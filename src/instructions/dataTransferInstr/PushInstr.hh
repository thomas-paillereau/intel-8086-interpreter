#pragma once

#include <cstdint>
#include <vector>

#include "../Instruction.hh"

class PushInstr : public Instruction {
public:
    PushInstr(const std::vector<uint8_t> &content, int position);
};
