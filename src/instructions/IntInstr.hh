#pragma once

#include <cstdint>
#include <vector>

#include "Instruction.hh"

class IntInstr : public Instruction {
public:
    IntInstr(const std::vector<uint8_t> &content, int position);

    std::string toString() const override;

private:
    int type_;
    
    uint8_t reg_type_;
};
