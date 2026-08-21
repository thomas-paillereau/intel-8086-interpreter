#include "LeaInstr.hh"

#include "utils/Utils.hh"

LeaInstr::LeaInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "lea";
    position_ = position;

    uint8_t curr2 = content.at(position + 1);

    effect_ = 0;
    size_ = 2;

    mod_ = Utils::getIntervalNumFromByte(curr2, 7, 6);
    reg_ = Utils::getIntervalNumFromByte(curr2, 5, 3);
    rm_ = Utils::getIntervalNumFromByte(curr2, 2, 0);

    addInfoBytes(content, position);

    // Always 16bit instruction
    w_ = true;

    // Lea instructions is always reversed
    d_ = true;
}
