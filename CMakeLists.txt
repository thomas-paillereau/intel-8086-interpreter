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
        src/instructions/arithmeticInstr/AddInstr.cc
        src/instructions/arithmeticInstr/AddInstr.hh
        src/instructions/dataTransferInstr/MovInstr.cc
        src/instructions/dataTransferInstr/MovInstr.hh
        src/utils/Utils.cc
        src/utils/Utils.hh
        src/instructions/instruction-header.hh
        src/instructions/controlTransferInstr/IntInstr.cc
        src/instructions/controlTransferInstr/IntInstr.hh
        src/instructions/dataTransferInstr/PushInstr.cc
        src/instructions/dataTransferInstr/PushInstr.hh
        src/instructions/dataTransferInstr/PopInstr.cc
        src/instructions/dataTransferInstr/PopInstr.hh
        src/instructions/logicInstr/XorInstr.cc
        src/instructions/logicInstr/XorInstr.hh
        src/instructions/dataTransferInstr/LeaInstr.cc
        src/instructions/dataTransferInstr/LeaInstr.hh
        src/instructions/arithmeticInstr/CmpInstr.cc
        src/instructions/arithmeticInstr/CmpInstr.hh
        src/instructions/controlTransferInstr/JnbJnaInstr.cc
        src/instructions/controlTransferInstr/JnbJnaInstr.hh
        src/instructions/logicInstr/TestInstr.cc
        src/instructions/logicInstr/TestInstr.hh
        src/instructions/controlTransferInstr/JneJnzInstr.cc
        src/instructions/controlTransferInstr/JneJnzInstr.hh
        src/instructions/controlTransferInstr/CallInstr.cc
        src/instructions/controlTransferInstr/CallInstr.hh
        src/instructions/processorControlInstr/HltInstr.cc
        src/instructions/processorControlInstr/HltInstr.hh
        src/instructions/controlTransferInstr/JmpInstr.cc
        src/instructions/controlTransferInstr/JmpInstr.hh
        src/instructions/arithmeticInstr/DecInstr.cc
        src/instructions/arithmeticInstr/DecInstr.hh
        src/instructions/controlTransferInstr/JlJngeInstr.cc
        src/instructions/controlTransferInstr/JlJngeInstr.hh
        src/instructions/logicInstr/ShlSalInstr.cc
        src/instructions/logicInstr/ShlSalInstr.hh
        src/instructions/controlTransferInstr/JeJzInstr.cc
        src/instructions/controlTransferInstr/JeJzInstr.hh
        src/instructions/controlTransferInstr/RetInstr.cc
        src/instructions/controlTransferInstr/RetInstr.hh
        src/instructions/logicInstr/AndInstr.cc
        src/instructions/logicInstr/AndInstr.hh
        src/instructions/dataTransferInstr/InInstr.cc
        src/instructions/dataTransferInstr/InInstr.hh
        src/instructions/arithmeticInstr/SbbInstr.cc
        src/instructions/arithmeticInstr/SbbInstr.hh
        src/instructions/arithmeticInstr/SubInstr.cc
        src/instructions/arithmeticInstr/SubInstr.hh
        src/instructions/logicInstr/OrInstr.cc
        src/instructions/logicInstr/OrInstr.hh
        src/instructions/controlTransferInstr/JnlJgeInstr.cc
        src/instructions/controlTransferInstr/JnlJgeInstr.hh
        src/instructions/arithmeticInstr/NegInstr.cc
        src/instructions/arithmeticInstr/NegInstr.hh
        src/instructions/arithmeticInstr/CbwInstr.cc
        src/instructions/arithmeticInstr/CbwInstr.hh
        src/instructions/arithmeticInstr/CwdInstr.cc
        src/instructions/arithmeticInstr/CwdInstr.hh
        src/instructions/arithmeticInstr/IncInstr.cc
        src/instructions/arithmeticInstr/IncInstr.hh
        src/instructions/controlTransferInstr/JnleJgInstr.cc
        src/instructions/controlTransferInstr/JnleJgInstr.hh
)

target_compile_options(intel8084Interpreter PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

target_include_directories(intel8084Interpreter PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
