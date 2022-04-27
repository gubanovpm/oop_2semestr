cmake_minimum_required (VERSION 3.9)

project ("SkillTree" VERSION 1.0)

find_package(SFML 2.5 COMPONENTS 
                graphics 
                window 
                system 
                REQUIRED)

set (EXEC_FILE "skill_tree.exe")

set (SOURCES
    sources/Node.cc
    sources/main.cc
    sources/HitNode.cc
    sources/AccumulateNode.cc
    sources/AbstructSkillTree.cc
)

add_executable(${EXEC_FILE} ${SOURCES})

target_include_directories(${EXEC_FILE} PRIVATE include)
target_link_libraries(${EXEC_FILE} 
                        sfml-graphics 
                        sfml-window 
                        sfml-system
                     )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

target_compile_options(${EXEC_FILE} PRIVATE ${COMPILER_SETTINGS})