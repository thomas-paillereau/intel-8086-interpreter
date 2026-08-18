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

    enum byte_type {
        NONE,
        DATA,
        ADDR_HL,
        PORT,
        DISP_HL,
        OFFSET_HL,
        SEG_HL,
        DISP,
        DATA_HL,
        TYPE,
    };

    byte_type info_byte_type_ = NONE;

    uint8_t info_byte1_ = 0b0;
    uint8_t info_byte2_ = 0b0;

    std::string name_ = "UNDEFINED";
};
