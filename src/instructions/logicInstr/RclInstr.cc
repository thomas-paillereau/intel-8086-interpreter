#include "RclInstr.hh"

#include "utils/Utils.hh"

RclInstr::RclInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "rcl";
    position_ = position;
    size_ = 2;

    uint8_t curr1 = content.at(position);
    uint8_t curr2 = content.at(position + 1);

    w_ = Utils::getEnabledBitFromByte(curr1, 0);
    v_ = Utils::getEnabledBitFromByte(curr1, 1);
    v_used_ = true;

    mod_ = Utils::getIntervalNumFromByte(curr2, 7, 6);
    rm_ = Utils::getIntervalNumFromByte(curr2, 2, 0);

    addInfoBytes(content, position);
}
