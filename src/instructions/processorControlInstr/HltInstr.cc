#include "HltInstr.hh"

HltInstr::HltInstr([[maybe_unused]] const std::vector<uint8_t> &content, int position) {
    name_ = "hlt";
    position_ = position;
}

bool HltInstr::execute(Cpu &cpu, bool &halt, [[maybe_unused]] bool printing) {
    halt = true;

    cpu.addToIp(size_);
    if (position_ + size_ <= position_)
        return true;
    return false;
}
