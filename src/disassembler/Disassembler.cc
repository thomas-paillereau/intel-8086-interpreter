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
        instruction->setZeroPadding();
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
        || (curr1 == 0b11111111
            && Utils::getIntervalNumFromByte(content_.at(position + 1), 5, 3) == 0b110)
        || (0b00000110 == curr1 || 0b00001110 == curr1 || 0b00010110 == curr1 || 0b00011110 == curr1)) {
        return std::make_unique<PushInstr>(content_, position);
    }
    // POP
    if ((0b01011000 <= curr1 && curr1 <= 0b01011111)
        || (curr1 == 0b10001111 && Utils::getIntervalNumFromByte(content_.at(position + 1), 5, 3) == 0b000)
        || (0b00000111 == curr1 || 0b00001111 == curr1 || 0b00010111 == curr1 || 0b00011111 == curr1)) {
        return std::make_unique<PopInstr>(content_, position);
    }

    // XCHG
    // IN
    if (0b11100100 == curr1 || 0b11100101 == curr1
        || 0b11101100 == curr1 || 0b11101101 == curr1) {
        return std::make_unique<InInstr>(content_, position);
    }
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
    if ((0b00101000 <= curr1 && curr1 <= 0b00101011)
        || (0b10000000 <= curr1 && curr1 <= 0b10000011
            && Utils::getIntervalNumFromByte(content_.at(position + 1), 5, 3) == 0b101)
        || (0b0010110 <= curr1 && curr1 <= 0b0010111)) {
        return std::make_unique<SubInstr>(content_, position);
    }
    // SSB
    if ((0b00011000 <= curr1 && curr1 <= 0b00011011)
        || (0b10000000 <= curr1 && curr1 <= 0b10000011
            && Utils::getIntervalNumFromByte(content_.at(position + 1), 5, 3) == 0b011)
        || (0b0001110 <= curr1 && curr1 <= 0b0001111)) {
        return std::make_unique<SbbInstr>(content_, position);
    }
    // DEC
    if (((0b11111110 == curr1 || curr1 == 0b11111111)
         && Utils::getIntervalNumFromByte(content_.at(position + 1), 5, 3) == 0b000)
        || (0b01001000 <= curr1 && curr1 <= 0b01001111)) {
        return std::make_unique<DecInstr>(content_, position);
    }
    // NEG
    if ((curr1 == 0b11110110 || curr1 == 0b11110111)
        && Utils::getIntervalNumFromByte(content_.at(position + 1), 5, 3) == 0b011) {
        return std::make_unique<NegInstr>(content_, position);
    }
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
    if (0b10011000 == curr1) {
        return std::make_unique<CbwInstr>(content_, position);
    }
    // CWD
    if (0b10011001 == curr1) {
        return std::make_unique<CwdInstr>(content_, position);
    }

    /// LOGIC
    // NOT
    // SHL/SAL
    if (0b11010000 <= curr1 && curr1 <= 0b11010011
        && Utils::getIntervalNumFromByte(content_.at(position + 1), 5, 3) == 0b100) {
        return std::make_unique<ShlSalInstr>(content_, position);
    }
    // SHR
    // SAR
    // ROL
    // ROR
    // RCL
    // RCR
    // AND
    if ((0b00100000 <= curr1 && curr1 <= 0b00100011)
        || (0b10000000 <= curr1 && curr1 <= 0b10000001
            && Utils::getIntervalNumFromByte(content_.at(position + 1), 5, 3) == 0b100)
        || (0b00100100 <= curr1 && curr1 <= 0b00100101)) {
        return std::make_unique<AndInstr>(content_, position);
    }
    // TEST
    if ((0b10000100 <= curr1 && curr1 <= 0b10000101)
        || (0b11110110 <= curr1 && curr1 <= 0b11110111
            && Utils::getIntervalNumFromByte(content_.at(position + 1), 5, 3) == 0b000)
        || (0b10101000 <= curr1 && curr1 <= 0b10101001)) {
        return std::make_unique<TestInstr>(content_, position);
    }
    // OR
    if ((0b00001000 <= curr1 && curr1 <= 0b00001011)
        || (0b10000000 <= curr1 && curr1 <= 0b10000001
            && Utils::getIntervalNumFromByte(content_.at(position + 1), 5, 3) == 0b001)
        || (0b00001100 <= curr1 && curr1 <= 0b00001101)) {
        return std::make_unique<OrInstr>(content_, position);
    }
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
    if (0b11101000 == curr1
        || (0b11111111 == curr1
            && Utils::getIntervalNumFromByte(content_.at(position + 1), 5, 3) == 0b010)
        || 0b10011010 == curr1
        || (0b11111111 == curr1
            && Utils::getIntervalNumFromByte(content_.at(position + 1), 5, 3) == 0b011)) {
        return std::make_unique<CallInstr>(content_, position);
    }
    // JMP
    if (0b11101001 == curr1
        || 0b11101011 == curr1
        || (0b11111111 == curr1
            && Utils::getIntervalNumFromByte(content_.at(position + 1), 5, 3) == 0b100)
        || 0b11101010 == curr1
        || (0b11111111 == curr1
            && Utils::getIntervalNumFromByte(content_.at(position + 1), 5, 3) == 0b101)) {
        return std::make_unique<JmpInstr>(content_, position);
    }
    // RET
    if (0b11000011 == curr1
        || 0b11000010 == curr1
        || 0b11001011 == curr1
        || 0b11001010 == curr1) {
        return std::make_unique<RetInstr>(content_, position);
    }
    // JE/JZ
    if (0b01110100 == curr1) {
        return std::make_unique<JeJzInstr>(content_, position);
    }
    // JL/JNGE
    if (0b01111100 == curr1) {
        return std::make_unique<JlJngeInstr>(content_, position);
    }
    // JLE/JNG
    // JB/JNAE
    // JBE/JNA
    // JP/JPE
    // JO
    // JS
    // JNE/JNZ
    if (curr1 == 0b01110101) {
        return std::make_unique<JneJnzInstr>(content_, position);
    }
    // JNL/JGE
    if (curr1 == 0b01111101) {
        return std::make_unique<JnlJgeInstr>(content_, position);
    }
    // JNLE/JG
    // JNB/JAE
    if (curr1 == 0b01110011) {
        return std::make_unique<JnbJnaInstr>(content_, position);
    }
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
    if (curr1 == 0b11110100) {
        return std::make_unique<HltInstr>(content_, position);
    }
    // WAIT
    // ESC
    // LOCK

    // UNDEFINED
    return std::make_unique<Instruction>();
}
