#include "IntInstr.hh"

IntInstr::IntInstr(const std::vector<uint8_t> &content, int position) {
    uint8_t curr1 = content.at(position);
    if (0b11001101 == curr1) {
        type_ = 0;
        size_ = 2;
        reg_type_ = content.at(position + 1);
    } else {
        type_ = 1;
        size_ = 1;
    }
}

std::string IntInstr::toString() const {
    return "int";
}
