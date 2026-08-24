#include "Cpu.hh"

#include <cstring>

/// Constructor

Cpu::Cpu(const std::vector<uint8_t> &content, int content_size, int data_size
         , int n_args, char **args) {
    // Setting data into the memory
    for (int i = 0; i < data_size; ++i) {
        memory_.at(i) = content.at(i + content_size);
    }
    ss_ = data_size;

    // Separating instructions from data
    content_ = std::vector(content.begin(), content.begin() + content_size);

    // Getting env var
    std::string env = ENV;

    // Readjusting sp register
    size_t n = env.size() + 1;
    for (int i = 0; i < n_args; ++i)
        n += strlen(args[i]) + 1;

    if (n % 2 == 1)
        sp_++;

    // Creating address list
    std::vector<uint16_t> addrList;

    // Entering Env Var in memory
    memory_[--sp_] = 0;
    for (uint8_t c: env)
        memory_[--sp_] = c;

    uint16_t addrEnv = sp_;

    // Entering argv in memory
    for (int i = n_args - 1; i >= 0; --i) {
        memory_[--sp_] = 0;
        for (int j = static_cast<int>(strlen(args[i]) - 1); j >= 0; --j)
            memory_[--sp_] = args[i][j];
        addrList.push_back(sp_);
    }

    // Adding 2 null bytes
    memory_[--sp_] = 0;
    memory_[--sp_] = 0;

    // Adding env addr
    memory_[--sp_] = addrEnv >> 8;
    memory_[--sp_] = addrEnv & 0xFF;

    // Adding 2 null bytes
    memory_[--sp_] = 0;
    memory_[--sp_] = 0;

    // Adding argv addrs
    for (uint16_t addr: addrList) {
        memory_[--sp_] = addr >> 8;
        memory_[--sp_] = addr & 0xFF;
    }

    // Adding argc
    memory_[--sp_] = n_args >> 8;
    memory_[--sp_] = n_args & 0xFF;
}

/// Basic getter and setters

const std::vector<uint8_t> &Cpu::getContent() const {
    return content_;
}

uint16_t Cpu::getIp() const {
    return ip_;
}

void Cpu::setIp(uint16_t value) {
    ip_ = value;
}

bool Cpu::addToIp(uint16_t value) {
    if (value == 0)
        return false;
    if (ip_ + value < ip_)
        return true;
    ip_ += value;
    return false;
}

/// General Getter and Setter

uint16_t Cpu::get(type type, int index) const {
    switch (type) {
        case MEM8:
            return getMem8(index);
        case MEM16:
            return getMem16(index);
        case REG8:
            return getReg8(static_cast<reg8>(index));
        case REG16:
            return getReg16(static_cast<reg16>(index));
        case SEG:
            return getSeg(static_cast<seg>(index));
        case FLAG:
            return getFlag(static_cast<flag>(index));
        case IMM:
            return index;
        default:
            return 0; // TODO make error
    }
}

void Cpu::set(type type, int index, uint16_t value) {
    switch (type) {
        case MEM8:
            setMem8(index, value);
            break;
        case MEM16:
            setMem16(index, value);
            break;
        case REG8:
            setReg8(static_cast<reg8>(index), value);
            break;
        case REG16:
            setReg16(static_cast<reg16>(index), value);
            break;
        case SEG:
            setSeg(static_cast<seg>(index), value);
            break;
        case FLAG:
            setFlag(static_cast<flag>(index), value);
            break;
        default:
            break; // TODO make error
    }
}

/// Push and pop

void Cpu::push(uint16_t value) {
    sp_ -= 2;
    memory_[sp_] = value & 0xFF;
    memory_[sp_ + 1] = value >> 8;
}

uint16_t Cpu::pop() {
    uint16_t value = memory_[sp_] & 0xF;
    value += static_cast<uint16_t>(memory_[sp_ + 1]) << 8;
    sp_ += 2;
    return value;
}

/// Memory
uint8_t Cpu::getMem8(int index) const {
    return memory_[index];
}

uint16_t Cpu::getMem16(int index) const {
    uint16_t value = memory_[index] & 0xFF;
    value += static_cast<uint16_t>(memory_[index + 1]) << 8;
    return value;
}

void Cpu::setMem8(int index, uint8_t value) {
    memory_[index] = value;
}

void Cpu::setMem16(int index, uint16_t value) {
    memory_[index] = value & 0xFF;
    memory_[index + 1] = value >> 8;
}

