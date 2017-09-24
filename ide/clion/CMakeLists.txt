cmake_minimum_required(VERSION 3.8)
project(clion)

set(CMAKE_CXX_STANDARD 11)

include_directories("../../include")


set(SOURCE_FILES
        ../../include/Color.h
        ../../include/Convert.h
        ../../include/CoreColor.h
        ../../include/CoreColor_Utils.h
        ../../src/CoreColor.cpp
        ../../src/Convert.cpp
        main.cpp)
add_executable(clion ${SOURCE_FILES})
