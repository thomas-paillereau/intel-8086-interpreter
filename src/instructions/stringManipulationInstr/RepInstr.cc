#include "RepInstr.hh"

#include "utils/Utils.hh"
#include "disassembler/Disassembler.hh"

RepInstr::RepInstr(const std::vector<uint8_t> &content, int position) {
    name_ = "rep";
    position_ = position;
    size_ = 1;
    z_ = Utils::getEnabledBitFromByte(content.at(position_), 0);

    Disassembler disassembler = Disassembler(content, position, 0x20); //TODO make disassembler static
    std::unique_ptr<Instruction> instr = disassembler.disassembleInstruction(position + 1);
    // TODO add stoking of instruction
    name_ += " " + instr->toString();
    size_ += instr->getSize();
}
