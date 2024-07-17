#ifndef JP_APP_ARGUMENTS_PARSER_HPP
#define JP_APP_ARGUMENTS_PARSER_HPP

namespace app_options {
    bool parse(int argc, char *argv[]);

    bool isFullScreen();

    unsigned int gridWidth();

    unsigned int gridHeight();

    int snakeInitialBodySize();

    int snakeBodySizeToIncrease();

    float snakeInitialSpeed();

    void checkHasArgumentLeft(int argc, int i);
};

#endif
