#pragma once

#include <cstdint>
#include <vector>

#include "Instruction.hh"

class AddInstr : public Instruction {
public:
    AddInstr(const std::vector<uint8_t> &content, int position);

    std::string toString() const override;

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
