#include "JbeJnaInstr.hh"

JbeJnaInstr::JbeJnaInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "jbe";
    position_ = position;
    size_ = 2;
    imm_low_ = content.at(position + 1);
    info_byte_type_ = DISP;
}

bool JbeJnaInstr::execute(Cpu &cpu, bool &halt, [[maybe_unused]] bool printing) {
    if (!halt && (cpu.getFlag(Cpu::CF) || cpu.getFlag(Cpu::ZF))) {
        cpu.setIp(cpu.get(type_dst_, dst_));
        return false;
    }
    cpu.addToIp(size_);
    if (position_ + size_ <= position_)
        return true;
    return false;
}
