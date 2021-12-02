cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(gregorian)

include_directories(backpack src/include)
file(GLOB SRC_FILES src/*.c)
add_library(gregorian STATIC ${SRC_FILES})
