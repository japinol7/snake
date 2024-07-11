#include <iostream>
#include <string>

#include "src/arguments_parser/arguments_parser.hpp"
#include <src/config/constants.hpp>
#include "src/tools/logger/logger.hpp"
#include "src/controller/controller.hpp"
#include "src/renderer/renderer.hpp"
#include "src/services/resource_manager/resource_manager.hpp"
#include "game.hpp"

int main(int argc, char *argv[]) {
    bool exit_app = false;
    try {
        exit_app = app_options::Parse(argc, argv);
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n' << kAppCLIArgumentsUsage;
        return EXIT_FAILURE;
    }
    if (exit_app)
        return EXIT_FAILURE;

    Log("%s", kLogMsgAppStart.c_str());
    ResourceManager resource_manager;
    Renderer renderer(kScreen_width, kScreen_height,
                      app_options::GridWidth(), app_options::GridHeight(),
                      resource_manager);
    EventController controller;

    Game game(app_options::GridWidth(), app_options::GridHeight());
    game.Run(controller, renderer, kMs_per_frame);

    game.LogGameEndToFile();
    Log("%s", kLogMsgAppEnd.c_str());
    return EXIT_SUCCESS;
}
