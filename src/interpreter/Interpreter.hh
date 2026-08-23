#pragma once

#include <vector>

#include "Cpu.hh"
#include "instructions/Instruction.hh"

class Interpreter {
public:
    Interpreter(const std::vector<uint8_t> &content, int content_size, int data_size,
                int interpreter_args_size_, char **interpreter_args);

    void setPrinting(bool value);

    void interpret();

private:
    std::unique_ptr<Instruction> printCpuStatus() const;

    Cpu cpu_;

    int content_size_;

    bool printing_enabled_ = false;
};
