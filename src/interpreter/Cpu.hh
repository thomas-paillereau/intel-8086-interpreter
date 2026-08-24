#pragma once

#define MEMORY_SIZE 0xFFFF
#define ENV "PATH=/usr:/usr/bin";

#include <array>
#include <memory>
#include <vector>

class Cpu {
public:
    /// Constructors
    Cpu() = default;

    Cpu(const std::vector<uint8_t> &content, int content_size, int data_size, int n_args, char **args);

    /// Direct getter to instructions

    const std::vector<uint8_t> &getContent() const;

    /// Getter, setter and augmentor of IP

    uint16_t getIp() const;

    void setIp(uint16_t value);

    bool addToIp(uint16_t value);

    /// Basic Push and Pop of memory (with sp as index)

    void push(uint16_t value);

    uint16_t pop();

    /// General Getter and Setter

    enum type {
        NONE,
        MEM8,
        MEM16,
        REG8,
        REG16,
        SEG,
        FLAG,
        IMM,
    };

    uint16_t get(type type, int index) const;

    void set(type type, int index, uint16_t value);

    /// Getting and setting memory

    uint8_t getMem8(int index) const;

    uint16_t getMem16(int index) const;

    void setMem8(int index, uint8_t value);

    void setMem16(int index, uint16_t value);

    std::array<uint8_t, MEMORY_SIZE> &getMemory();

    /// Getting info from 8 bit register

    enum reg8 {
        AL = 0b000,
        CL = 0b001,
        DL = 0b010,
        BL = 0b011,
        AH = 0b100,
        CH = 0b101,
        DH = 0b110,
        BH = 0b111,
        ERR_8B,
    };

    uint8_t getReg8(reg8 index) const;

    void setReg8(reg8 index, uint8_t value);

    /// Getting info from 16 bit registers

    enum reg16 {
        AX = 0b000,
        CX = 0b001,
        DX = 0b010,
        BX = 0b011,
        SP = 0b100,
        BP = 0b101,
        SI = 0b110,
        DI = 0b111,
        ERR_16B,
    };

    uint16_t getReg16(reg16 index) const;

    void setReg16(reg16 index, uint16_t value);

    /// Getting and Setting of segments

    enum seg {
        ES = 0b00,
        CS = 0b01,
        SS = 0b10,
        DS = 0b11,
    };

    uint16_t getSeg(seg index) const;

    void setSeg(seg index, uint16_t value);

    /// Interacting with flags

    enum flag {
        OF = 0,
        SF = 1,
        ZF = 2,
        CF = 4,
    };

    bool getFlag(flag flag) const;

    void setFlag(flag flag, bool value);

    void updateOF(short dst, short src, short res, char operation);

    void updateSF(short value);

    void updateZF(short value);

    void updateCF(uint16_t dst, uint16_t src, char operation);

    /// Getter and setter of last register used

    std::pair<type, uint16_t> getLastReg() const;

    void setLastReg(type type, uint16_t value);

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
    uint16_t es_ = 0xfffe;

    bool of_ = false;
    bool sf_ = false;
    bool zf_ = false;
    bool cf_ = false;

    std::pair<type, uint16_t> last_reg_ = std::make_pair(NONE, 0);

    std::array<uint8_t, MEMORY_SIZE> memory_ = std::array<uint8_t, MEMORY_SIZE>();
    int memory_size_ = MEMORY_SIZE;

    std::vector<uint8_t> content_;
};
