#include "IntInstr.hh"

IntInstr::IntInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "int";
    uint8_t curr1 = content.at(position);
    if (0b11001101 == curr1) {
        effect_ = 0;
        size_ = 2;
        type_ = content.at(position + 1);
        type_used_ = true;
    } else {
        effect_ = 1;
        size_ = 1;
    }
}
