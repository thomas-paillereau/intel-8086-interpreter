#include "JneJnzInstr.hh"

JneJnzInstr::JneJnzInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "jne";
    position_ = position;
    size_ = 2;
    imm_low_ = content.at(position + 1);
    info_byte_type_ = DISP;
}

bool JneJnzInstr::execute(Cpu &cpu, [[maybe_unused]] bool printing) {
    if (!cpu.getFlag(Cpu::ZF)) {
        cpu.setIp(cpu.get(type_dst_, dst_));
        return false;
    }
    cpu.addToIp(size_);
    if (position_ + size_ <= position_)
        return true;
    return false;
}
