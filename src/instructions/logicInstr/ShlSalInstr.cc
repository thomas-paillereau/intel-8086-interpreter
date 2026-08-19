#include "ShlSalInstr.hh"

#include "utils/Utils.hh"

ShlSalInstr::ShlSalInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "shl";
    position_ = position;
    size_ = 2;

    uint8_t curr1 = content.at(position);
    uint8_t curr2 = content.at(position + 1);

    w_ = Utils::getEnabledBitFromByte(curr1, 0);
    v_ = Utils::getEnabledBitFromByte(curr1, 1);
    v_used_ = true;

    mod_ = Utils::getIntervalNumFromByte(curr2, 7, 6);
    rm_ = Utils::getIntervalNumFromByte(curr2, 2, 0);

    if ((mod_ == 0b00 && rm_ == 0b110) || mod_ == 0b10) {
        disp_low_ = content.at(position + size_);
        disp_high_ = content.at(position + size_ + 1);
        size_disp_ = 2;
        size_ += 2;
    } else if (mod_ == 0b01) {
        disp_low_ = content.at(position + size_);
        size_disp_ = 1;
        size_ += 1;
    }
}
