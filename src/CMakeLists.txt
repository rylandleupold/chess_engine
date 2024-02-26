cmake_minimum_required(VERSION 3.28.0)

project(ChessEngineLib)

set(ChessEngineLib_src 
    bitboard.h 
    bitboard.cpp 
    castling_rights.h
    castling_rights.cpp
    color.h
    direction.h
    mask.h
    move.h
    move.cpp
    move_generator.h
    move_generator.cpp
    piece.h 
    piece.cpp
    position.h
    position.cpp
    square.h
)

add_library(${PROJECT_NAME} ${ChessEngineLib_src})
