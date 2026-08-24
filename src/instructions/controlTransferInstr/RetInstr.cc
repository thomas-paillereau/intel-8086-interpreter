#include "RetInstr.hh"

RetInstr::RetInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "ret";
    position_ = position;

    uint8_t curr1 = content.at(position_);

    if (0b11000011 == curr1) {
        effect_ = 0;
        size_ = 1;
    } else if (0b11000010 == curr1) {
        effect_ = 1;
        size_ = 1;
        w_ = true;
        info_byte_type_ = DATA_HL;
    } else if (0b11001011 == curr1) {
        effect_ = 2;
        size_ = 1;
    } else {
        effect_ = 3;
        size_ = 1;
        w_ = true;
        info_byte_type_ = DATA_HL;
    }

    addInfoBytes(content, position);
}

bool RetInstr::execute(Cpu &cpu, [[maybe_unused]] bool printing) {
    uint16_t value = cpu.pop();
    cpu.setIp(value);
    if (type_dst_ != Cpu::type::NONE) {
        auto diff = static_cast<short>(cpu.get(type_dst_, dst_));
        cpu.setReg16(Cpu::SP, static_cast<short>(cpu.getReg16(Cpu::SP) + diff));
    }
    return false;
}
