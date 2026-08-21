#include "CwdInstr.hh"

CwdInstr::CwdInstr([[maybe_unused]] const std::vector<uint8_t> &content, int position) {
    name_ = "cwd";
    position_ = position;
}
