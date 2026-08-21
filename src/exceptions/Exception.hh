#pragma once

#include <exception>
#include <string>
#include <utility>

class Exception : public std::exception {
public:
    explicit Exception(const char *message)
        : msg_(message) {
    }

    Exception(std::string message)
        : msg_(std::move(message)) {
    }


    ~Exception() noexcept override = default;

    const char *what() const noexcept override {
        return msg_.c_str();
    }

protected:
    std::string msg_;
};
