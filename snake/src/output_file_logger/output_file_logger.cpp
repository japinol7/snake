#include <iostream>
#include <ctime>

#include "src/arguments_parser/arguments_parser.hpp"
#include "src/config/constants.hpp"
#include "src/tools/logger/logger.hpp"
#include "output_file_logger.hpp"

OutputFileLogger::OutputFileLogger() {
    std::string fileName = kOutputScoreFileName;
    out_file.open(fileName, std::ios::app);

    if (!out_file.is_open())
        std::cerr << "ERROR: Unable to write to file: " << fileName << std::endl;
}

OutputFileLogger::~OutputFileLogger() {
    if (out_file.is_open()) {
        out_file.close();
    }
}

void OutputFileLogger::SaveGameStart() {
    if (!out_file.is_open())
        return;

    out_file << kGameLogSeparator;
    out_file << GetCurrentDateTime() << " " << kLogMsgAppStart.c_str()
             << "Screen size in pixels: " << kWinWidth << " * " << kWinHeight << "\n"
             << "Screen size minus the score bar: " << kWinWidth << " * " << kWinHeightBoard << "\n"
        << "Screen cells horizontal qty: " << app_options::GridWidth() << "\n"
        << "Screen cells vertical qty: " << app_options::GridHeight() << "\n"
        << "Snake initial body size: " << app_options::SnakeInitialBodySize() << "\n"
        << "Snake body size to increase: " << app_options::SnakeBodySizeToIncrease() << "\n"
        << "Snake initial speed: " << app_options::SnakeInitialSpeed() << "\n";
    out_file.flush();
}

void OutputFileLogger::SaveGameEnd(
        int score, int snake_body_size, int apples_fetched,
        float snake_speed) {
    if (!out_file.is_open())
        return;

    Log("%s", "Save game stats to file");
    out_file << "\n" << GetCurrentDateTime() << " " << kLogMsgAppEnd.c_str();
    out_file << "Score: " << score << "\n"
        << "Apples fetched: " << apples_fetched << "\n"
        << "Snake body size: " << snake_body_size << "\n"
        << "Snake speed: " << snake_speed << "\n"
        << "End game reason: " << "--" << "\n"
        << kGameLogSeparator << ".\n";
    out_file.flush();
}

std::string OutputFileLogger::GetCurrentDateTime() {
    time_t now = time(nullptr);
    char buf[80];
    struct tm t_struct{*localtime(&now)};

    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &t_struct);
    return buf;
}
