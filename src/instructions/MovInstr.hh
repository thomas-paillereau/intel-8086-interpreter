#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "Instruction.hh"

class MovInstr : Instruction {
public:
    MovInstr(int position, std::vector<uint8_t> &content);

    std::string toString() override;

private:
    int type_;

    bool d_;
    bool w_;
    int mod_;
    int reg_;
    int rnm_;
    uint8_t data_;
    uint8_t data2_;
    uint8_t addr_low_;
    uint8_t addr_high_;
};
