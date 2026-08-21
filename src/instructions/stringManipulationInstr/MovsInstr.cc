#include "MovsInstr.hh"

#include "utils/Utils.hh"

MovsInstr::MovsInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "movs";
    position_ = position;
    size_ = 1;
    w_ = Utils::getEnabledBitFromByte(content.at(position_), 0);
    name_ += w_ ? "w" : "b";
}
