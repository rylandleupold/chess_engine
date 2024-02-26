#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <string>

enum Piece {
    blackPawn, blackKnight, blackBishop, blackRook, blackQueen, blackKing,
    whitePawn, whiteKnight, whiteBishop, whiteRook, whiteQueen, whiteKing,
    noPiece
};

std::ostream& operator<<(std::ostream& os, const Piece piece);

const char* pieceToString(Piece piece);

#endif