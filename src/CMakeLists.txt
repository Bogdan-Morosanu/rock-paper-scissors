cmake_minimum_required(VERSION 3.10)

project(rps)

add_subdirectory(parser)
add_subdirectory(game)
add_subdirectory(app)

add_executable(rps app/main.cpp)
target_include_directories(rps PUBLIC "${PROJECT_SOURCE_DIR}")
target_link_libraries(rps PUBLIC app parser game)

add_executable(tests tests/tests.cpp)
target_include_directories(tests PUBLIC "${PROJECT_SOURCE_DIR}")
target_link_libraries(tests PUBLIC app parser game)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
