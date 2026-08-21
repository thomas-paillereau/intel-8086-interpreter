#include "JmpInstr.hh"

#include "utils/Utils.hh"

JmpInstr::JmpInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "jmp";
    position_ = position;

    uint8_t curr1 = content.at(position);

    w_ = true;
    if (0b11101001 == curr1) {
        effect_ = 0;
        size_ = 1;
        info_byte_type_ = DISP_HL;
    } else if (0b11101011 == curr1) {
        effect_ = 1;
        name_ += " short";
        w_ = false;
        size_ = 1;
        info_byte_type_ = DISP;
    } else if (0b11111111 == curr1
               && Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3) == 0b100) {
        effect_ = 2;
        size_ = 2;
    } else if (0b11101010 == curr1) {
        effect_ = 3;
        size_ = 1;
        info_byte_type_ = OFFSET_HL;
    } else {
        effect_ = 4;
        size_ = 2;
    }

    if (effect_ == 2 || effect_ == 4) {
        uint8_t curr2 = content.at(position + 1);
        mod_ = Utils::getIntervalNumFromByte(curr2, 7, 6);
        rm_ = Utils::getIntervalNumFromByte(curr2, 2, 0);
    }

    addInfoBytes(content, position);
}
