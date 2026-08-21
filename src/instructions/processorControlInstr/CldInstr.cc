#include "CldInstr.hh"

CldInstr::CldInstr([[maybe_unused]] const std::vector<uint8_t> &content, int position) {
    name_ = "cld";
    position_ = position;
}
