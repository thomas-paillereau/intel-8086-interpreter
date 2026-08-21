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
        reg_ = Utils::getIntervalNumFromByte(curr1, 5, 3);
        rm_ = Utils::getIntervalNumFromByte(curr2, 2, 0);
    } else {
        effect_ = 1;
        size_ = 1;
        w_ = true;
        reg_ = Utils::getIntervalNumFromByte(curr1, 2, 0);
    }

    addInfoBytes(content, position);
}
