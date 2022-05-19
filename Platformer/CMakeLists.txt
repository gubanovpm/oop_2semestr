cmake_minimum_required(VERSION 3.4.0)
project(player_movement)

# Найдём библиотеку SFML в системе
find_package(SFML 2.5 COMPONENTS
                graphics 
                window 
                system
            REQUIRED)

set (EXEC_FILE "player_movement.exe")

set (SOURCES 
            sources/main.cpp
            sources/player.cpp
            sources/player_states.cpp
    )

add_executable(${EXEC_FILE} ${SOURCES})
target_include_directories(${EXEC_FILE} PRIVATE include)

# Укажем, что нужно использовать стандарт C++20
target_compile_features(${EXEC_FILE} PRIVATE cxx_std_20)

# Подключим библиотеку SFML к нашему проекту
target_link_libraries(${EXEC_FILE} PRIVATE
                        sfml-graphics
                        sfml-system
                        sfml-window
                    )
