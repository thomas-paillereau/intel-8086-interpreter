#include "JbJnaeInstr.hh"

JbJnaeInstr::JbJnaeInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "jb";
    position_ = position;
    size_ = 2;
    imm_low_ = content.at(position + 1);
    info_byte_type_ = DISP;
}

bool JbJnaeInstr::execute(Cpu &cpu, bool &halt, [[maybe_unused]] bool printing) {
    if (!halt && cpu.getFlag(Cpu::CF)) {
        cpu.setIp(cpu.get(type_dst_, dst_));
        return false;
    }
    cpu.addToIp(size_);
    if (position_ + size_ <= position_)
        return true;
    return false;
}
