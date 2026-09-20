#include "MulInstr.hh"

#include "utils/Utils.hh"

MulInstr::MulInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "mul";
    position_ = position;
    size_ = 2;
    padding_ = 0;
    uint8_t curr1 = content.at(position);
    uint8_t curr2 = content.at(position + 1);
    w_ = Utils::getEnabledBitFromByte(curr1, 0);
    mod_ = Utils::getIntervalNumFromByte(curr2, 7, 6);
    rm_ = Utils::getIntervalNumFromByte(curr2, 2, 0);

    addInfoBytes(content, position);
}

bool MulInstr::execute(Cpu &cpu, bool &halt, [[maybe_unused]] bool printing) {
    if (!halt) {
        uint16_t dst = cpu.get(type_dst_, dst_);
        uint16_t src = cpu.get(type_src_, src_);
        uint16_t value = dst * src;
        cpu.set(type_dst_, dst_, value);
        cpu.setFlag(Cpu::OF, value >> 8 != 0);
        cpu.setFlag(Cpu::CF, value >> 8 != 0);
        cpu.setLastReg(type_dst_, dst_);
    }

    cpu.addToIp(size_);
    if (position_ + size_ <= position_)
        return true;
    return false;
}
