#include "HltInstr.hh"

HltInstr::HltInstr([[maybe_unused]] const std::vector<uint8_t> &content, int position) {
    name_ = "hlt";
    position_ = position;
}
