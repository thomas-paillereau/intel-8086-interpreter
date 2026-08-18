#pragma once

#include <cstdint>

class Utils {
public:
    static int getIntervalNumFromByte(uint8_t n, int left, int right);

    static bool getEnabledBitFromByte(uint8_t n, int pos);
};
