#include "StdInstr.hh"

StdInstr::StdInstr([[maybe_unused]] const std::vector<uint8_t> &content, int position) {
    name_ = "std";
    position_ = position;
}
