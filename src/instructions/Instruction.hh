#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "interpreter/Cpu.hh"
#include "interpreter/Cpu.hh"

class Instruction {
public:
    Instruction() = default;

    /// Disassembler utilities
    void setZeroPadding();

    std::string toString() const;

    void print() const;

    /// Interpreter utilities

    // Search values before execution
    void searchValues(Cpu &cpu);

    // Prints the value of the first address of the line
    void printAddressOfVals(Cpu &cpu) const;

    // Execute the instruction
    virtual bool execute(Cpu &cpu);

    int getSize() const;

protected:
    /// -----------------------------------------------------------------------------------------------------------------///
    /// DISASSEMBLER PRINTING

    // General function to add imm and disp bytes to the instruction
    void addInfoBytes(const std::vector<uint8_t> &content, int position);

    // Implicit
    std::string decodeImplicit() const;

    // Mod + R/M
    std::string decodeModRm() const;

    // Reg
    std::string decodeRegImm() const;

    // Data
    std::string decodeAccImm() const;

    // Addr
    std::string decodeDirectAddr() const;

    std::string decodeRelative() const;

    // Info byte present (PORT, OFFSET, SEG, DISP, TYPE)
    std::string decodeOnlyImm() const;

    /// -----------------------------------------------------------------------------------------------------------------///
    /// INTERPRETER EXECUTION

    // Setting the val1 depending on reg, w_, and the 3 or 2 bit possibility
    void setRegisterVal(bool is_rm = false);

    // Swapping the 2 execution values
    void swapValues();

    // Implicit
    void searchImplicit();

    // Mod + R/M utility (for memory operand)
    void searchMemoryOperand(uint16_t base);

    // Mod + R/M
    void searchModRm(Cpu &cpu);

    // Reg
    void searchRegImm();

    // Data
    void searchAccImm();

    // Addr
    void searchDirectAddr();

    void searchRelative();

    // Info byte present (PORT, OFFSET, SEG, DISP, TYPE)
    void searchOnlyImm();

    /// -----------------------------------------------------------------------------------------------------------------///
    /// ATTRIBUTES

    // Basic instruction args
    std::string name_ = "(undefined)";
    int size_ = 1;
    int position_ = 0;

    // Which type of the instruction it is
    int effect_ = 0;

    // One bit opcode flags
    bool w_ = false;
    bool d_ = false;
    bool s_ = false;
    bool z_ = false;
    bool v_ = false;
    bool v_used_ = false;

    // Multiple bit opcode flags (2 or 3)
    int mod_ = -1;
    int reg_ = -1;
    int rm_ = -1;

    bool two_bits_reg_ = false;

    // 1 byte opcode flags
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

    // Value to store the "byte" state
    bool byte_ = false;

    // Printing utilities
    int padding_ = -1;

    // Execution utilities
    Cpu::type type_dst_ = Cpu::type::NONE;
    uint16_t dst_ = 0b0000;

    Cpu::type type_src_ = Cpu::type::NONE;
    uint16_t src_ = 0b0000;
};
