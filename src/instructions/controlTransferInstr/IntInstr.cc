#include "IntInstr.hh"

#include <iomanip>
#include <iostream>

IntInstr::IntInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "int";
    position_ = position;
    uint8_t curr1 = content.at(position);
    if (0b11001101 == curr1) {
        effect_ = 0;
        size_ = 2;
        imm_low_ = content.at(position + 1);
        info_byte_type_ = TYPE;
    } else {
        effect_ = 1;
        size_ = 1;
    }
}

bool IntInstr::execute(Cpu &cpu, bool &halt, bool printing) {
    auto lastReg = cpu.getLastReg();
    uint16_t index = cpu.get(lastReg.first, lastReg.second);
    uint16_t type = cpu.get(type_dst_, dst_);

    halt = false;
    cpu.setReg16(Cpu::AX, 0);

    if (type != 0x20)
        return false;

    uint16_t sys_type = cpu.getMem8(index + 3) * 256 + cpu.getMem8(index + 2);
    uint16_t fd = cpu.getMem16(index + 4);
    uint16_t len = cpu.getMem16(index + 6);
    uint16_t coords = cpu.getMem16(index + 10);

    bool result = false;

    if (sys_type == 1) {
        if (printing)
            std::cout << "<exit(" << std::dec << fd << ")>" << std::endl;
        result = true;
    } else if (sys_type == 4) {
        uint8_t *textData = cpu.getMemory().data() + coords;
        if (printing)
            printf("<write(%i, 0x%04hx, %i)", fd, coords, len);
        fflush(nullptr);
        write(fd, textData, len);
        if (printing)
            printf(" => %i>\n", len);
        cpu.setMem16(index + 2, len);
    } else if (sys_type == 17) {
        uint16_t addr = cpu.getMem16(index + 10);
        if (printing)
            printf("<brk(0x%04hx) => 0>\n", addr);
        cpu.setMem16(index + 2, 0);
        cpu.setMem16(index + 18, addr);
    } else if (sys_type == 54) {
        errno = EINVAL;
        uint16_t value1 = cpu.getMem8(index + 9) * 256 + cpu.getMem8(index + 8);
        uint16_t value2 = cpu.getMem16(index + 19) * 256 + cpu.getMem16(index + 18);
        if (printing)
            printf("<ioctl(%i, 0x%04hx, 0x%04hx)>\n", fd, value1, value2);
        cpu.setMem16(index + 2, -errno);
    } else {
        result = true; // TODO make error
    }
    fflush(nullptr);

    if (result)
        return true;

    cpu.setLastReg(type_dst_, dst_);
    cpu.addToIp(size_);
    if (position_ + size_ <= position_)
        return true;
    return false;
}
