#include "SarInstr.hh"

#include "utils/Utils.hh"

SarInstr::SarInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "sar";
    position_ = position;
    size_ = 2;

    uint8_t curr1 = content.at(position);
    uint8_t curr2 = content.at(position + 1);

    w_ = Utils::getEnabledBitFromByte(curr1, 0);
    v_ = Utils::getEnabledBitFromByte(curr1, 1);
    v_used_ = true;

    mod_ = Utils::getIntervalNumFromByte(curr2, 7, 6);
    rm_ = Utils::getIntervalNumFromByte(curr2, 2, 0);

    addInfoBytes(content, position);
}

bool SarInstr::execute(Cpu &cpu, bool &halt, [[maybe_unused]] bool printing) {
    if (!halt) {
        auto dst = static_cast<short>(cpu.get(type_dst_, dst_));
        auto src = static_cast<short>(cpu.get(type_src_, src_));

        bool cf = false;
        for (short i = 0; i < src; i++) {
            cf = (dst & 1) != 0;
            dst >>= 1;
            dst += static_cast<short>((dst >> 14) << 15);
        }
        cpu.set(type_dst_, dst_, dst);
        cpu.setFlag(Cpu::CF, cf);
        cpu.updateSF(dst);
        cpu.updateZF(dst);
        cpu.setLastReg(type_dst_, dst_);
    }

    cpu.addToIp(size_);
    if (position_ + size_ <= position_)
        return true;
    return false;
}
