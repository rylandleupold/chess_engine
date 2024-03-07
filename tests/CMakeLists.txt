cmake_minimum_required(VERSION 3.28.0)

project(ChessEngineTests VERSION 1.0)

set(ChessEngineTests_src 
    bitboard_test.cpp
    castling_rights_test.cpp
    fen_parser_test.cpp
    move_test.cpp
    move_generator_test.cpp
    piece_test.cpp
    position_test.cpp
)

add_executable(${PROJECT_NAME} ${ChessEngineTests_src})

target_link_libraries(${PROJECT_NAME}
    ChessEngineLib
    gtest_main
)

add_test(NAME bitboard_test COMMAND ${PROJECT_NAME})
add_test(NAME castling_rights_test COMMAND ${PROJECT_NAME})
add_test(NAME fen_parser_test COMMAND ${PROJECT_NAME})
add_test(NAME move_generator_test COMMAND ${PROJECT_NAME})
add_test(NAME move_test COMMAND ${PROJECT_NAME})
add_test(NAME piece_test COMMAND ${PROJECT_NAME})
add_test(NAME position_test COMMAND ${PROJECT_NAME})

project(ChessEnginePerftTests VERSION 1.0)

set(ChessEnginePerftTests_src
    perft_test.cpp
)

add_executable(ChessEnginePerftTests ${ChessEnginePerftTests_src})

target_link_libraries(ChessEnginePerftTests
    ChessEngineLib
    gtest_main
) 
