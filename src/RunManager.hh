#pragma once

#include <cstdint>
#include <vector>

/// This class is used to store information on the current program
/// It contains the content of the file given as arguments of this executable
/// It also stocks the flags used during the execution
class RunManager {
public:
    /// Current status of the program
    enum status {
        NORMAL = 0,
        ERROR,
        WRONG_ARGS,
        FILE_NOT_OPENED,
    };
    status status;

    /// Constructor
    RunManager(int argc, char** argv);

    /// Running the program depending on the chosen flags
    void run();

    /// Getter of the content of the file given as argument
    const std::vector<uint8_t>& get_content() const;

    /// Getter of interpreter_enabled_
    bool get_interpret_enabled() const;

    /// Getter of pretty_print_enabled_
    bool get_pretty_print() const;

private:
    bool interpreter_enabled_;
    bool pretty_print_enabled_;
    std::vector<uint8_t> content_;
};
