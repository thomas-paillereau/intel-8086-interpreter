#include "AddInstr.hh"
#include "../utils/Utils.hh" // TODO change CMakeLists to do better utils integration

AddInstr::AddInstr(const std::vector<uint8_t> &content, int position) {
    uint8_t curr1 = content.at(position);
    uint8_t curr2 = content.at(position + 1);
    if (curr1 <= 0b00000011) {
        type_ = 0;
        size_ = 2;
    } else if (0b10000000 <= curr1 && curr1 <= 0b10000011) {
        type_ = 1;
        size_ = 4;
    } else {
        type_ = 3;
        size_ = 3;
    }

    w_ = Utils::getEnabledBitFromByte(curr1, 0);
    if (type_ == 0)
        d_ = Utils::getEnabledBitFromByte(curr1, 1);
    if (type_ == 1)
        s_ = Utils::getEnabledBitFromByte(curr1, 1);

    if (type_ != 2) {
        mod_ = Utils::getIntervalNumFromByte(curr2, 7, 6);
        rnm_ = Utils::getIntervalNumFromByte(curr2, 5, 3);
        if (type_ == 0)
            reg_ = Utils::getIntervalNumFromByte(curr2, 2, 0);
    }

    if (type_ == 1) {
        data_ = content.at(position + 2);
        if (w_)
            data2_ = content.at(position + 3);
    }

    if (type_ == 2) {
        data_ = content.at(position + 1);
        if (w_)
            data2_ = content.at(position + 2);
    }
}

std::string AddInstr::toString() const {
    return "add";
}
