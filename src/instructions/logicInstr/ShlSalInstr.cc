#include "ShlSalInstr.hh"

#include "utils/Utils.hh"

ShlSalInstr::ShlSalInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "shl";
    position_ = position;
    size_ = 2;

    uint8_t curr1 = content.at(position);
    uint8_t curr2 = content.at(position + 1);

    w_ = Utils::getEnabledBitFromByte(curr1, 0);
    v_ = Utils::getEnabledBitFromByte(curr1, 1);
    v_used_ = true;

    mod_ = Utils::getIntervalNumFromByte(curr2, 7, 6);
    rm_ = Utils::getIntervalNumFromByte(curr2, 2, 0);

    addInfoBytes(content, position);
}

bool ShlSalInstr::execute(Cpu &cpu, bool &halt, [[maybe_unused]] bool printing) {
    if (!halt) {
        uint16_t dst = cpu.get(type_dst_, dst_);
        uint16_t src = cpu.get(type_src_, src_);
        uint16_t value = dst << src;
        cpu.set(type_dst_, dst_, value);
        cpu.setFlag(Cpu::CF, dst >> (16 - src) & 0x1);
        cpu.updateSF(static_cast<short>(value));
        cpu.updateZF(static_cast<short>(value));
        cpu.setLastReg(type_dst_, dst_);
    }
    cpu.addToIp(size_);
    if (position_ + size_ <= position_)
        return true;
    return false;
}
