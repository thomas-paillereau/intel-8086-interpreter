#include "Instruction.hh"

#include <iomanip>
#include <iostream>
#include <ostream>
#include <sstream>

#include "disassembler/Disassembler.hh"
#include "exceptions/NonExistentRegisterException.hh"
#include "exceptions/NonImplementedInstructionException.hh"
#include "exceptions/UnknownInstructionException.hh"

/// -----------------------------------------------------------------------------------------------------------------///
/// Utils

std::string getRegisterString(int reg, bool w, bool only_2_bits) {
    if (only_2_bits) {
        switch (reg) {
            case 0b000:
                return "es";
            case 0b001:
                return "cs";
            case 0b010:
                return "ss";
            case 0b011:
                return "ds";
            case 0b100:
            default:
                throw NonExistentRegisterException(
                    ("No Segment was found for the int: " + std::to_string(reg)).c_str());
        }
    }

    switch (reg) {
        case 0b000:
            return w ? "ax" : "al";
        case 0b001:
            return w ? "cx" : "cl";
        case 0b010:
            return w ? "dx" : "dl";
        case 0b011:
            return w ? "bx" : "bl";
        case 0b100:
            return w ? "sp" : "ah";
        case 0b101:
            return w ? "bp" : "ch";
        case 0b110:
            return w ? "si" : "dh";
        case 0b111:
            return w ? "di" : "bh";
        default:
            throw NonExistentRegisterException(("No register was found for the int: " + std::to_string(reg)).c_str());
    }
}

uint16_t uint8ToUint16(uint8_t low, uint8_t high, bool w) {
    uint16_t value = low;
    if (w)
        value |= static_cast<uint16_t>(high) << 8;
    return value;
}

std::string Uint16ToHexString(uint16_t n, int zero_padding) {
    std::stringstream ss;
    ss << std::hex
            << std::setw(zero_padding)
            << std::setfill('0')
            << n;
    return ss.str();
}

/// -----------------------------------------------------------------------------------------------------------------///
/// Function to add displacement and immediate bytes for the instructions

void Instruction::addInfoBytes(const std::vector<uint8_t> &content, int position) {
    if ((mod_ == 0b00 && rm_ == 0b110) || mod_ == 0b10) {
        disp_low_ = content.at(position + size_);
        disp_high_ = content.at(position + size_ + 1);
        size_disp_ = 2;
        size_ += 2;
    } else if (mod_ == 0b01) {
        disp_low_ = content.at(position + size_);
        size_disp_ = 1;
        size_ += 1;
    }

    if (info_byte_type_ == DATA) {
        imm_low_ = content.at(position + size_);
        size_++;
        if (!s_ && w_) {
            imm_high_ = content.at(position + size_);
            size_++;
        }
    } else if (info_byte_type_ == ADDR_HL || info_byte_type_ == DISP_HL
               || info_byte_type_ == OFFSET_HL || info_byte_type_ == DATA_HL) {
        imm_low_ = content.at(position + size_);
        imm_high_ = content.at(position + size_ + 1);
        size_ += 2;
    } else if (info_byte_type_ == PORT || info_byte_type_ == DISP || info_byte_type_ == TYPE) {
        imm_low_ = content.at(position + size_);
        size_++;
    }
}

/// -----------------------------------------------------------------------------------------------------------------///
/// Decoding the opcode into assembly code

// Modifying the zero padding length depending on the opcode
void Instruction::setZeroPadding() {
    if (reg_ == -1 && !w_) {
        byte_ = true;
        padding_ = 0;
    } else if (!s_ && w_)
        padding_ = 4;
    else
        padding_ = 2;
}

//Main function of string generation
std::string Instruction::toString() const {
    if (name_ == "(undefined)")
        return name_;

    std::string res;
    res += name_;
    if (name_ == "in" || name_ == "out" || (name_ == "xchg" && effect_ == 1)) {
        res += " " + decodeImplicit();
    } else if (mod_ != -1 && rm_ != -1) {
        res += " " + decodeModRm();
    } else if (reg_ != -1 && info_byte_type_ == DATA && mod_ == -1 && rm_ == -1) {
        res += " " + decodeRegImm();
    } else if (reg_ != -1 && info_byte_type_ == NONE) {
        res += " " + getRegisterString(reg_, w_, two_bits_reg_);
    } else if (info_byte_type_ == DATA) {
        res += " " + decodeAccImm();
    } else if (info_byte_type_ == ADDR_HL) {
        res += " " + decodeDirectAddr();
    } else if (info_byte_type_ == DISP || info_byte_type_ == DISP_HL) {
        res += " " + decodeRelative();
    } else if (info_byte_type_ != NONE) {
        res += " " + decodeOnlyImm();
    }
    return res;
}

