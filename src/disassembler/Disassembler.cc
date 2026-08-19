#include "Disassembler.hh"

#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>

#include "cstdio"

#include "instructions/instruction-header.hh"
#include "utils/Utils.hh"

Disassembler::Disassembler(const std::vector<uint8_t> &content, int content_size, int header_size)
    : content_(content)
      , header_size_(header_size)
      , content_size_(content_size) {
}

void Disassembler::disassemble() {
    int pos = header_size_;
    while (pos < header_size_ + content_size_) {
        auto instruction = disassembleInstruction(pos);
        printf("%04x: %-14s", pos - header_size_, getStringFromBytes(pos, instruction->getSize()).c_str());
        if (pos + instruction->getSize() >= header_size_ + content_size_)
            std::cout << "(undefined)" << std::endl;
        else
            instruction->print();
        pos += instruction->getSize();
    }
}

std::string Disassembler::getStringFromBytes(int position, int size) const {
    if (position + size > header_size_ + content_size_)
        return "00";
    std::stringstream ss;
    for (int i = 0; i < size; ++i) {
        ss << std::hex
                << std::setw(2)
                << std::setfill('0')
                << static_cast<int>(content_[position + i]);
    }
    return ss.str();
}

std::unique_ptr<Instruction> Disassembler::disassembleInstruction(int position) {
    const uint8_t curr1 = content_.at(position);

    /// DATA TRANSFER
    // MOV
    if ((0b10001000 <= curr1 && curr1 <= 0b10001011)
        || (0b11000110 <= curr1 && curr1 <= 0b11000111)
        || (0b10110000 <= curr1 && curr1 <= 0b10111111)
        || (0b10100000 <= curr1 && curr1 <= 0b10100001)
        || (0b10100010 <= curr1 && curr1 <= 0b10100011)
        || (curr1 == 0b10001110)
        || (curr1 == 0b10001100)) {
        return std::make_unique<MovInstr>(content_, position);
    }
    // PUSH
    if ((0b01010000 <= curr1 && curr1 <= 0b01010111)
        || (0b00000110 <= curr1 && curr1 <= 0b00011110)
        || (curr1 == 0b11111111
            && Utils::getIntervalNumFromByte(content_.at(position + 1), 5, 3) == 0b110)) {
        return std::make_unique<PushInstr>(content_, position);
    }
    // POP
    if ((0b01011000 <= curr1 && curr1 <= 0b01011111)
        || (curr1 == 0b10001111 && Utils::getIntervalNumFromByte(content_.at(position + 1), 5, 3) == 0b000)
        || (0b00000111 <= curr1 && curr1 <= 0b00011111)) {
        return std::make_unique<PopInstr>(content_, position);
    }

    // XCHG
    // IN
    // OUT
    // XLAT
    // LEA
    if (0b10001101 == curr1) {
        return std::make_unique<LeaInstr>(content_, position);
    }
    // LDS
    // LES
    // LAHF
    // SAHF
    // PUSHF
    // POPF

    /// ARITHMETIC
    // ADD
    if ((curr1 <= 0b00000011)
        || (0b10000000 <= curr1 && curr1 <= 0b10000011
            && Utils::getIntervalNumFromByte(content_.at(position + 1), 5, 3) == 0b000)
        || (0b00000100 <= curr1 && curr1 <= 0b00000101)) {
        return std::make_unique<AddInstr>(content_, position);
    }
    // ADC
    // INC
    // AAA
    // BAA
    // SUB
    // SSB
    // DEC
    // NEG
    // CMP
    if ((0b00111000 <= curr1 && curr1 <= 0b00111011)
        || (0b10000000 <= curr1 && curr1 <= 0b10000011
            && Utils::getIntervalNumFromByte(content_.at(position + 1), 5, 3) == 0b111)
        || (0b00111100 <= curr1 && curr1 <= 0b00111101)) {
        return std::make_unique<CmpInstr>(content_, position);
    }
    // AAS
    // DAS
    // MUL
    // IMUL
    // AAM
    // DIV
    // IDIV
    // AAD
    // CBW
    // CWD

    /// LOGIC
    // NOT
    // SHL/SAL
    // SHR
    // SAR
    // ROL
    // ROR
    // RCL
    // RCR
    // AND
    // TEST
    // OR
    // XOR
    if ((0b00110000 <= curr1 && curr1 <= 0b00110011)
        || (0b10000000 <= curr1 && curr1 <= 0b10000001
            && Utils::getIntervalNumFromByte(content_.at(position + 1), 5, 3) == 0b110)
        || (0b00110100 <= curr1 && curr1 <= 0b00110101)) {
        return std::make_unique<XorInstr>(content_, position);
    }

    /// STRING MANIPULATION
    // REP
    // MOVS
    // CMPS
    // SCAS
    // LODS
    // STOS

    /// CONTROL TRANSFER
    // CALL
    // JMP
    // RET
    // JE/JZ
    // JL/JNGE
    // JLE/JNG
    // JB/JNAE
    // JBE/JNA
    // JP/JPE
    // JO
    // JS
    // JNE/JNZ
    // JNL/JGE
    // JNLE/JG
    // JNB/JAE
    // JNBE/JA
    // JNP/JPO
    // JNO
    // JNS
    // LOOP
    // LOOPZ/LOOPE
    // LOOPNZ/LOOPNE
    // JCXZ
    // INT
    if (curr1 == 0b11001101 || curr1 == 0b11001100) {
        return std::make_unique<IntInstr>(content_, position);
    }
    // INTO
    // IRET

    /// PROCESSOR CONTROL
    // CLC
    // CMC
    // STC
    // CLD
    // STD
    // CLI
    // STI
    // HLT
    // WAIT
    // ESC
    // LOCK

    // UNDEFINED
    return std::make_unique<Instruction>();
}
