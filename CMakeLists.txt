cmake_minimum_required(VERSION 4.3)
project(intel8084Interpreter)

set(CMAKE_CXX_STANDARD 20)

add_executable(intel8084Interpreter
        src/main.cc
        src/RunManager.cc
        src/RunManager.hh
        src/disassembler/Disassembler.cc
        src/disassembler/Disassembler.hh
        src/instructions/Instruction.cc
        src/instructions/Instruction.hh)
