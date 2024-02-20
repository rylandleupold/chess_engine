#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <string>

enum Piece {
    whitePawn, whiteKnight, whiteBishop, whiteRook, whiteQueen, whiteKing,
    blackPawn, blackKnight, blackBishop, blackRook, blackQueen, blackKing,
    noPiece
};

std::ostream& operator<<(std::ostream& os, const Piece piece);

const char* pieceToString(Piece piece);

#endif