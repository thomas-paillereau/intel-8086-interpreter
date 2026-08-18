#pragma once

#include <cstdint>
#include <vector>

#include "Instruction.hh"

class AddInstr : Instruction {
public:
    AddInstr(int position, std::vector<uint8_t> &content);

    std::string toString() override;

private:
    int type_;

    bool d_;
    bool s_;
    bool w_;
    int mod_;
    int reg_;
    int rnm_;
    uint8_t data_;
    uint8_t data2_;
};
