#include "AndInstr.hh"

#include "utils/Utils.hh"

AndInstr::AndInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "and";
    position_ = position;

    uint8_t curr1 = content.at(position);
    w_ = Utils::getEnabledBitFromByte(curr1, 0);
    if (0b00100000 <= curr1 && curr1 <= 0b00100011) {
        effect_ = 0;
        size_ = 2;
        d_ = Utils::getEnabledBitFromByte(curr1, 1);
    } else if (0b10000000 <= curr1 && curr1 <= 0b10000001) {
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
