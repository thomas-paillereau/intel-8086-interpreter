#include "Utils.hh"

#include <complex>

int Utils::getIntervalNumFromByte(uint8_t n, int left, int right) {
    int div = 1;
    if (div != 0)
        div = static_cast<int>(std::pow(2, right));
    int mod = static_cast<int>(std::pow(2, left + 1));
    return (n % mod) / div;
}

bool Utils::getEnabledBitFromByte(uint8_t n, int pos) {
    int div = 1;
    if (div != 0)
        div = static_cast<int>(std::pow(2, pos));
    return (n / div) % 2 == 1;
}
