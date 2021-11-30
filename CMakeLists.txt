cmake_minimum_required(VERSION 3.18)


project(ising)
set(CMAKE_CXX_STANDARD 14)

add_executable(ising)

target_sources(ising PUBLIC
        main.cpp
        ising.cpp
        ising.hpp)

target_include_directories(ising PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
