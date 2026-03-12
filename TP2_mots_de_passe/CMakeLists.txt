cmake_minimum_required(VERSION 3.5)
project(TP2_mdp C)

set(CMAKE_C_STANDARD 23)

include_directories(include/)
add_compile_options(-O2)

add_executable(main
        src/bruteforce.c
        src/database.c
        src/interface.c
        src/main.c
        src/md2.c
        src/person.c
        src/utils.c
)
