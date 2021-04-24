add_library(ai Strategy.cpp)

target_include_directories(ai PUBLIC "${PROJECT_SOURCE_DIR}")
target_link_libraries(ai PUBLIC game)

