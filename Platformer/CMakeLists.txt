cmake_minimum_required(VERSION 3.4.0)
project(player_movement)

find_package(SFML 2.5 COMPONENTS
                graphics 
                window 
                system
            REQUIRED)

set (EXEC_FILE "player_movement.exe")

set (SOURCES 
            sources/main.cc
            sources/player.cc
            sources/player_states.cc
    )

add_executable(${EXEC_FILE} ${SOURCES})
target_include_directories(${EXEC_FILE} PRIVATE include)

target_compile_features(${EXEC_FILE} PRIVATE cxx_std_20)

target_link_libraries(${EXEC_FILE} PRIVATE
                        sfml-graphics
                        sfml-system
                        sfml-window
                    )

set (COMPILER_SETTINGS
    -O2
)

target_compile_options(${EXEC_FILE} PRIVATE ${COMPILER_SETTINGS})