std::array<uint8_t, MEMORY_SIZE> &Cpu::getMemory() {
    return memory_;
}

/// Reg
uint8_t Cpu::getReg8(reg8 index) const {
    switch (index) {
        case AL:
            return a_.bytes.l;
        case CL:
            return c_.bytes.l;
        case DL:
            return d_.bytes.l;
        case BL:
            return b_.bytes.l;
        case AH:
            return a_.bytes.h;
        case CH:
            return c_.bytes.h;
        case DH:
            return d_.bytes.h;
        case BH:
            return b_.bytes.h;
        default:
            return 0; // TODO make error
    }
}

void Cpu::setReg8(reg8 index, uint8_t value) {
    switch (index) {
        case AL:
            a_.bytes.l = value;
            break;
        case CL:
            c_.bytes.l = value;
            break;
        case DL:
            d_.bytes.l = value;
            break;
        case BL:
            b_.bytes.l = value;
            break;
        case AH:
            a_.bytes.h = value;
            break;
        case CH:
            c_.bytes.h = value;
            break;
        case DH:
            d_.bytes.h = value;
            break;
        case BH:
            b_.bytes.h = value;
            break;
        default:
            break; // TODO make error
    }
}

uint16_t Cpu::getReg16(reg16 index) const {
    switch (index) {
        case AX:
            return a_.x;
        case CX:
            return c_.x;
        case DX:
            return d_.x;
        case BX:
            return b_.x;
        case SP:
            return sp_;
        case BP:
            return bp_;
        case SI:
            return si_;
        case DI:
            return di_;
        default:
            return 0; // TODO make error
    }
}

void Cpu::setReg16(reg16 index, uint16_t value) {
    switch (index) {
        case AX:
            a_.x = value;
            break;
        case CX:
            c_.x = value;
            break;
        case DX:
            d_.x = value;
            break;
        case BX:
            b_.x = value;
            break;
        case SP:
            sp_ = value;
            break;
        case BP:
            bp_ = value;
            break;
        case SI:
            si_ = value;
            break;
        case DI:
            di_ = value;
            break;
        default:
            break; // TODO make error
    }
}

/// Seg

uint16_t Cpu::getSeg(seg index) const {
    switch (index) {
        case ES:
            return es_;
        case CS:
            return cs_;
        case SS:
            return ss_;
        case DS:
            return ds_;
        default:
            return 0; // TODO make error
    }
}

void Cpu::setSeg(seg index, uint16_t value) {
    switch (index) {
        case ES:
            es_ = value;
            break;
        case CS:
            cs_ = value;
            break;
        case SS:
            ss_ = value;
            break;
        case DS:
            ds_ = value;
            break;
        default:
            break; // TODO make error
    }
}

/// Flags

bool Cpu::getFlag(flag flag) const {
    switch (flag) {
        case OF:
            return of_;
        case SF:
            return sf_;
        case ZF:
            return zf_;
        case CF:
            return cf_;
        default:
            return false; // TODO make error
    }
}

void Cpu::setFlag(flag flag, bool value) {
    switch (flag) {
        case OF:
            of_ = value;
            break;
        case SF:
            sf_ = value;
            break;
        case ZF:
            zf_ = value;
            break;
        case CF:
            cf_ = value;
            break;
        default:
            break; // TODO make error
    }
}

void Cpu::updateOF(short dst, short src, short res, char operation) {
    if (operation == '+') {
        of_ = false;
        if (dst < 0 && src < 0 && res >= 0)
            of_ = true;
        if (dst >= 0 && src >= 0 && res < 0)
            of_ = true;
    } else if (operation == '-') {
        of_ = false;
        src = -src;
        if (dst < 0 && src < 0 && res >= 0)
            of_ = true;
        if (dst >= 0 && src >= 0 && res < 0)
            of_ = true;
    }
}

void Cpu::updateSF(short value) {
    sf_ = value < 0;
}

void Cpu::updateZF(short value) {
    zf_ = value == 0;
}

void Cpu::updateCF(uint16_t dst, uint16_t src, char operation) {
    if (operation == '-') {
        cf_ = dst < src;
    } else {
        uint32_t dst32 = dst;
        uint32_t src32 = src;
        uint32_t res = dst32 + src32;
        cf_ = res > 0xFFFF;
    }
}

std::pair<Cpu::type, uint16_t> Cpu::getLastReg() const {
    return last_reg_;
}

void Cpu::setLastReg(type type, uint16_t value) {
    last_reg_ = std::make_pair(type, value);
}
