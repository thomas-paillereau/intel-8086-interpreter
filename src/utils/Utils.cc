#include "Utils.hh"

int Utils::getIntervalNumFromByte(uint8_t n, int left, int right) {
    int width = left - right + 1;
    uint8_t mask = (1 << width) - 1;
    return (n >> right) & mask;
}

bool Utils::getEnabledBitFromByte(uint8_t n, int pos) {
    return (n & (1 << pos)) != 0;
}
