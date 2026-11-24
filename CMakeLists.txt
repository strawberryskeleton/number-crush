cmake_minimum_required(VERSION 3.20)
project(number_crush C)

set(CMAKE_C_STANDARD 11)

add_executable(main
        main.c
        tinymt32.c
)