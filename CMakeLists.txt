cmake_minimum_required(VERSION 3.2)
project(Mineswheeper)

set(CMAKE_C_FLAGS "-g -pedantic -Wall -Wextra -Werror -Wpedantic -Wno-unused")

set(APP_NAME "minesweeper")
add_executable(
    ${APP_NAME}
    src/main.c
    src/minesweeper_game.c
    src/terminal_frontend.c
    src/util.c)

target_include_directories(${APP_NAME} PUBLIC include)
