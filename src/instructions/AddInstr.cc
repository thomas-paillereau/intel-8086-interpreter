#include "AddInstr.hh"
#include "../utils/Utils.hh" // TODO change CMakeLists to do better utils integration

AddInstr::AddInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "add";
    uint8_t curr1 = content.at(position);
    uint8_t curr2 = content.at(position + 1);
    if (curr1 <= 0b00000011) {
        effect_ = 0;
        size_ = 2;
    } else if (0b10000000 <= curr1 && curr1 <= 0b10000011) {
        effect_ = 1;
        size_ = 4;
        info_byte_type_ = DATA;
    } else {
        effect_ = 3;
        size_ = 3;
        info_byte_type_ = DATA;
    }

    w_ = Utils::getEnabledBitFromByte(curr1, 0);
    if (effect_ == 0)
        d_ = Utils::getEnabledBitFromByte(curr1, 1);
    if (effect_ == 1)
        s_ = Utils::getEnabledBitFromByte(curr1, 1);

    if (effect_ != 2) {
        mod_ = Utils::getIntervalNumFromByte(curr2, 7, 6);
        rm_ = Utils::getIntervalNumFromByte(curr2, 5, 3);
        if (effect_ == 0)
            reg_ = Utils::getIntervalNumFromByte(curr2, 2, 0);
    }

    if (effect_ == 1) {
        info_byte1_ = content.at(position + 2);
        if (w_)
            info_byte2_ = content.at(position + 3);
    }

    if (effect_ == 2) {
        info_byte1_ = content.at(position + 1);
        if (w_)
            info_byte2_ = content.at(position + 2);
    }
}
