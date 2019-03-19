cmake_minimum_required(VERSION 3.8)
project(E03)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        cammino.txt
        labirinto.txt
        main.c)

add_executable(E03 ${SOURCE_FILES})