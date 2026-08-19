#include "InInstr.hh"

#include "utils/Utils.hh"

InInstr::InInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "in";
    position_ = position;

    uint8_t curr1 = content.at(position_);

    w_ = Utils::getEnabledBitFromByte(curr1, 0);
    if (0b11100100 == curr1 || 0b11100101 == curr1) {
        effect_ = 0;
        size_ = 2;
        info_byte_type_ = PORT;
        imm_low_ = content.at(position + 1);
    } else {
        effect_ = 1;
        size_ = 1;
    }
}
