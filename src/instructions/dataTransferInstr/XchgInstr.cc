#include "XchgInstr.hh"

#include "utils/Utils.hh"

XchgInstr::XchgInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "xchg";
    position_ = position;

    uint8_t curr1 = content.at(position_);
    if (curr1 == 0b10000110 || curr1 == 0b10000111) {
        uint8_t curr2 = content.at(position_ + 1);
        effect_ = 0;
        size_ = 2;
        w_ = Utils::getEnabledBitFromByte(curr1, 0);
        mod_ = Utils::getIntervalNumFromByte(curr2, 7, 6);
        reg_ = Utils::getIntervalNumFromByte(curr2, 5, 3);
        rm_ = Utils::getIntervalNumFromByte(curr2, 2, 0);
    } else {
        effect_ = 1;
        size_ = 1;
        w_ = true;
        reg_ = Utils::getIntervalNumFromByte(curr1, 2, 0);
    }

    addInfoBytes(content, position);
}

bool XchgInstr::execute(Cpu &cpu, bool &halt, [[maybe_unused]] bool printing) {
    if (!halt) {
        uint16_t dst = cpu.get(type_dst_, dst_);
        uint16_t src = cpu.get(type_src_, src_);
        cpu.set(type_dst_, dst_, src);
        cpu.set(type_src_, src_, dst);
    }

    cpu.addToIp(size_);
    if (position_ + size_ <= position_)
        return true;
    return false;
}
