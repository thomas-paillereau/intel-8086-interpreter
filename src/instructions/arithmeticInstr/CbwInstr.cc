#include "CbwInstr.hh"

CbwInstr::CbwInstr([[maybe_unused]] const std::vector<uint8_t> &content, int position) {
    name_ = "cbw";
    position_ = position;
}
