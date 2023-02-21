cmake_minimum_required(VERSION 3.8)
project(TeSSA)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Manager.cpp Manager.h Data.cpp Data.h)
add_executable(TeSSA ${SOURCE_FILES})