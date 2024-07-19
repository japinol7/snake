#ifndef JP_CONSTANTS_HPP
#define JP_CONSTANTS_HPP

#include <iostream>

using std::string;

constexpr int kWinWidth = 1280;
constexpr int kWinHeight = 948;
constexpr int kWinHeightBoard = 900;

constexpr unsigned int kGridWidth = 100;
constexpr double kGridRatio = 0.8;
constexpr unsigned int kGridHeight = kGridWidth * kGridRatio;

constexpr int kFps = 60;

constexpr int kOneSecInMs = 1000;

constexpr float kSnakeInitialSpeed = 0.6f;
constexpr int kSnakeInitialBodySize = 5;
constexpr int kSnakeBodySizeToIncrease = 1;
constexpr float kSnakeIncreaseSpeed = 0.02f;
constexpr int kXpApple = 15;

constexpr int kGridWidthMin = 30;
constexpr int kGridWidthMax = 250;
constexpr int kSnakeInitialBodySizeMin = 0;
constexpr int kSnakeInitialBodySizeMax = 50;
constexpr int kSnakeBodySizeToIncreaseMin = 0;
constexpr int kSnakeBodySizeToIncreaseMax = 5;
constexpr float kSnakeInitialSpeedMin = 0.3f;
constexpr float kSnakeInitialSpeedMax = 0.95f;
constexpr float kSnakeSpeedMax = 0.98f;

constexpr bool kSnakeDieWhenBiteOwnTail = true;

constexpr unsigned int kScreen_width{kWinWidth};
constexpr unsigned int kScreen_height{kWinHeightBoard};
constexpr std::size_t kMs_per_frame{1000 / kFps};

constexpr string kAppName = "Snake";
constexpr string kAppVersion = "0.01";
const string kAppNameWithVersion = kAppName + " v. " + kAppVersion;
constexpr string kAppAuthor = "Joan A. Pinol";

const string kLogMsgAppStart = "Start app " + kAppNameWithVersion
    + " dev. in C++" + " by " + kAppAuthor + "\n";
const string kLogMsgAppEnd = "End app " + kAppName + "\n";

const string kAppCLIArgumentsUsage = ""
    "usage: app [-h  help]\n"
    "\t[-g  cells-width-qty] QTY\n"
    "\t[-b  body-pieces] QTY\n"
    "\t[-r  body-size-to-increase] QTY\n"
    "\t[-s  snake-speed] QTY\n"
     ;

const string kGameLogSeparator = "...........................................\n";
constexpr string kOutputScoreFileName = "snake_score.txt";

const char *const kFileNameImgBackground = "assets/img/backgrounds/background_11.png";
const char *const kFileNameImgScoreZone = "assets/img/backgrounds/score_zone.png";
const char *const kFileNameImgLogoJp = "assets/img/logos/logo_japinol_ld.png";

#endif
