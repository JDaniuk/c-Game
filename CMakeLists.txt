cmake_minimum_required(VERSION 3.26)
project(SAMurai)

set(CMAKE_CXX_STANDARD 20)
include(FetchContent)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 10.1.1
)


FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.0
)





FetchContent_MakeAvailable(fmt)
FetchContent_MakeAvailable(sfml)


add_executable(SAMurai main.cpp
        Game.h
        Game.cpp
        Camera.cpp
        Camera.h
        Player.cpp
        Player.h
        GameMap.cpp
        GameMap.h
        enemy.cpp
        enemy.h
        Turret.cpp
        Turret.h
        Projectile.cpp
        Projectile.h
        Level.cpp
        Level.h
)

target_link_libraries(
        SAMurai
        fmt
        sfml-graphics
        sfml-window
        sfml-system
)

IF (WIN32)
    add_custom_command(TARGET SAMurai POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:SAMurai> $<TARGET_FILE_DIR:SAMurai>
            COMMAND_EXPAND_LISTS
    )
ENDIF ()