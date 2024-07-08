#ifndef JP_APP_ARGUMENTS_PARSER_HPP
#define JP_APP_ARGUMENTS_PARSER_HPP

namespace app_options {
    bool Parse(int argc, char *argv[]);

    bool IsFullScreen();

    unsigned int GridWidth();

    unsigned int GridHeight();

    int SnakeInitialBodySize();

    int SnakeBodySizeToIncrease();

    float SnakeInitialSpeed();

    void CheckHasArgumentLeft(int argc, int i);
};

#endif
