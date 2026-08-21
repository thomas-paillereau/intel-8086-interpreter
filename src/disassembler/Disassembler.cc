#include "Disassembler.hh"

#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>

#include "cstdio"

#include "instructions/instruction-header.hh"
#include "utils/Utils.hh"

int Disassembler::header_size_ = 0;
int Disassembler::content_size_ = 0;

void Disassembler::init(int contentsize, int header_size) {
    header_size_ = header_size;
    content_size_ = contentsize;
}

int Disassembler::getHeaderSize() {
    return header_size_;
}

void Disassembler::disassemble(const std::vector<uint8_t> &content) {
    int pos = header_size_;
    while (pos < header_size_ + content_size_) {
        auto instruction = disassembleInstruction(content, pos);
        instruction->setZeroPadding();
        printf("%04x: %-14s", pos - header_size_, getStringFromBytes(content, pos, instruction->getSize()).c_str());
        if (pos + instruction->getSize() > header_size_ + content_size_)
            std::cout << "(undefined)" << std::endl;
        else
            instruction->print();
        pos += instruction->getSize();
    }
}

std::string Disassembler::getStringFromBytes(const std::vector<uint8_t> &content, int position, int size) {
    if (position + size > header_size_ + content_size_)
        return "00";
    std::stringstream ss;
    for (int i = 0; i < size; ++i) {
        ss << std::hex
                << std::setw(2)
                << std::setfill('0')
                << static_cast<int>(content[position + i]);
    }
    return ss.str();
}

