cmake_minimum_required(VERSION 3.20)
project(AiSP)

set(CMAKE_CXX_STANDARD 20)

add_executable(AiSP main.cpp
        stockDatabase.cpp)
