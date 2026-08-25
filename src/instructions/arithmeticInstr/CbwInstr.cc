#include "CbwInstr.hh"

CbwInstr::CbwInstr([[maybe_unused]] const std::vector<uint8_t> &content, int position) {
    name_ = "cbw";
    position_ = position;
}

bool CbwInstr::execute(Cpu &cpu, bool &halt, [[maybe_unused]] bool printing) {
    if (!halt) {
        /*std::pair<Cpu::type, uint16_t> lastReg = cpu.getLastReg();
        if (lastReg.first == Cpu::type::REG8 && lastReg.second < 4) {
            // Checking for reg8 register, between AL and DL
            uint16_t value = cpu.getReg8(static_cast<Cpu::reg8>(lastReg.second)) & 0xFF;
            if (value & 0x80)
                value |= 0xFF00;
            else
                value &= 0x00FF;
            cpu.setReg16(static_cast<Cpu::reg16>(lastReg.second), value);
        }*/
        uint16_t value = cpu.getReg8(Cpu::reg8::AL);

        if (value & 0x80)
            value |= 0xFF00;

        cpu.setReg16(Cpu::reg16::AX, value);
    }
    
    cpu.addToIp(size_);
    if (position_ + size_ <= position_)
        return true;
    return false;
}
