#include "NegInstr.hh"

#include "utils/Utils.hh"

NegInstr::NegInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "neg";
    position_ = position;
    size_ = 2;
    padding_ = 0;
    uint8_t curr1 = content.at(position);
    uint8_t curr2 = content.at(position + 1);
    w_ = Utils::getEnabledBitFromByte(curr1, 0);
    mod_ = Utils::getIntervalNumFromByte(curr2, 7, 6);
    rm_ = Utils::getIntervalNumFromByte(curr2, 2, 0);

    addInfoBytes(content, position);
}

bool NegInstr::execute(Cpu &cpu, bool &halt, [[maybe_unused]] bool printing) {
    if (!halt) {
        auto dst = static_cast<short>(cpu.get(type_dst_, dst_));
        auto value = static_cast<short>(-dst);
        cpu.set(type_dst_, dst_, value);
        cpu.updateSF(value);
        cpu.updateZF(value);
        cpu.setFlag(Cpu::OF, dst == static_cast<short>(0x8000));
        cpu.setFlag(Cpu::CF, dst != 0);
        cpu.setLastReg(type_dst_, dst_);
    }
    
    cpu.addToIp(size_);
    if (position_ + size_ <= position_)
        return true;
    return false;
}
