#include <tuple>

#include "colors.hpp"

std::tuple<int, int, int> HexToRGB(int hexValue) {
    int r = (hexValue >> 16) & 0xFF;
    int g = (hexValue >> 8) & 0xFF;
    int b = hexValue & 0xFF;
    return std::make_tuple(r, g, b);
};
