#include "JbJnaeInstr.hh"

JbJnaeInstr::JbJnaeInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "jb";
    position_ = position;
    size_ = 2;
    imm_low_ = content.at(position + 1);
    info_byte_type_ = DISP;
}
