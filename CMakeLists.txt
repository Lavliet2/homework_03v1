cmake_minimum_required(VERSION 3.5)

project(GuessTheNumberGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(GuessTheNumberGame main.cpp
    GuessNumber.h GuessNumber.cpp
)


install(TARGETS GuessTheNumberGame
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
