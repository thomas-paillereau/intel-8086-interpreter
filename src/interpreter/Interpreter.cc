#include "Interpreter.hh"

#include <iomanip>
#include <iostream>

#include "disassembler/Disassembler.hh"

#define HEX std::hex << std::setw(4) << std::setfill('0')

Interpreter::Interpreter(const std::vector<uint8_t> &content, int content_size, int data_size,
                         int interpreter_args_size_, char **interpreter_args) : content_size_(content_size) {
    cpu_ = Cpu(content, content_size, data_size, interpreter_args_size_, interpreter_args);
    Disassembler::init(content_size);
}

void Interpreter::setPrinting(bool value) {
    printing_enabled_ = value;
}

void Interpreter::interpret() {
    if (printing_enabled_)
        std::cout << " AX   BX   CX   DX   SP   BP   SI   DI  FLAGS IP" << std::endl;
    bool running = true;
    bool halt = false;
    while (running) {
        // Getting instruction
        std::unique_ptr<Instruction> instr;
        try {
            instr = Disassembler::disassembleInstruction(cpu_.getContent(), cpu_.getIp());
        } catch (std::out_of_range &e) {
            std::cerr << "CPU has reach end of the instructions" << std::endl;
            break;
        }
        instr->searchValues(cpu_);

        // Printing if necessary
        if (printing_enabled_) {
            std::cout << HEX << cpu_.getReg16(Cpu::AX) << " ";
            std::cout << HEX << cpu_.getReg16(Cpu::BX) << " ";
            std::cout << HEX << cpu_.getReg16(Cpu::CX) << " ";
            std::cout << HEX << cpu_.getReg16(Cpu::DX) << " ";
            std::cout << HEX << cpu_.getReg16(Cpu::SP) << " ";
            std::cout << HEX << cpu_.getReg16(Cpu::BP) << " ";
            std::cout << HEX << cpu_.getReg16(Cpu::SI) << " ";
            std::cout << HEX << cpu_.getReg16(Cpu::DI) << " ";

            std::cout << (cpu_.getFlag(Cpu::OF) ? "O" : "-");
            std::cout << (cpu_.getFlag(Cpu::SF) ? "S" : "-");
            std::cout << (cpu_.getFlag(Cpu::ZF) ? "Z" : "-");
            std::cout << (cpu_.getFlag(Cpu::CF) ? "C" : "-");
            std::cout << " ";

            printf("%04x:%-13s"
                   , cpu_.getIp()
                   , Disassembler::getStringFromBytes(cpu_.getContent(), cpu_.getIp(), instr->getSize()).c_str());
            instr->setZeroPadding();
            std::cout << instr->toString();
            instr->printAddressOfVals(cpu_);
        }

        // Executing the command
        bool ip_exceeded = instr->execute(cpu_, halt, printing_enabled_);

        if (ip_exceeded) {
            std::cerr << "Error : Instruction section size was exceeded." << std::endl;
            running = false;
        }
    }
}
