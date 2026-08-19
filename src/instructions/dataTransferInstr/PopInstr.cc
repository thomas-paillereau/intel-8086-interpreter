#include "PopInstr.hh"

#include "utils/Utils.hh"

PopInstr::PopInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "pop";
    position_ = position;

    uint8_t curr1 = content.at(position);

    if (curr1 == 0b10001111) {
        uint8_t curr2 = content.at(position + 1);

        effect_ = 0;
        size_ = 2;

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
    } else if (0b01011000 <= curr1 && curr1 <= 0b01011111) {
        effect_ = 1;
        size_ = 1;
        reg_ = Utils::getIntervalNumFromByte(curr1, 2, 0);
    } else {
        effect_ = 2;
        size_ = 1;
        two_bits_reg_ = true;
        reg_ = Utils::getIntervalNumFromByte(curr1, 4, 3);
    }

    // POP only takes 16-bit operands
    w_ = true;
}
