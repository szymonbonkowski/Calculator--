cmake_minimum_required(VERSION 4.0)
project(Calculator--)

set(CMAKE_CXX_STANDARD 17)

add_executable(Calculator-- main.cpp)

if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
endif()