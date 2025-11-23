cmake_minimum_required(VERSION 3.16)
project(Calculator--)

set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
endif()

add_executable(Calculator--Console main.cpp)

add_executable(Calculator--GUI WIN32 main_gui.cpp)