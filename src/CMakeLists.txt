cmake_minimum_required(VERSION 3.28.0)

project(ChessEngineLib)

set(ChessEngineLib_src 
    bitboard.h 
    bitboard.cpp 
    piece.h 
    position.h
    position.cpp
    square.h
)

add_library(${PROJECT_NAME} ${ChessEngineLib_src})
