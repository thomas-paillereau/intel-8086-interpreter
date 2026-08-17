#include "RunManager.hh"

#include <iostream>
#include <fstream>
#include <cstdint>

RunManager::RunManager(int argc, char **argv) {
    status = NORMAL;
    std::string filename;

    // Consuming given arguments
    for (int i = 0; i < argc; i++)
    {
        auto currArg = std::string(argv[i]);
        // TODO make -h and --help
        if (currArg == "-m")
            this->pretty_print_enabled_ = true;
        else if (currArg == "-d")
            this->interpreter_enabled_ = false;
        else if (currArg == "-p")
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
    if (status != WRONG_ARGS)
        return;

    // Opening file and getting content
    auto file = std::ifstream(filename, std::ios::binary);
    if (!file.is_open()) {
        status = WRONG_ARGS;
        return;
    }
    content_ = {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
}

void RunManager::run() {
    if (interpreter_enabled_)
        std::cout << "Interpreter " << std::endl;
    else
        std::cout << "Disassembler " << std::endl;
}

const std::vector<uint8_t>& RunManager::get_content() const{
    return content_;
}

bool RunManager::get_interpret_enabled() const {
    return interpreter_enabled_;
}

bool RunManager::get_pretty_print() const {
    return pretty_print_enabled_;
}
