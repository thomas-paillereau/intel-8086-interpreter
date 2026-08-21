#include "RetInstr.hh"

RetInstr::RetInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "ret";
    position_ = position;

    uint8_t curr1 = content.at(position_);

    if (0b11000011 == curr1) {
        effect_ = 0;
        size_ = 1;
    } else if (0b11000010 == curr1) {
        effect_ = 1;
        size_ = 1;
        w_ = true;
        info_byte_type_ = DATA;
    } else if (0b11001011 == curr1) {
        effect_ = 2;
        size_ = 1;
    } else {
        effect_ = 3;
        size_ = 1;
        w_ = true;
        info_byte_type_ = DATA;
    }

    addInfoBytes(content, position);
}
