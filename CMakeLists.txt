cmake_minimum_required(VERSION 3.15)

project(EulerFluid  VERSION 0.1
                    DESCRIPTION "A simple staggered grid based fluid simulation"
                    LANGUAGES CXX)

file(GLOB_RECURSE sources src/*.cpp)

add_executable(eulerf ${sources})
target_include_directories(eulerf PRIVATE include)

find_package(raylib CONFIG REQUIRED)
target_link_libraries(eulerf PRIVATE raylib)

