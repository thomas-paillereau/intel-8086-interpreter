#include "MovInstr.hh"
#include "../utils/Utils.hh"

MovInstr::MovInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "mov";
    uint8_t curr1 = content.at(position);
    uint8_t curr2 = content.at(position + 1);
    if (0b10001000 <= curr1 && curr1 <= 0b10001011) {
        effect_ = 0;
        size_ = 2;
    } else if (0b11000110 <= curr1 && curr1 <= 0b11000111) {
        effect_ = 1;
        size_ = 4;
        data_used_ = true;
    } else if (0b10110000 <= curr1 && curr1 <= 0b10111111) {
        effect_ = 2;
        size_ = 3;
        data_used_ = true;
    } else if (0b10100000 <= curr1 && curr1 <= 0b10100001) {
        effect_ = 3;
        size_ = 3;
        addr_used_ = true;
    } else if (0b10100010 <= curr1 && curr1 <= 0b10100011) {
        effect_ = 4;
        size_ = 3;
        addr_used_ = true;
    } else if (curr1 == 0b10001110) {
        effect_ = 5;
        size_ = 2;
    } else {
        effect_ = 6;
        size_ = 2;
    }

    if (effect_ == 0 || effect_ == 1 || effect_ == 3 || effect_ == 4)
        w_ = Utils::getEnabledBitFromByte(curr1, 0);
    else if (effect_ == 2)
        w_ = Utils::getEnabledBitFromByte(curr1, 3);

    if (effect_ == 0)
        d_ = Utils::getEnabledBitFromByte(curr1, 1);

    if (effect_ == 0)
        reg_ = Utils::getIntervalNumFromByte(curr2, 5, 3);
    else if (effect_ == 2)
        reg_ = Utils::getIntervalNumFromByte(curr1, 2, 0);
    else if (effect_ == 5 || effect_ == 6)
        reg_ = Utils::getIntervalNumFromByte(curr2, 4, 3);
    // TODO check for other implication for the instruction (reg of size 2)

    if (effect_ == 0 || effect_ == 1 || effect_ == 5 || effect_ == 6) {
        mod_ = Utils::getIntervalNumFromByte(curr1, 7, 6);
        rnm_ = Utils::getIntervalNumFromByte(curr1, 2, 0);
    }

    if (effect_ == 1) {
        data_ = content.at(position + 2);
        data2_ = content.at(position + 3);
    } else if (effect_ == 2) {
        data_ = content.at(position + 1);
        data2_ = content.at(position + 2);
    }

    if (effect_ == 3 || effect_ == 4) {
        addr_low_ = content.at(position + 1);
        addr_high_ = content.at(position + 2);
    }
}