// Implicit
std::string Instruction::decodeImplicit() const {
    std::stringstream ss;
    if (name_ == "in" || name_ == "out") {
        if (effect_ == 0) {
            ss << "ax, " << std::hex << static_cast<int>(imm_low_);
        } else {
            ss << "al, dx";
        }
    } else if (name_ == "xchg") {
        ss << getRegisterString(reg_, w_, false) + ", ax";
    }
    return ss.str();
}

// Decode immediate operand of mod r/m
std::string decodeImmediate(uint8_t low, uint8_t high, bool s, bool w, int padding) {
    std::stringstream ss;
    if (s && w) {
        int16_t value = static_cast<int8_t>(low);
        if (value < 0)
            ss << "-" << std::hex << -static_cast<int>(value);
        else
            ss << std::hex << static_cast<int>(value);
        return ss.str();
    }
    uint16_t value = uint8ToUint16(low, high, w);
    return Uint16ToHexString(value, padding);
}

// Decode direct memory operand of mod r/m
std::string decodeDirectMemory(uint8_t imm_low, uint8_t imm_high) {
    uint16_t address = uint8ToUint16(imm_low, imm_high, true);
    return "[" + Uint16ToHexString(address, 4) + "]";
}

// Decode memory operand of mod r/m
std::string decodeMemoryOperand(const std::string &base, int mod, uint8_t disp_low, uint8_t disp_high) {
    std::stringstream ss;
    if (mod == 0b01) {
        int displacement = static_cast<int8_t>(disp_low);
        if (displacement >= 0)
            ss << "+" << std::hex << displacement;
        else
            ss << "-" << std::hex << -displacement;
    } else if (mod == 0b10) {
        int displacement = static_cast<int16_t>(
            static_cast<uint16_t>(disp_low) |
            (static_cast<uint16_t>(disp_high) << 8)
        );
        if (displacement > 0)
            ss << "+" << std::hex << displacement;
        else if (displacement < 0)
            ss << "-" << std::hex << -displacement;
    }
    return "[" + base + ss.str() + "]";
}

// Decode Mod R/M
std::string Instruction::decodeModRm() const {
    std::string byteString = reg_ == -1 && !w_ ? "byte " : "";

    std::string regValue;
    if (reg_ != -1)
        regValue = getRegisterString(reg_, w_, two_bits_reg_);
    else if (v_used_)
        regValue = v_ ? "cl" : "1";
    else if (info_byte_type_ != NONE)
        regValue = decodeImmediate(imm_low_, imm_high_, s_, w_, padding_);

    if (mod_ == 0b11) {
        if (regValue.empty())
            return getRegisterString(rm_, w_, two_bits_reg_);
        if (d_)
            return regValue + ", " + getRegisterString(rm_, w_, two_bits_reg_);
        return getRegisterString(rm_, w_, two_bits_reg_) + ", " + regValue;
    }

    std::string operand;
    if (rm_ == 0b000)
        operand = "bx+si";
    else if (rm_ == 0b001)
        operand = "bx+di";
    else if (rm_ == 0b010)
        operand = "bp+si";
    else if (rm_ == 0b011)
        operand = "bp+di";
    else if (rm_ == 0b100)
        operand = "si";
    else if (rm_ == 0b101)
        operand = "di";
    else if (rm_ == 0b110) {
        if (mod_ == 0b00) {
            if (regValue.empty())
                return decodeDirectMemory(disp_low_, disp_high_);
            if (d_)
                return regValue + ", " + decodeDirectMemory(disp_low_, disp_high_);
            return decodeDirectMemory(disp_low_, disp_high_) + ", " + regValue;
        }
        operand = "bp";
    } else if (rm_ == 0b111)
        operand = "bx";
    std::string rmValue = decodeMemoryOperand(operand, mod_, disp_low_, disp_high_);

    if (regValue.empty())
        return byteString + rmValue;
    if (d_)
        return byteString + regValue + ", " + rmValue;
    return byteString + rmValue + ", " + regValue;
}

//Decode REG Immediate
std::string Instruction::decodeRegImm() const {
    std::string regString = getRegisterString(reg_, w_, two_bits_reg_);
    uint16_t rightValue = uint8ToUint16(imm_low_, imm_high_, w_);

    std::stringstream ss;
    ss << regString << ", " << Uint16ToHexString(rightValue, w_ ? 4 : 2);
    return ss.str();
}

// Decode Acc Immediate
std::string Instruction::decodeAccImm() const {
    std::string accString = w_ ? "ax" : "al";
    uint16_t rightValue = uint8ToUint16(imm_low_, imm_high_, w_);

    std::stringstream ss;
    ss << accString << ", " << Uint16ToHexString(rightValue, padding_);
    return ss.str();
}

