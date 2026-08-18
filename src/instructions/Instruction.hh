#pragma once
#include <cstdint>
#include <string>

class Instruction {
public:
    Instruction() = default;

    std::string toString() const;

    void print() const;

    int getSize() const;

    // TODO virtual void exec();

protected:
    int size_ = 1;

    int effect_ = 0;

    bool w_ = false;
    bool d_ = false;
    bool s_ = false;

    int mod_ = -1;
    int reg_ = -1;
    int rm_ = -1;

    uint8_t data_ = 0b0;
    uint8_t data2_ = 0b0;
    uint8_t addr_low_ = 0b0;
    uint8_t addr_high_ = 0b0;
    uint8_t type_ = 0b0;

    bool data_used_ = false;
    bool addr_used_ = false;
    bool type_used_ = false;

    std::string name_ = "UNDEFINED";
};
