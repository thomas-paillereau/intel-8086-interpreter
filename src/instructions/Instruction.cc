#include "Instruction.hh"

#include <iomanip>
#include <iostream>
#include <ostream>
#include <sstream>

/// -----------------------------------------------------------------------------------------------------------------///
/// Main To String function

std::string Instruction::toString() const {
    if (name_ == "UNDEFINED")
        return name_;

    std::string res;
    res += name_;
    if (mod_ != -1 && rm_ != -1) {
        res += " " + decodeModRm();
    } else if (reg_ != -1 && info_byte_type_ == DATA && mod_ == -1 && rm_ == -1) {
        res += " " + decodeRegImm();
    } else if (info_byte_type_ == DATA) {
        res += " " + decodeAccImm();
    } else if (info_byte_type_ == ADDR_HL) {
        res += " " + decodeDirectAddr();
    } else if (info_byte_type_ == DISP) {
        res += " " + decodeRelative();
    } else if (info_byte_type_ != NONE) {
        res += " " + decodeOnlyImm();
    }
    return res;
}

/// -----------------------------------------------------------------------------------------------------------------///
/// Utils

std::string getRegisterString(int reg, bool w) {
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
            return "Error"; // TODO make error
    }
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
/// Decode Mod R/M

std::string decodeDirectMemory(uint8_t info_byte1, uint8_t info_byte2) {
    uint16_t address = static_cast<uint16_t>(info_byte1) | (static_cast<uint16_t>(info_byte2) << 8);
    return "[" + Uint16ToHexString(address, 4) + "]";
}

std::string decodeMemoryOperand(const std::string &base, int mod, uint8_t info_byte1, uint8_t info_byte2) {
    std::stringstream ss;
    if (mod == 0b01) {
        int8_t displacement = static_cast<int8_t>(info_byte1);
        if (displacement >= 0)
            ss << "+" << std::hex << static_cast<int>(displacement);
        else
            ss << std::hex << static_cast<int>(displacement);
    } else if (mod == 0b10) {
        int16_t displacement =
                static_cast<int16_t>(
                    static_cast<uint16_t>(info_byte1) |
                    (static_cast<uint16_t>(info_byte2) << 8)
                );
        if (displacement >= 0)
            ss << "+" << std::hex << displacement;
        else
            ss << std::hex << displacement;
    }
    return "[" + base + ss.str() + "]";
}

std::string Instruction::decodeModRm() const {
    if (mod_ == 0b11) {
        return getRegisterString(rm_, w_);
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
        if (mod_ == 0b000)
            return decodeDirectMemory(info_byte1_, info_byte2_);
        operand = "bp";
    } else if (rm_ == 0b111)
        operand = "bx";
    std::string rmValue = decodeMemoryOperand(operand, mod_, info_byte1_, info_byte2_);
    std::string regValue = getRegisterString(reg_, w_);
    if (d_)
        return regValue + ", " + rmValue;
    return rmValue + ", " + regValue;
}

/// -----------------------------------------------------------------------------------------------------------------///
/// Decode REG Immediate

std::string Instruction::decodeRegImm() const {
    std::string regString = getRegisterString(reg_, w_);
    uint16_t rightValue = info_byte1_;
    if (w_)
        rightValue |= static_cast<uint16_t>(info_byte2_) << 8;

    std::stringstream ss;
    ss << regString << ", " << Uint16ToHexString(rightValue, w_ ? 4 : 2);
    return ss.str();
}

/// -----------------------------------------------------------------------------------------------------------------///
/// Decode Acc Immediate

std::string Instruction::decodeAccImm() const {
    std::string accString = w_ ? "ax" : "al";
    uint16_t rightValue = info_byte1_;
    if (w_)
        rightValue |= static_cast<uint16_t>(info_byte2_) << 8;

    std::stringstream ss;
    ss << accString << ", " << Uint16ToHexString(rightValue, w_ ? 4 : 2);
    return ss.str();
}

/// -----------------------------------------------------------------------------------------------------------------///
/// Decode Direct Addr

std::string Instruction::decodeDirectAddr() const {
    uint16_t address = static_cast<uint16_t>(info_byte1_) | (static_cast<uint16_t>(info_byte2_) << 8);
    std::string memory = "[" + Uint16ToHexString(address, 4) + "]";
    std::string reg = getRegisterString(0, w_);

    std::stringstream ss;
    if (d_)
        ss << reg << ", " << memory;
    else
        ss << memory << ", " << reg;
    return ss.str();
}

/// -----------------------------------------------------------------------------------------------------------------///
/// Decode Relative Instr

std::string Instruction::decodeRelative() const {
    int16_t displacement;

    if (w_) {
        uint16_t value = static_cast<uint16_t>(info_byte1_) | (static_cast<uint16_t>(info_byte2_) << 8);
        displacement = static_cast<int16_t>(value);
    } else {
        displacement = static_cast<int8_t>(info_byte1_);
    }

    auto target = static_cast<uint16_t>(position_ + size_ + displacement);
    return Uint16ToHexString(target, 4);
}

/// -----------------------------------------------------------------------------------------------------------------///
/// Decode Immediate Instr

std::string Instruction::decodeOnlyImm() const {
    uint16_t value = info_byte1_;
    if (w_)
        value |= static_cast<uint16_t>(info_byte2_) << 8;
    return Uint16ToHexString(value, w_ ? 4 : 2);
}

/// -----------------------------------------------------------------------------------------------------------------///
/// Print functino

void Instruction::print() const {
    std::cout << toString() << std::endl;
}

/// -----------------------------------------------------------------------------------------------------------------///
/// Getters

int Instruction::getSize() const {
    return size_;
}