// Decode Direct Addr
std::string Instruction::decodeDirectAddr() const {
    uint16_t address = uint8ToUint16(imm_low_, imm_high_, true);
    std::string memory = "[" + Uint16ToHexString(address, 4) + "]";
    std::string reg = getRegisterString(0, w_, two_bits_reg_);

    std::stringstream ss;
    if (d_)
        ss << reg << ", " << memory;
    else
        ss << memory << ", " << reg;
    return ss.str();
}

// Decode Relative Instr
std::string Instruction::decodeRelative() const {
    int16_t displacement;

    if (w_ || info_byte_type_ == DISP_HL) {
        uint16_t value = uint8ToUint16(imm_low_, imm_high_, true);
        displacement = static_cast<int16_t>(value);
    } else {
        displacement = static_cast<int8_t>(imm_low_);
    }

    auto target = static_cast<uint16_t>(position_ + size_ + displacement);
    return Uint16ToHexString(target, 4);
}

// Decode Immediate Instr
std::string Instruction::decodeOnlyImm() const {
    uint16_t value = uint8ToUint16(imm_low_, imm_high_, w_);
    return Uint16ToHexString(value, w_ ? 4 : 2);
}

// Print function
void Instruction::print() const {
    std::cout << toString() << std::endl;
}

/// -----------------------------------------------------------------------------------------------------------------///
/// Main functions of instruction execution (overridable)

bool Instruction::execute([[maybe_unused]] Cpu &cpu) {
    if (name_ == "(undefined)") {
        throw UnknownInstructionException("Execution was stopped, Unknown instruction detected");
    } else {
        throw NonImplementedInstructionException(
            (name_ + " instruction was not implemented for the execution").c_str());
    }
    //return cpu.addToIp(size_);
}

/// -----------------------------------------------------------------------------------------------------------------///
/// Functions to search for values for execution

// Setting the val1 depending on reg, w_, and the 3 or 2 bit possibility
void Instruction::setRegisterVal(bool is_rm) {
    dst_ = is_rm ? rm_ : reg_;
    if (two_bits_reg_)
        type_dst_ = Cpu::SEG;
    else if (w_)
        type_dst_ = Cpu::REG16;
    else
        type_dst_ = Cpu::REG8;
}

// Swaps the execution values
void Instruction::swapValues() {
    uint16_t tmp = dst_;
    Cpu::type tmp_type = type_dst_;

    dst_ = src_;
    type_dst_ = type_src_;

    src_ = tmp;
    type_src_ = tmp_type;
}

// Main function of searching
void Instruction::searchValues(Cpu &cpu) {
    if (name_ == "(undefined)")
        return;

    if (name_ == "in" || name_ == "out" || (name_ == "xchg" && effect_ == 1)) {
        searchImplicit();
    } else if (mod_ != -1 && rm_ != -1) {
        searchModRm(cpu);
    } else if (reg_ != -1 && info_byte_type_ == DATA && mod_ == -1 && rm_ == -1) {
        searchRegImm();
    } else if (reg_ != -1 && info_byte_type_ == NONE) {
        setRegisterVal();
    } else if (info_byte_type_ == DATA) {
        searchAccImm();
    } else if (info_byte_type_ == ADDR_HL) {
        searchDirectAddr();
    } else if (info_byte_type_ == DISP || info_byte_type_ == DISP_HL) {
        searchRelative();
    } else if (info_byte_type_ != NONE) {
        searchOnlyImm();
    }
}

void Instruction::searchImplicit() {
    if (name_ == "in" || name_ == "out") {
        if (effect_ == 0) {
            type_dst_ = Cpu::REG16;
            type_src_ = Cpu::IMM;
            dst_ = static_cast<uint16_t>(Cpu::reg16::AX);
            src_ = imm_low_;
        } else {
            type_dst_ = Cpu::REG8;
            type_src_ = Cpu::REG16;
            dst_ = static_cast<uint16_t>(Cpu::reg8::AL);
            src_ = static_cast<uint16_t>(Cpu::reg16::DX);
        }
    } else if (name_ == "xchg") {
        setRegisterVal();
        type_src_ = Cpu::REG16;
        src_ = static_cast<uint16_t>(Cpu::reg16::AX);
    }
}

