#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "interpreter/Cpu.hh"

class Instruction {
public:
    Instruction() = default;

    /// Disassembler utilities
    void setZeroPadding();

    std::string toString() const;

    void print() const;

    /// Interpreter utilities

    virtual void Exec(Cpu &cpu);

    int getSize() const;

protected:
    /// General function to add imm and disp bytes to the instruction
    void addInfoBytes(const std::vector<uint8_t> &content, int position);

    /// Implicit
    std::string decodeImplicit() const;

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

    /// Basic instruction args
    std::string name_ = "(undefined)";
    int size_ = 1;
    int position_ = 0;

    /// Which type of the instruction it is
    int effect_ = 0;

    /// One bit opcode flags
    bool w_ = false;
    bool d_ = false;
    bool s_ = false;
    bool z_ = false;
    bool v_ = false;
    bool v_used_ = false;

    /// Multiple bit opcode flags (2 or 3)
    int mod_ = -1;
    int reg_ = -1;
    int rm_ = -1;

    bool two_bits_reg_ = false;

    /// 1 byte opcode flags
    enum byte_type {
        NONE,
        DATA,
        DATA_HL,
        ADDR_HL,
        PORT,
        DISP,
        DISP_HL,
        OFFSET_HL,
        TYPE,
    };

    byte_type info_byte_type_ = NONE;

    uint8_t imm_low_ = 0b0000;
    uint8_t imm_high_ = 0b0000;

    uint8_t disp_low_ = 0b0000;
    uint8_t disp_high_ = 0b0000;
    int size_disp_ = 0;

    /// Printing utilities
    int padding_ = -1;
};
