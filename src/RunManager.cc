#include "RunManager.hh"
#include "disassembler/Disassembler.hh"

#include <cmath>
#include <iostream>
#include <fstream>

#include "interpreter/Interpreter.hh"

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
    int i = 1;
    for (; i < argc; i++) {
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
            filename = currArg;
            break;
        }
    }
    interpreter_args_ = argv + i + 1;
    interpreter_args_size_ = argc - i - 1;


    // Filename errors
    if (filename.empty()) {
        status = WRONG_ARGS;
        return;
    }

    // Opening file and getting content
    auto file = std::ifstream(filename, std::ios::binary);
    if (!file.is_open()) {
        status = WRONG_ARGS;
        return;
    }
    content_ = {std::istreambuf_iterator(file), std::istreambuf_iterator<char>()};

    // Getting the size of instruction section
    content_size_ =
            content_.at(8) % 256 * static_cast<int>(std::pow(256, 0))
            + content_.at(9) % 256 * static_cast<int>(std::pow(256, 1))
            + content_.at(10) % 256 * static_cast<int>(std::pow(256, 2))
            + content_.at(11) % 256 * static_cast<int>(std::pow(256, 3));

    data_size_ =
            content_.at(12) % 256 * static_cast<int>(std::pow(256, 0))
            + content_.at(13) % 256 * static_cast<int>(std::pow(256, 1))
            + content_.at(14) % 256 * static_cast<int>(std::pow(256, 2))
            + content_.at(15) % 256 * static_cast<int>(std::pow(256, 3));

    // Removing header, which is not useful anymore
    content_ = std::vector(content_.begin() + HEADER_SIZE, content_.end());
}

void RunManager::run() {
    //try {
    if (interpreter_enabled_) {
        auto interpreter = Interpreter(content_, content_size_, data_size_
                                       , interpreter_args_size_, interpreter_args_);
        interpreter.setPrinting(pretty_print_enabled_);
        interpreter.interpret();
    } else {
        std::cout << "Size: " << content_.size() << std::endl;
        std::cout << "Content Size: " << content_size_ << std::endl;
        content_ = std::vector(content_.begin(), content_.begin() + content_size_);
        Disassembler::init(content_size_);
        Disassembler::disassemble(content_);
    }
    /*} catch (std::exception &e) {
        throw e;
    }*/
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