std::unique_ptr<Instruction> Disassembler::disassembleInstruction(const std::vector<uint8_t> &content, int position) {
    const uint8_t curr1 = content.at(position);

    /// DATA TRANSFER
    // MOV
    if ((0b10001000 <= curr1 && curr1 <= 0b10001011)
        || (0b11000110 <= curr1 && curr1 <= 0b11000111)
        || (0b10110000 <= curr1 && curr1 <= 0b10111111)
        || (0b10100000 <= curr1 && curr1 <= 0b10100001)
        || (0b10100010 <= curr1 && curr1 <= 0b10100011)
        || (curr1 == 0b10001110)
        || (curr1 == 0b10001100)) {
        return std::make_unique<MovInstr>(content, position);
    }
    // PUSH
    if ((0b01010000 <= curr1 && curr1 <= 0b01010111)
        || (curr1 == 0b11111111
            && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b110)
        || (0b00000110 == curr1 || 0b00001110 == curr1 || 0b00010110 == curr1 || 0b00011110 == curr1)) {
        return std::make_unique<PushInstr>(content, position);
    }
    // POP
    if ((0b01011000 <= curr1 && curr1 <= 0b01011111)
        || (curr1 == 0b10001111 && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b000)
        || (0b00000111 == curr1 || 0b00001111 == curr1 || 0b00010111 == curr1 || 0b00011111 == curr1)) {
        return std::make_unique<PopInstr>(content, position);
    }

    // XCHG
    if (0b10000110 == curr1 || 0b10000111 == curr1
        || (0b10010000 <= curr1 && curr1 <= 0b10010111)) {
        return std::make_unique<XchgInstr>(content, position);
    }
    // IN
    if (0b11100100 == curr1 || 0b11100101 == curr1
        || 0b11101100 == curr1 || 0b11101101 == curr1) {
        return std::make_unique<InInstr>(content, position);
    }
    // OUT
    // XLAT
    // LEA
    if (0b10001101 == curr1) {
        return std::make_unique<LeaInstr>(content, position);
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
            && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b000)
        || (0b00000100 <= curr1 && curr1 <= 0b00000101)) {
        return std::make_unique<AddInstr>(content, position);
    }
    // ADC
    if ((0b00010000 <= curr1 && curr1 <= 0b00010011)
        || (0b10000000 <= curr1 && curr1 <= 0b10000011
            && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b010)
        || (0b00010100 <= curr1 && curr1 <= 0b00010101)) {
        return std::make_unique<AdcInstr>(content, position);
    }
    // INC
    if (((curr1 == 0b11111110 || curr1 == 0b11111111)
         && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b000)
        || (0b01000000 <= curr1 && curr1 <= 0b01000111)) {
        return std::make_unique<IncInstr>(content, position);
    }
    // AAA
    // BAA
    // SUB
    if ((0b00101000 <= curr1 && curr1 <= 0b00101011)
        || (0b10000000 <= curr1 && curr1 <= 0b10000011
            && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b101)
        || (0b00101100 <= curr1 && curr1 <= 0b00101101)) {
        return std::make_unique<SubInstr>(content, position);
    }
    // SSB
    if ((0b00011000 <= curr1 && curr1 <= 0b00011011)
        || (0b10000000 <= curr1 && curr1 <= 0b10000011
            && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b011)
        || (0b0001110 <= curr1 && curr1 <= 0b0001111)) {
        return std::make_unique<SbbInstr>(content, position);
    }
    // DEC
    if (((0b11111110 == curr1 || curr1 == 0b11111111)
         && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b001)
        || (0b01001000 <= curr1 && curr1 <= 0b01001111)) {
        return std::make_unique<DecInstr>(content, position);
    }
    // NEG
    if ((curr1 == 0b11110110 || curr1 == 0b11110111)
        && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b011) {
        return std::make_unique<NegInstr>(content, position);
    }
    // CMP
    if ((0b00111000 <= curr1 && curr1 <= 0b00111011)
        || (0b10000000 <= curr1 && curr1 <= 0b10000011
            && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b111)
        || (0b00111100 <= curr1 && curr1 <= 0b00111101)) {
        return std::make_unique<CmpInstr>(content, position);
    }
    // AAS
    // DAS
    // MUL
    if ((curr1 == 0b11110110 || curr1 == 0b11110111)
        && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b100) {
        return std::make_unique<MulInstr>(content, position);
    }
    // IMUL
    // AAM
    // DIV
    if ((curr1 == 0b11110110 || curr1 == 0b11110111)
        && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b110) {
        return std::make_unique<DivInstr>(content, position);
    }
    // IDIV
    // AAD
    // CBW
    if (0b10011000 == curr1) {
        return std::make_unique<CbwInstr>(content, position);
    }
    // CWD
    if (0b10011001 == curr1) {
        return std::make_unique<CwdInstr>(content, position);
    }

    /// LOGIC
    // NOT
    // SHL/SAL
    if (0b11010000 <= curr1 && curr1 <= 0b11010011
        && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b100) {
        return std::make_unique<ShlSalInstr>(content, position);
    }
    // SHR
    if (0b11010000 <= curr1 && curr1 <= 0b11010011
        && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b101) {
        return std::make_unique<ShrInstr>(content, position);
    }
    // SAR
    if (0b11010000 <= curr1 && curr1 <= 0b11010011
        && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b111) {
        return std::make_unique<SarInstr>(content, position);
    }
    // ROL
    // ROR
    // RCL
    if (0b11010000 <= curr1 && curr1 <= 0b11010011
        && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b010) {
        return std::make_unique<RclInstr>(content, position);
    }
    // RCR
    // AND
    if ((0b00100000 <= curr1 && curr1 <= 0b00100011)
        || (0b10000000 <= curr1 && curr1 <= 0b10000001
            && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b100)
        || (0b00100100 <= curr1 && curr1 <= 0b00100101)) {
        return std::make_unique<AndInstr>(content, position);
    }
    // TEST
    if ((0b10000100 <= curr1 && curr1 <= 0b10000101)
        || (0b11110110 <= curr1 && curr1 <= 0b11110111
            && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b000)
        || (0b10101000 <= curr1 && curr1 <= 0b10101001)) {
        return std::make_unique<TestInstr>(content, position);
    }
    // OR
    if ((0b00001000 <= curr1 && curr1 <= 0b00001011)
        || (0b10000000 <= curr1 && curr1 <= 0b10000001
            && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b001)
        || (0b00001100 <= curr1 && curr1 <= 0b00001101)) {
        return std::make_unique<OrInstr>(content, position);
    }
    // XOR
    if ((0b00110000 <= curr1 && curr1 <= 0b00110011)
        || (0b10000000 <= curr1 && curr1 <= 0b10000001
            && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b110)
        || (0b00110100 <= curr1 && curr1 <= 0b00110101)) {
        return std::make_unique<XorInstr>(content, position);
    }

    /// STRING MANIPULATION
    // REP
    if (0b11110010 == curr1 || 0b11110011 == curr1) {
        return std::make_unique<RepInstr>(content, position);
    }
    // MOVS
    if (0b10100100 == curr1 || 0b10100101 == curr1) {
        return std::make_unique<MovsInstr>(content, position);
    }
    // CMPS
    // SCAS
    // LODS
    // STOS

    /// CONTROL TRANSFER
    // CALL
    if (0b11101000 == curr1
        || (0b11111111 == curr1
            && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b010)
        || 0b10011010 == curr1
        || (0b11111111 == curr1
            && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b011)) {
        return std::make_unique<CallInstr>(content, position);
    }
    // JMP
    if (0b11101001 == curr1
        || 0b11101011 == curr1
        || (0b11111111 == curr1
            && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b100)
        || 0b11101010 == curr1
        || (0b11111111 == curr1
            && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b101)) {
        return std::make_unique<JmpInstr>(content, position);
    }
    // RET
    if (0b11000011 == curr1
        || 0b11000010 == curr1
        || 0b11001011 == curr1
        || 0b11001010 == curr1) {
        return std::make_unique<RetInstr>(content, position);
    }
    // JE/JZ
    if (0b01110100 == curr1) {
        return std::make_unique<JeJzInstr>(content, position);
    }
    // JL/JNGE
    if (0b01111100 == curr1) {
        return std::make_unique<JlJngeInstr>(content, position);
    }
    // JLE/JNG
    if (0b01111110 == curr1) {
        return std::make_unique<JlejngInstr>(content, position);
    }
    // JB/JNAE
    if (0b01110010 == curr1) {
        return std::make_unique<JbJnaeInstr>(content, position);
    }
    // JBE/JNA
    if (0b01110110 == curr1) {
        return std::make_unique<JbeJnaInstr>(content, position);
    }
    // JP/JPE
    // JO
    // JS
    // JNE/JNZ
    if (curr1 == 0b01110101) {
        return std::make_unique<JneJnzInstr>(content, position);
    }
    // JNL/JGE
    if (curr1 == 0b01111101) {
        return std::make_unique<JnlJgeInstr>(content, position);
    }
    // JNLE/JG
    if (curr1 == 0b01111111) {
        return std::make_unique<JnleJgInstr>(content, position);
    }
    // JNB/JAE
    if (curr1 == 0b01110011) {
        return std::make_unique<JnbJaeInstr>(content, position);
    }
    // JNBE/JA
    if (curr1 == 0b01110111) {
        return std::make_unique<JnbeJaInstr>(content, position);
    }
    // JNP/JPO
    // JNO
    // JNS
    // LOOP
    if (curr1 == 0b11100010) {
        return std::make_unique<LoopInstr>(content, position);
    }
    // LOOPZ/LOOPE
    // LOOPNZ/LOOPNE
    // JCXZ
    // INT
    if (curr1 == 0b11001101 || curr1 == 0b11001100) {
        return std::make_unique<IntInstr>(content, position);
    }
    // INTO
    // IRET

    /// PROCESSOR CONTROL
    // CLC
    // CMC
    // STC
    // CLD
    if (curr1 == 0b11111100) {
        return std::make_unique<CldInstr>(content, position);
    }
    // STD
    if (curr1 == 0b11111101) {
        return std::make_unique<StdInstr>(content, position);
    }
    // CLI
    // STI
    // HLT
    if (curr1 == 0b11110100) {
        return std::make_unique<HltInstr>(content, position);
    }
    // WAIT
    // ESC
    // LOCK

    // UNDEFINED
    return std::make_unique<Instruction>();
}
