#pragma once

#include <memory>
#include <vector>

#include "../instructions/Instruction.hh"

class Disassembler {
public:
    Disassembler(const std::vector<uint8_t> &content, int content_size, int header_size);

    void disassemble();

    std::unique_ptr<Instruction> disassembleInstruction(int position);

private:
    std::string getStringFromBytes(int position, int size) const;

    const std::vector<uint8_t> &content_;

    const int header_size_;;
    const int content_size_;
};
