cmake_minimum_required(VERSION 3.28.0)

project(ChessEngineTests VERSION 1.0)

set(ChessEngineTests_src 
    bitboard_test.cpp
    castling_rights_test.cpp
    move_test.cpp
)

add_executable(${PROJECT_NAME} ${ChessEngineTests_src})

target_link_libraries(${PROJECT_NAME}
    ChessEngineLib
    gtest_main
)

add_test(NAME bitboard_test COMMAND ${PROJECT_NAME})