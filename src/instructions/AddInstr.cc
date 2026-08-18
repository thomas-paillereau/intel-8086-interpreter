#include "AddInstr.hh"
#include "../utils/Utils.hh" // TODO change CMakeLists to do better utils integration

AddInstr::AddInstr(int position, std::vector<uint8_t> &content) {
    uint8_t curr = content.at(position);
    if (curr < 0b100)
        type_ = 0;
    else if (curr < 0b1000)
        type_ = 2;
    else
        type_ = 3;

    w_ = Utils::getEnabledBitFromByte(curr, 0);
    if (type_ == 0)
        d_ = Utils::getEnabledBitFromByte(curr, 1);
    if (type_ == 1)
        s_ = Utils::getEnabledBitFromByte(curr, 1);

    if (type_ != 2) {
        mod_ = Utils::getIntervalNumFromByte(content.at(position + 1), 7, 6);
        rnm_ = Utils::getIntervalNumFromByte(content.at(position + 1), 5, 3);
        if (type_ == 0)
            reg_ = Utils::getIntervalNumFromByte(content.at(position + 1), 2, 0);
    }

    if (type_ == 1) {
        data_ = content.at(position + 2);
        if (w_)
            data2_ = content.at(position + 3);
    }

    if (type_ == 2) {
        data_ = content.at(position + 1);
        if (w_)
            data2_ = content.at(position + 2);
    }
}

std::string AddInstr::toString() {
    return Instruction::toString() + "Add";
}
