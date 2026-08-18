#include "RunManager.hh"
#include "disassembler/Disassembler.hh"

#include <cmath>
#include <iostream>
#include <fstream>

#define HEADER_SIZE 0x20

RunManager::RunManager(int argc, char **argv) {
    status = NORMAL;
    std::string filename;

    // Consuming given arguments
    for (int i = 1; i < argc; i++) {
        auto currArg = std::string(argv[i]);
        // TODO make -h and --help
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
            + content_.at(7) % 256 * static_cast<int>(std::pow(256, 1))
            + content_.at(6) % 256 * static_cast<int>(std::pow(256, 2))
            + content_.at(5) % 256 * static_cast<int>(std::pow(256, 3));
}

void RunManager::run() {
    if (interpreter_enabled_)
        std::cout << "Interpreter " << std::endl;
    else {
        auto disassembler = Disassembler(content_, instr_section_size_, HEADER_SIZE);
        disassembler.disassemble();
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
