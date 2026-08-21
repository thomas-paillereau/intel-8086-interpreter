#include "DivInstr.hh"

#include "utils/Utils.hh"

DivInstr::DivInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "div";
    position_ = position;
    size_ = 2;
    padding_ = 0;
    uint8_t curr1 = content.at(position);
    uint8_t curr2 = content.at(position + 1);
    w_ = Utils::getEnabledBitFromByte(curr1, 0);
    mod_ = Utils::getIntervalNumFromByte(curr2, 7, 6);
    rm_ = Utils::getIntervalNumFromByte(curr2, 2, 0);

    addInfoBytes(content, position);
}
