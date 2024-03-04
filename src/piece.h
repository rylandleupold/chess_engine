#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <string>

enum Piece {
    blackPawn, whitePawn, 
    blackKnight, whiteKnight, 
    blackBishop, whiteBishop, 
    blackRook, whiteRook, 
    blackQueen, whiteQueen,
    blackKing, whiteKing,
    noPiece
};

std::ostream& operator<<(std::ostream& os, const Piece piece);

const char* pieceToString(Piece piece);
const Piece charToPiece(char c);

const bool isWhite(Piece piece);
const bool isSlider(Piece piece);

#endif