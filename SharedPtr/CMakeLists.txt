cmake_minimum_required (VERSION 3.0)
project (shared_ptr VERSION 1.0)

set (EXEC_FILE "main.exe")

set (SOURCES
    sources/main.cc
)

set (HEADERS
    include/shared_ptr.hh
)

add_executable(${EXEC_FILE} ${SOURCES})

target_include_directories(${EXEC_FILE} PRIVATE include)

set (COMPILER_SETTINGS
    -std=c++2a
    -O2
)

target_compile_options(${EXEC_FILE} PRIVATE ${COMPILER_SETTINGS})