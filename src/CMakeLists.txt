cmake_minimum_required(VERSION 3.10)

project(rps)

add_subdirectory(parser)
add_subdirectory(game)

add_executable(rps app/main.cpp)

target_include_directories(rps PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(rps PUBLIC parser game)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
