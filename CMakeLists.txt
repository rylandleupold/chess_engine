cmake_minimum_required(VERSION 3.28.0)

project(ChessEngine LANGUAGES C CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} chess_engine.cpp)

add_subdirectory(src)
target_link_libraries(${PROJECT_NAME} ChessEngineLib)
