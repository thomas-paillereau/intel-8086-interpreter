#include "RunManager.hh"
#include "disassembler/Disassembler.hh"

#include <cmath>
#include <iostream>
#include <fstream>

#define HEADER_SIZE 0x20

static void helpMessage() {
    std::cout << "intel 8086 interpreter and disassembler 2.0 (by Thomas Paillereau)" << std::endl;
    std::cout << std::endl;
    std::cout << "Usage: ./build/intel8084Interpreter [options] <filename>" << std::endl;
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -i                            activates the interpreter mode (active by default)" << std::endl;
    std::cout << "  -d                            activates the disassembler mode" << std::endl;
    std::cout << "  -m                            enables the printing of instruction on CPU action in interpreter mode"
            << std::endl;
    std::cout << "  -h                            show this help message" << std::endl;
    std::cout << std::endl;
    _Exit(0);
}

RunManager::RunManager(int argc, char **argv) {
    status = NORMAL;
    std::string filename;

    // Consuming given arguments
    for (int i = 1; i < argc; i++) {
        auto currArg = std::string(argv[i]);
        if (currArg == "-h" || currArg == "--help")
            helpMessage();
        if (currArg == "-m")
            this->pretty_print_enabled_ = true;
        else if (currArg == "-d")
            this->interpreter_enabled_ = false;
        else if (currArg == "-i")
            this->interpreter_enabled_ = true;
        else {
            if (!filename.empty())
                status = WRONG_ARGS;
            else
                filename = currArg;
        }
    }

    // Filename errors
    if (filename.empty())
        status = WRONG_ARGS;
    if (status == WRONG_ARGS)
        return;

    // Opening file and getting content
    auto file = std::ifstream(filename, std::ios::binary);
    if (!file.is_open()) {
        status = WRONG_ARGS;
        return;
    }
    content_ = {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};

    // Getting the size of instruction section
    instr_section_size_ =
            content_.at(8) % 256 * static_cast<int>(std::pow(256, 0))
            + content_.at(9) % 256 * static_cast<int>(std::pow(256, 1))
            + content_.at(10) % 256 * static_cast<int>(std::pow(256, 2))
            + content_.at(11) % 256 * static_cast<int>(std::pow(256, 3));
}

void RunManager::run() {
    try {
        if (interpreter_enabled_)
            std::cout << "Interpreter " << std::endl; //TODO
        else {
            Disassembler::init(instr_section_size_, HEADER_SIZE);
            Disassembler::disassemble(content_);
        }
    } catch (std::exception &e) {
        std::cerr << "Error : " << e.what() << std::endl;
    }
}

void RunManager::exitIfError() const {
    if (status != NORMAL) {
        if (status == WRONG_ARGS)
            std::cerr << "Wrong Arguments" << std::endl;
        else if (status == FILE_NOT_OPENED)
            std::cerr << "File could not be opened" << std::endl;
        else if (status == ERROR)
            std::cerr << "Error" << std::endl;
        _Exit(1);
    }
}

const std::vector<uint8_t> &RunManager::getContent() const {
    return content_;
}

bool RunManager::getInterpretEnabled() const {
    return interpreter_enabled_;
}

bool RunManager::getPrettyPrint() const {
    return pretty_print_enabled_;
}
