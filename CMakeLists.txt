cmake_minimum_required(VERSION 3.15)
project(ESISAR_CS211_TP4 C)

set(CMAKE_C_STANDARD 99)


file(
        GLOB_RECURSE
        source_files
        src/*
)

add_executable(ESISAR_CS211_TP4 main.c ${source_files})
