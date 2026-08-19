#include "CmpInstr.hh"

#include "utils/Utils.hh"

CmpInstr::CmpInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "cmp";
    position_ = position;

    uint8_t curr1 = content.at(position);

    w_ = Utils::getEnabledBitFromByte(curr1, 0);
    if (0b00111000 <= curr1 && curr1 <= 0b00111011) {
        effect_ = 0;
        size_ = 2;
        d_ = Utils::getEnabledBitFromByte(curr1, 1);
    } else if (0b10000000 <= curr1 && curr1 <= 0b10000011) {
        effect_ = 1;
        size_ = 2;
        s_ = Utils::getEnabledBitFromByte(curr1, 1);
    } else {
        effect_ = 2;
        size_ = 1;
    }

    if (effect_ == 0 || effect_ == 1) {
        uint8_t curr2 = content.at(position + 1);
        mod_ = Utils::getIntervalNumFromByte(curr2, 7, 6);
        rm_ = Utils::getIntervalNumFromByte(curr2, 2, 0);
        if (effect_ == 0)
            reg_ = Utils::getIntervalNumFromByte(curr2, 5, 3);

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

    if (effect_ == 1 || effect_ == 2) {
        imm_low_ = content.at(position + size_);
        size_++;
        if (!s_ && w_) {
            imm_high_ = content.at(position + size_);
            size_++;
        }
    }
}
