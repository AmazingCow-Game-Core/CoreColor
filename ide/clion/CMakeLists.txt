cmake_minimum_required(VERSION 3.8)
project(clion)

set(CMAKE_CXX_STANDARD 11)

include_directories("../../")


set(SOURCE_FILES
        ../../CoreColor/Color.h
        ../../CoreColor/include/Color.h
        ../../CoreColor/include/Convert.h
        ../../CoreColor/include/CoreColor_Utils.h
        ../../CoreColor/src/Color.cpp
        ../../CoreColor/src/Convert.cpp
        main.cpp)
add_executable(clion ${SOURCE_FILES})
