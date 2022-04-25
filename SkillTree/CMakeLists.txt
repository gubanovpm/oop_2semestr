cmake_minimum_required (VERSION 3.9)

project ("SkillTree" VERSION 1.0)

find_package(SFML 2.5 COMPONENTS 
                graphics 
                window 
                system 
                REQUIRED)

set (EXEC_FILE "skill_tree.exe")

set (SOURCES
    sources/skilltree.cpp
)

add_executable(${EXEC_FILE} ${SOURCES})

target_include_directories(${EXEC_FILE} PRIVATE include)
target_link_libraries(${EXEC_FILE} 
                        sfml-graphics 
                        sfml-window 
                        sfml-system
                     )

set (COMPILER_SETTINGS
    -std=c++2a
    -O2
)

target_compile_options(${EXEC_FILE} PRIVATE ${COMPILER_SETTINGS})