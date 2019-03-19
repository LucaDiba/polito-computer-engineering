cmake_minimum_required(VERSION 3.8)
project(E02)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        bin/Debug/E02.exe
        obj/Debug/main.o
        E02.cbp
        E02.depend
        E02.layout
        main.c
        voli.txt)

add_executable(E02 ${SOURCE_FILES})