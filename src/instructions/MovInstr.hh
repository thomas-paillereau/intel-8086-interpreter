#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "Instruction.hh"

class MovInstr : public Instruction {
public:
    MovInstr(const std::vector<uint8_t> &content, int position);

    std::string toString() const override;

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
