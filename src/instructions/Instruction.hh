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
    /// Mod + R/M
    std::string decodeModRm() const;

    /// Reg
    std::string decodeRegImm() const;

    /// Data
    std::string decodeAccImm() const;

    /// Addr
    std::string decodeDirectAddr() const;

    std::string decodeRelative() const;

    /// Info byte present (PORT, OFFSET, SEG, DISP, TYPE)
    std::string decodeOnlyImm() const;

    std::string name_ = "(undefined)";
    int size_ = 1;
    int position_ = 0;

    int effect_ = 0;

    bool w_ = false;
    bool d_ = false;
    bool s_ = false;
    bool v_ = false;
    bool v_used_ = false;

    int mod_ = -1;
    int reg_ = -1;
    int rm_ = -1;

    bool two_bits_reg_ = false;

    enum byte_type {
        NONE,
        DATA,
        ADDR_HL,
        PORT,
        DISP_HL,
        OFFSET_HL,
        DISP,
        DATA_HL,
        TYPE,
    };

    byte_type info_byte_type_ = NONE;

    uint8_t imm_low_ = 0b0000;
    uint8_t imm_high_ = 0b0000;

    uint8_t disp_low_ = 0b0000;
    uint8_t disp_high_ = 0b0000;
    int size_disp_ = 0;
};
