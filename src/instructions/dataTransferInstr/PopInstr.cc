#include "PopInstr.hh"

#include "utils/Utils.hh"

PopInstr::PopInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "pop";
    position_ = position;

    uint8_t curr1 = content.at(position);
    if (curr1 == 0b10001111) {
        uint8_t curr2 = content.at(position + 1);
        effect_ = 0;
        size_ = 2;
        mod_ = Utils::getIntervalNumFromByte(curr2, 7, 6);
        rm_ = Utils::getIntervalNumFromByte(curr2, 2, 0);
    } else if (0b01011000 <= curr1 && curr1 <= 0b01011111) {
        effect_ = 1;
        size_ = 1;
        reg_ = Utils::getIntervalNumFromByte(curr1, 2, 0);
    } else {
        effect_ = 2;
        size_ = 1;
        two_bits_reg_ = true;
        reg_ = Utils::getIntervalNumFromByte(curr1, 4, 3);
    }

    addInfoBytes(content, position);

    // POP only takes 16-bit operands
    w_ = true;
}

bool PopInstr::execute(Cpu &cpu, [[maybe_unused]] bool printing) {
    uint16_t value = cpu.pop();
    cpu.set(type_dst_, dst_, value);

    cpu.setLastReg(type_dst_, dst_);
    cpu.addToIp(size_);
    if (position_ + size_ <= position_)
        return true;
    return false;
}
