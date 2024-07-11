project(snake_game)

set(HEADER_FILES
        src/arguments_parser/arguments_parser.hpp
        src/output_file_logger/output_file_logger.hpp
        src/controller/controller.hpp
        src/services/resource_manager/resource_manager.cpp
        src/tools/logger/logger.hpp
        src/tools/utils/utils.hpp
        src/game.hpp
        src/renderer/renderer.hpp
        src/entities/apple.hpp
        src/entities/snake.hpp
)

set(SOURCE_FILES
        src/arguments_parser/arguments_parser.cpp
        src/output_file_logger/output_file_logger.cpp
        src/controller/controller.cpp
        src/services/resource_manager/resource_manager.cpp
        src/tools/logger/logger.cpp
        src/tools/utils/utils.cpp
        src/game.cpp
        src/main.cpp
        src/renderer/renderer.cpp
        src/entities/apple.cpp
        src/entities/snake.cpp
)

add_library(snake_game STATIC ${SOURCE_FILES} ${HEADER_FILES})
