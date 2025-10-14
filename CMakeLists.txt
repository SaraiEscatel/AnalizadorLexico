cmake_minimum_required(VERSION 4.0)
project(Analizador_Lexico)

set(CMAKE_CXX_STANDARD 20)

add_executable(Analizador_Lexico main.cpp
        scanner.cpp)
