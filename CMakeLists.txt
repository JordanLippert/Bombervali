cmake_minimum_required(VERSION 3.25)
project(Game02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(Game02 main.cpp src/Game.h src/Player.h src/enums/GameChar.h src/Bombs.h src/utils/ConsoleColors.h config.h src/utils/StringUtils.h src/Enemies.h src/Menu.h src/enums/GameStage.h)
