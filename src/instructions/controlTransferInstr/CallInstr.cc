#include "CallInstr.hh"

#include "utils/Utils.hh"

CallInstr::CallInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "call";
    position_ = position;

    uint8_t curr1 = content.at(position);

    w_ = Utils::getEnabledBitFromByte(curr1, 0);
    if (0b11101000 == curr1) {
        effect_ = 0;
        size_ = 1;
        info_byte_type_ = DISP_HL;
    } else if (0b11111111 == curr1
               && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b010) {
        effect_ = 1;
        size_ = 2;
    } else if (0b10011010 == curr1) {
        effect_ = 2;
        size_ = 1;
        info_byte_type_ = OFFSET_HL;
    } else {
        effect_ = 3;
        size_ = 1;
    }

    if (effect_ == 1 || effect_ == 3) {
        uint8_t curr2 = content.at(position + 1);
        mod_ = Utils::getIntervalNumFromByte(curr2, 7, 6);
        rm_ = Utils::getIntervalNumFromByte(curr2, 2, 0);
    }

    addInfoBytes(content, position);
}

bool CallInstr::execute(Cpu &cpu, bool &halt, [[maybe_unused]] bool printing) {
    if (!halt) {
        uint16_t currIp = cpu.getIp();
        cpu.push(currIp + size_);
        cpu.setIp(cpu.get(type_dst_, dst_));
        return false;
    }

    cpu.addToIp(size_);
    if (position_ + size_ <= position_)
        return true;
    return false;
}
