#include "AddInstr.hh"

#include <ios>

#include "utils/Utils.hh"

AddInstr::AddInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "add";
    position_ = position;

    uint8_t curr1 = content.at(position);
    uint8_t curr2 = content.at(position + 1);

    if (curr1 <= 0b00000011) {
        effect_ = 0;
        size_ = 2;
    } else if (0b10000000 <= curr1 && curr1 <= 0b10000011) {
        effect_ = 1;
        size_ = 2;
        info_byte_type_ = DATA;
    } else if (0b00000100 <= curr1 && curr1 <= 0b00000101) {
        effect_ = 2;
        size_ = 1;
        info_byte_type_ = DATA;
    }

    w_ = Utils::getEnabledBitFromByte(curr1, 0);

    if (effect_ == 0)
        d_ = Utils::getEnabledBitFromByte(curr1, 1);

    if (effect_ == 1)
        s_ = Utils::getEnabledBitFromByte(curr1, 1);

    if (effect_ == 0 || effect_ == 1) {
        mod_ = Utils::getIntervalNumFromByte(curr2, 7, 6);
        reg_ = Utils::getIntervalNumFromByte(curr2, 5, 3);
        rm_ = Utils::getIntervalNumFromByte(curr2, 2, 0);

        if ((mod_ == 0b00 && rm_ == 0b110) || (mod_ == 0b10)) {
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
        size_ += 1;
        if (w_ && !s_) {
            imm_high_ = content.at(position + size_);
            size_ += 1;
        }
    }
}
