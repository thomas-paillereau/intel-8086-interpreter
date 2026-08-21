#include "JnleJgInstr.hh"

JnleJgInstr::JnleJgInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "jnle";
    position_ = position;
    size_ = 2;
    imm_low_ = content.at(position + 1);
    info_byte_type_ = DISP;
}