void Instruction::searchMemoryOperand(uint16_t base) {
    if (mod_ == 0b01) {
        int displacement = static_cast<int8_t>(disp_low_);
        if (displacement >= 0)
            base += displacement;
        else
            base -= displacement;
    } else if (mod_ == 0b10) {
        int displacement = static_cast<int16_t>(
            static_cast<uint16_t>(disp_low_) |
            (static_cast<uint16_t>(disp_high_) << 8)
        );
        if (displacement > 0)
            base += displacement;
        else if (displacement < 0)
            base -= displacement;
    }
    type_src_ = Cpu::MEM16;
    src_ = base;
}

void Instruction::searchModRm(Cpu &cpu) {
    std::string byteString = reg_ == -1 && !w_ ? "byte " : "";

    if (reg_ != -1)
        setRegisterVal();
    else if (v_used_) {
        type_dst_ = v_ ? Cpu::REG8 : Cpu::IMM;
        dst_ = v_ ? static_cast<uint16_t>(Cpu::reg8::CL) : 1;
    } else if (info_byte_type_ != NONE) {
        //TODO checking sign to do in post
        type_dst_ = Cpu::IMM;
        dst_ = uint8ToUint16(imm_low_, imm_high_, w_);
    }

    if (mod_ == 0b11) {
        swapValues();
        setRegisterVal(true);
        if (d_)
            swapValues();
        return;
    }

    uint16_t operand;
    if (rm_ == 0b000)
        operand = cpu.getReg16(Cpu::BX) + cpu.getReg16(Cpu::SI);
    else if (rm_ == 0b001)
        operand = cpu.getReg16(Cpu::BX) + cpu.getReg16(Cpu::DI);
    else if (rm_ == 0b010)
        operand = cpu.getReg16(Cpu::BP) + cpu.getReg16(Cpu::SI);
    else if (rm_ == 0b011)
        operand = cpu.getReg16(Cpu::BP) + cpu.getReg16(Cpu::DI);
    else if (rm_ == 0b100)
        operand = cpu.getReg16(Cpu::SI);
    else if (rm_ == 0b101)
        operand = cpu.getReg16(Cpu::DI);
    else if (rm_ == 0b110) {
        if (mod_ == 0b00) {
            type_src_ = Cpu::MEM16;
            src_ = uint8ToUint16(imm_low_, imm_high_, true);
            if (!d_ || type_dst_ == Cpu::NONE)
                swapValues();
            return;
        }
        operand = cpu.getReg16(Cpu::BP);
    } else
        operand = cpu.getReg16(Cpu::BX);
    searchMemoryOperand(operand);

    if (!d_ || type_dst_ == Cpu::NONE)
        swapValues();
}

void Instruction::searchRegImm() {
    setRegisterVal();
    type_src_ = Cpu::IMM;
    src_ = uint8ToUint16(imm_low_, imm_high_, w_);
}

void Instruction::searchAccImm() {
    type_dst_ = w_ ? Cpu::type::REG16 : Cpu::type::REG8;
    dst_ = w_ ? static_cast<uint16_t>(Cpu::reg16::AX) : static_cast<uint16_t>(Cpu::reg8::AL);
    type_src_ = Cpu::IMM;
    src_ = uint8ToUint16(imm_low_, imm_high_, w_);
}

void Instruction::searchDirectAddr() {
    reg_ = 0b0;
    setRegisterVal();
    type_src_ = Cpu::IMM;
    src_ = uint8ToUint16(imm_low_, imm_high_, true);
    if (!d_)
        swapValues();
}

void Instruction::searchRelative() {
    int16_t displacement;
    if (w_ || info_byte_type_ == DISP_HL) {
        uint16_t value = uint8ToUint16(imm_low_, imm_high_, true);
        displacement = static_cast<int16_t>(value);
    } else {
        displacement = static_cast<int8_t>(imm_low_);
    }
    type_dst_ = Cpu::IMM;
    dst_ = displacement;
}

void Instruction::searchOnlyImm() {
    type_dst_ = Cpu::IMM;
    dst_ = uint8ToUint16(imm_low_, imm_high_, w_);
}

void Instruction::printAddressOfVals(Cpu &cpu) const {
    if (type_dst_ == Cpu::MEM16) {
        std::cout << " ;[" << std::hex << std::setw(4) << std::setfill('0') << dst_ << std::dec << "]"
                << std::hex << std::setw(4) << std::setfill('0') << cpu.get(type_dst_, dst_);
    } else if (type_src_ == Cpu::MEM16) {
        std::cout << " ;[" << std::hex << std::setw(4) << std::setfill('0') << src_ << std::dec << "]"
                << std::hex << std::setw(4) << std::setfill('0') << cpu.get(type_src_, src_);
    }
    std::cout << std::endl;
}

/// -----------------------------------------------------------------------------------------------------------------///
/// Getters

int Instruction::getSize() const {
    return size_;
}
