#include "Cpu.hh"

/// Constructor

Cpu::Cpu(const std::vector<uint8_t> &data) {
}

/// Basic getter and setters

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

uint8_t Cpu::getReg8(int index) const {
    switch (index) {
        case 0b000:
            return a_.bytes.l;
        case 0b001:
            return c_.bytes.l;
        case 0b010:
            return d_.bytes.l;
        case 0b011:
            return b_.bytes.l;
        case 0b100:
            return a_.bytes.h;
        case 0b101:
            return c_.bytes.h;
        case 0b110:
            return d_.bytes.h;
        case 0b111:
            return b_.bytes.h;
        default:
            return 0; // TODO make error
    }
}

uint16_t Cpu::getReg16(int index) const {
    switch (index) {
        case 0b000:
            return a_.x;
        case 0b001:
            return c_.x;
        case 0b010:
            return d_.x;
        case 0b011:
            return b_.x;
        case 0b100:
            return sp_;
        case 0b101:
            return bp_;
        case 0b110:
            return si_;
        case 0b111:
            return di_;
        default:
            return 0; // TODO make error
    }
}

void Cpu::setReg8(int index, uint8_t value) {
    switch (index) {
        case 0b000:
            a_.bytes.l = value;
            break;
        case 0b001:
            c_.bytes.l = value;
            break;
        case 0b010:
            d_.bytes.l = value;
            break;
        case 0b011:
            b_.bytes.l = value;
            break;
        case 0b100:
            a_.bytes.h = value;
            break;
        case 0b101:
            c_.bytes.h = value;
            break;
        case 0b110:
            d_.bytes.h = value;
            break;
        case 0b111:
            b_.bytes.h = value;
            break;
        default:
            break; // TODO make error
    }
}

void Cpu::setReg16(int index, uint16_t value) {
    switch (index) {
        case 0b000:
            a_.x = value;
            break;
        case 0b001:
            c_.x = value;
            break;
        case 0b010:
            d_.x = value;
            break;
        case 0b011:
            b_.x = value;
            break;
        case 0b100:
            sp_ = value;
            break;
        case 0b101:
            bp_ = value;
            break;
        case 0b110:
            si_ = value;
            break;
        case 0b111:
            di_ = value;
            break;
        default:
            break; // TODO make error
    }
}

uint16_t Cpu::getSeg(int index) const {
    switch (index) {
        case 0b000:
            return es_;
        case 0b001:
            return cs_;
        case 0b010:
            return ss_;
        case 0b011:
            return ds_;
        case 0b100:
        default:
            return 0; // TODO make error
    }
}

void Cpu::setSeg(int index, uint16_t value) {
    switch (index) {
        case 0b000:
            es_ = value;
            break;
        case 0b001:
            cs_ = value;
            break;
        case 0b010:
            ss_ = value;
            break;
        case 0b011:
            ds_ = value;
            break;
        case 0b100:
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
