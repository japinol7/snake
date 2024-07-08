#ifndef JP_OUTPUT_SCORE_HPP
#define JP_OUTPUT_SCORE_HPP

#include <string>
#include <fstream>
#include <ctime>
#include <memory>

class OutputFileLogger {
public:
    OutputFileLogger();
    ~OutputFileLogger();
    void SaveGameStart();
    void SaveGameEnd(int score, int snake_body_size,
                     int apples_fetched, float snake_speed);

private:
    std::ofstream out_file;
    static std::string GetCurrentDateTime();
};

#endif
