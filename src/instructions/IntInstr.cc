#include "IntInstr.hh"

IntInstr::IntInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "int";
    position_ = position;
    uint8_t curr1 = content.at(position);
    if (0b11001101 == curr1) {
        effect_ = 0;
        size_ = 2;
        info_byte1_ = content.at(position + 1);
        info_byte_type_ = TYPE;
    } else {
        effect_ = 1;
        size_ = 1;
    }
}
