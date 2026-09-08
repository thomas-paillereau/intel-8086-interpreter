#include "DivInstr.hh"

#include "utils/Utils.hh"

DivInstr::DivInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "div";
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

bool DivInstr::execute(Cpu &cpu, bool &halt, [[maybe_unused]] bool printing) {
    if (!halt) {
        auto value = static_cast<short>(cpu.get(type_dst_, dst_));
        if (value != 0)
        {
            uint32_t ax = cpu.get(Cpu::REG16, Cpu::AX);
            uint32_t dx = cpu.get(Cpu::REG16, Cpu::DX);
            uint32_t dividend = (dx << 16) | ax;
            uint16_t quotient = dividend / value;
            uint16_t remainder = dividend % value;

            cpu.set(Cpu::REG16, Cpu::AX, quotient);
            cpu.set(Cpu::REG16, Cpu::DX, remainder);
        }
    }

    cpu.addToIp(size_);
    if (position_ + size_ <= position_)
        return true;
    return false;
}
