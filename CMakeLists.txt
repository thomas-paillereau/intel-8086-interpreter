#cmake_minimum_required(VERSION 4.3)
cmake_minimum_required(VERSION 3.31.6)
project(intel8084Interpreter)

set(CMAKE_CXX_STANDARD 20)

add_executable(intel8084Interpreter
        src/main.cc
        src/RunManager.cc
        src/RunManager.hh
        src/disassembler/Disassembler.cc
        src/disassembler/Disassembler.hh
        src/instructions/Instruction.cc
        src/instructions/Instruction.hh
        src/instructions/AddInstr.cc
        src/instructions/AddInstr.hh
        src/instructions/MovInstr.cc
        src/instructions/MovInstr.hh
        src/utils/Utils.cc
        src/utils/Utils.hh
        src/instructions/instruction-header.hh
        src/instructions/IntInstr.cc
        src/instructions/IntInstr.hh
        src/instructions/PushInstr.cc
        src/instructions/PushInstr.hh
        src/instructions/PopInstr.cc
        src/instructions/PopInstr.hh
)

target_compile_options(intel8084Interpreter PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

target_include_directories(intel8084Interpreter PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
