cmake_minimum_required(VERSION 3.25)
project(Game02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(Game02 main.cpp src/Game.h src/entities/Player.h src/enums/GameChar.h src/entities/Bombs.h src/utils/ConsoleColors.h src/utils/StringUtils.h src/entities/Enemies.h src/Menu.h src/enums/GameStage.h src/GameStatistics.h src/utils/TimeFormat.h src/map/utils/MapRender.h src/map/GameMap.h src/utils/Vector.h src/map/utils/MapReader.h src/utils/Path.h src/managers/MapManager.h src/map/utils/MapLoader.h src/enums/PowerupType.h src/managers/GameStageManager.h src/map/PlayerLocation.h src/entities/Consumables.h src/enums/MenuOptionType.h src/MenuOptions.h src/save/SaveSystem.h src/save/utils/SaveWriter.h src/entities/Save.h src/enums/ConsumableType.h)
