#include "AdcInstr.hh"

#include "utils/Utils.hh"

AdcInstr::AdcInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "adc";
    position_ = position;

    uint8_t curr1 = content.at(position);
    uint8_t curr2 = content.at(position + 1);

    if (0b00010000 <= curr1 && curr1 <= 0b00010011) {
        effect_ = 0;
        size_ = 2;
        d_ = Utils::getEnabledBitFromByte(curr1, 1);
    } else if (0b10000000 <= curr1 && curr1 <= 0b10000011) {
        effect_ = 1;
        size_ = 2;
        info_byte_type_ = DATA;
        s_ = Utils::getEnabledBitFromByte(curr1, 1);
    } else {
        effect_ = 2;
        size_ = 1;
        info_byte_type_ = DATA;
    }

    w_ = Utils::getEnabledBitFromByte(curr1, 0);

    if (effect_ == 0 || effect_ == 1) {
        mod_ = Utils::getIntervalNumFromByte(curr2, 7, 6);
        rm_ = Utils::getIntervalNumFromByte(curr2, 2, 0);
        if (effect_ == 0)
            reg_ = Utils::getIntervalNumFromByte(curr2, 5, 3);
    }

    addInfoBytes(content, position);
}

bool AdcInstr::execute(Cpu &cpu, bool &halt, [[maybe_unused]] bool printing) {
    if (!halt) {
        uint16_t dst = cpu.get(type_dst_, dst_);
        uint16_t src = cpu.get(type_src_, src_);
        uint16_t sup = cpu.get(cpu.getLastReg().first, cpu.getLastReg().second);
        uint16_t value = dst + src + sup;
        cpu.set(type_dst_, dst_, value);
        cpu.updateOF(dst, src + sup, value, '+');
        cpu.updateSF(static_cast<short>(value));
        cpu.updateZF(static_cast<short>(value));
        cpu.updateCF(dst, src + sup, '+');
        cpu.setLastReg(type_dst_, dst_);
    }

    cpu.addToIp(size_);
    if (position_ + size_ <= position_)
        return true;
    return false;
}
