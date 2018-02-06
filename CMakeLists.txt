cmake_minimum_required(VERSION 2.8.9)
project (Windows-Standards)
set(CMAKE_BUILD_TYPE Release)
include_directories(include)
file(GLOB SOURCES "src/*.cpp")
add_executable(Windows-Standards Windows-Standards.cpp)

add_library(WindowsStandards SHARED ${SOURCES})