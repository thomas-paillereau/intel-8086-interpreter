#include "Cpu.hh"

/// Constructor

Cpu::Cpu(const std::vector<uint8_t> &content, int content_size, int data_size
         , int n_args, char **args) {
    content_ = std::vector<uint8_t>(content.begin(), content.begin() + content_size);
    std::string env = ENV;
    for (int i = 0; i < data_size; ++i) {
        memory_.at(i) = content.at(i + content_size);
    }
    ss_ = data_size;
    // TODO add env and args
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
