cmake_minimum_required(VERSION 3.5)

project(Battleship LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Battleship main.cpp
    utility.hpp
    ship.hpp
    player.hpp)
