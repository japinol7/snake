cmake_minimum_required(VERSION 3.28)
project(snake)

set(CMAKE_CXX_STANDARD 20)

set(JP_PRJ_RUN_NAME "snake")
set(JP_PRJ_PATH "snake")
set(JP_PRJ_SRC ${JP_PRJ_PATH}/src)

set(JP_LIB_PATH "D:/dev/libs")

# Add SDL2 library
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH ${JP_LIB_PATH}"/sdl2/SDL2-2.30.4/x86_64-w64-mingw32")
set(SDL2_IMAGE_PATH ${JP_LIB_PATH}"/sdl_image_2/SDL2_image-2.8.2/x86_64-w64-mingw32")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})

# Add SDL project
add_executable(${JP_PRJ_RUN_NAME}
        ${JP_PRJ_SRC}/main.cpp
        ${JP_PRJ_SRC}/arguments_parser/arguments_parser.cpp
        ${JP_PRJ_SRC}/game.cpp
        ${JP_PRJ_SRC}/controller/controller.cpp
        ${JP_PRJ_SRC}/tools/utils/utils.cpp
        ${JP_PRJ_SRC}/tools/logger/logger.cpp
        ${JP_PRJ_SRC}/output_file_logger/output_file_logger.cpp
        ${JP_PRJ_SRC}/renderer/renderer.cpp
        ${JP_PRJ_SRC}/entities/apple.cpp
        ${JP_PRJ_SRC}/entities/snake.cpp
)
include_directories(${JP_PRJ_PATH})
add_subdirectory(${JP_PRJ_PATH})
target_link_libraries(${JP_PRJ_RUN_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
