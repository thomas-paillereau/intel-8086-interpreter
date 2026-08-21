#include "TestInstr.hh"

#include "utils/Utils.hh"

TestInstr::TestInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "test";
    position_ = position;

    uint8_t curr1 = content.at(position);
    w_ = Utils::getEnabledBitFromByte(curr1, 0);
    if (0b10000100 <= curr1 && curr1 <= 0b10000101) {
        effect_ = 0;
        size_ = 2;
    } else if (0b11110110 <= curr1 && curr1 <= 0b11110111) {
        effect_ = 1;
        size_ = 2;
        info_byte_type_ = DATA;
    } else {
        effect_ = 2;
        size_ = 1;
        info_byte_type_ = DATA;
    }

    if (effect_ == 0 || effect_ == 1) {
        uint8_t curr2 = content.at(position + 1);
        mod_ = Utils::getIntervalNumFromByte(curr2, 7, 6);
        rm_ = Utils::getIntervalNumFromByte(curr2, 2, 0);
        if (effect_ == 0)
            reg_ = Utils::getIntervalNumFromByte(curr2, 5, 3);
    }

    addInfoBytes(content, position);
}
