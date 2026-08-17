#pragma once

#include <cstdint>
#include <vector>

class Disassembler {
public:
    Disassembler(const std::vector<uint8_t>& content);

    void disassemble();
    void disassemble_instruction(int &position);

private:
    const std::vector<uint8_t>& content_;
};
