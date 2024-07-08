#ifndef JP_COLORS_HPP
#define JP_COLORS_HPP

#include <tuple>

enum class Color {
    kAqua = 0x00FFFF,
    kBeige = 0xF5F5DC,
    kBlack = 0x000000,
    kBlackSafe = 0x0A0A0A,
    kBlue = 0x0000FF,
    kBlueLight = 0x0053FF,
    kBrown = 0xA52A2A,
    kCoral = 0xFF7F50,
    kCyan = 0x00FFFF,
    kGrayDark = 0xA9A9A9,
    kGrayLight = 0xD3D3D3,
    kGold = 0xFFD700,
    kGray = 0x808080,
    kGreen = 0x00FF00,
    kFuchsia = 0xFF00FF,
    kIndigo = 0x4B0082,
    kLavender = 0xE6E6FA,
    kLime = 0x00FF00,
    kMagenta = 0xFF00FF,
    kMaroon = 0x800000,
    kMint = 0x98FF98,
    kNavy = 0x000080,
    kOlive = 0x808000,
    kOrange = 0xFFA500,
    kOrchid = 0xDA70D6,
    kPink = 0xFFC0CB,
    kPlum = 0xDDA0DD,
    kPurple = 0x800080,
    kRed = 0xFF0000,
    kRedDark = 0x6F0000,
    kRoyalblue = 0x4169E1,
    kSalmon = 0xFA8072,
    kSeagreen = 0x2E8B57,
    kSilver = 0xC0C0C0,
    kSkyblue = 0x87CEEB,
    kSlateblue = 0x6A5ACD,
    kSlategray = 0x708090,
    kTan = 0xD2B48C,
    kTeal = 0x008080,
    kTurquoise = 0x40E0D0,
    kTomato = 0xFF6347,
    kViolet = 0xEE82EE,
    kYellow = 0xFFFF00,
    kWhite = 0xFFFFFF,
};

std::tuple<int, int, int> HexToRGB(int hexValue);

#endif
