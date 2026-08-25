#include "CwdInstr.hh"

CwdInstr::CwdInstr([[maybe_unused]] const std::vector<uint8_t> &content, int position) {
    name_ = "cwd";
    position_ = position;
}

bool CwdInstr::execute(Cpu &cpu, bool &halt, [[maybe_unused]] bool printing) {
    if (!halt) {
        if ((cpu.getReg16(Cpu::AX) & 0x8000) != 0) {
            cpu.setReg16(Cpu::DX, 0xFFFF);
        } else {
            cpu.setReg16(Cpu::DX, 0x0000);
        }
    }
    cpu.addToIp(size_);
    if (position_ + size_ <= position_)
        return true;
    return false;
}
