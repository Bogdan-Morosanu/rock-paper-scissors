add_library(app GameApp.cpp MoveCommandParsers.cpp)

target_include_directories(app PUBLIC "${PROJECT_SOURCE_DIR}")
target_link_libraries(app PUBLIC parser game ai)
