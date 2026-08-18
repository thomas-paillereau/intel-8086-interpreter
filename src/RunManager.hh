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
    RunManager(int argc, char **argv);

    /// Running the program depending on the chosen flags
    void run();

    /// Exits the process corresponding to the status
    void exitIfError() const;

    /// Getter of the content of the file given as argument
    const std::vector<uint8_t> &getContent() const;

    /// Getter of interpreter_enabled_
    bool getInterpretEnabled() const;

    /// Getter of pretty_print_enabled_
    bool getPrettyPrint() const;

private:
    bool interpreter_enabled_;
    bool pretty_print_enabled_;

    std::vector<uint8_t> content_;
    int instSectionSize_;
};
