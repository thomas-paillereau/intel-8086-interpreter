#pragma once

#include <memory>
#include <vector>

#include "../instructions/Instruction.hh"

class Disassembler {
public:
    static void init(int content_size, int header_size);

    static int getHeaderSize();

    static void disassemble(const std::vector<uint8_t> &content);

    static std::unique_ptr<Instruction> disassembleInstruction(const std::vector<uint8_t> &content, int position);

private:
    static std::string getStringFromBytes(const std::vector<uint8_t> &content, int position, int size);

    static int header_size_;
    static int content_size_;
};
