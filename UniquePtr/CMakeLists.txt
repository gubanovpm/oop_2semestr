cmake_minimum_required (VERSION 3.0)

project (sh0d4n_UniquePtr VERSION 1.0)


set (EXEC_FILE "main")

set (SOURCES
    sources/main.cc
)

set (HEADERS
    include/unique_ptr.hh
)

add_executable(${EXEC_FILE} ${SOURCES})

target_include_directories(${EXEC_FILE} PRIVATE include)

set (COMPILER_SETTINGS
    -std=c++2a
    -Wall
    -Wextra
    -Wpedantic

    -Wsign-promo
    -Wsign-conversion
    -Wdouble-promotion

    -Wfloat-equal
    -Wbool-compare

    -Wdiv-by-zero

    -O2
)

target_compile_options(${EXEC_FILE} PRIVATE ${COMPILER_SETTINGS})
