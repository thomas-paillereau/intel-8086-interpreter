#include "PushInstr.hh"

#include "utils/Utils.hh"

PushInstr::PushInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "push";
    position_ = position;

    uint8_t curr1 = content.at(position);

    if (curr1 == 0b11111111) {
        uint8_t curr2 = content.at(position + 1);
        effect_ = 0;
        size_ = 2;
        mod_ = Utils::getIntervalNumFromByte(curr2, 7, 6);
        rm_ = Utils::getIntervalNumFromByte(curr2, 2, 0);
    } else if (0b01010000 <= curr1 && curr1 <= 0b01010111) {
        effect_ = 1;
        size_ = 1;
        reg_ = Utils::getIntervalNumFromByte(curr1, 2, 0);
    } else {
        effect_ = 3;
        size_ = 1;
        two_bits_reg_ = true;
        reg_ = Utils::getIntervalNumFromByte(curr1, 4, 3);
    }
    addInfoBytes(content, position);


    // PUSH only takes 16bit registers
    w_ = true;
}
