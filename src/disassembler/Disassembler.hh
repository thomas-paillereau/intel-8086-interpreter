#pragma once

#include <memory>
#include <vector>

#include "../instructions/Instruction.hh"

class Disassembler {
public:
    static void init(int content_size);

    static int getContentSize();

    static void disassemble(const std::vector<uint8_t> &content);

    static std::unique_ptr<Instruction> disassembleInstruction(const std::vector<uint8_t> &content, int position);

    static std::string getStringFromBytes(const std::vector<uint8_t> &content, int position, int size);

private:
    static int content_size_;
};
