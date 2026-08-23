#pragma once

#define MEMORY_SIZE 0xFFFF

#include <memory>
#include <vector>

class Cpu {
public:
    /// Constructors
    Cpu() = default;

    Cpu(const std::vector<uint8_t> &data);

    /// Basic Push and Pop of memory (with sp as index)
    void push(uint16_t value);

    uint16_t pop();

    /// Getting and setting memory

    uint8_t getMem8(int index) const;

    uint16_t getMem16(int index) const;

    void setMem8(int index, uint8_t value);

    void setMem16(int index, uint16_t value);

    /// Getting info from registers

    uint8_t getReg8(int index) const;

    uint16_t getReg16(int index) const;

    void setReg8(int index, uint8_t value);

    void setReg16(int index, uint16_t value);

    /// Getting and Setting of segments

    uint16_t getSeg(int index) const;

    void setSeg(int index, uint16_t value);

    /// Interacting with flags

    enum flag {
        OF = 0,
        SF = 1,
        ZF = 2,
        CF = 4,
    };

    bool getFlag(flag flag) const;

    void setFlag(flag flag, bool value);

private:
    /// Union to create the uint16/uint8 situation
    union reg {
        uint16_t x;

        struct part {
            uint8_t h;
            uint8_t l;
        } bytes;
    };

    uint16_t ip_ = 0x0000;

    reg a_{};
    reg b_{};
    reg c_{};
    reg d_{};
    uint16_t sp_ = 0x0000;
    uint16_t bp_ = 0x0000;
    uint16_t si_ = 0x0000;
    uint16_t di_ = 0x0000;

    uint16_t cs_ = 0x0000;
    uint16_t ds_ = 0x0000;
    uint16_t ss_ = 0x0000;
    uint16_t es_ = 0x0000;

    bool of_ = false;
    bool sf_ = false;
    bool zf_ = false;
    bool cf_ = false;

    std::unique_ptr<char> lastReg_ = nullptr;

    uint8_t memory_[MEMORY_SIZE] = {};
};
