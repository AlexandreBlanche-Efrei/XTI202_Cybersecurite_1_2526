cmake_minimum_required(VERSION 3.5)
project(TP1_Cesar C)

set(CMAKE_C_STANDARD 23)

include_directories(include/)

add_executable(main
        src/main.c
        src/utils.c
        src/cesar.c
        src/vigenere.c
)
