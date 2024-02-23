#include "piece.h"

std::ostream& operator<<(std::ostream& os, const Piece piece) {
    switch (piece) {
        case (Piece::whitePawn): return os << "P";
        case (Piece::blackPawn): return os << "p";
        case (Piece::whiteKnight): return os << "N";
        case (Piece::blackKnight): return os << "n";
        case (Piece::whiteBishop): return os << "B";
        case (Piece::blackBishop): return os << "b";
        case (Piece::whiteRook): return os << "R";
        case (Piece::blackRook): return os << "r";
        case (Piece::whiteQueen): return os << "Q";
        case (Piece::blackQueen): return os << "q";
        case (Piece::whiteKing): return os << "K";
        case (Piece::blackKing): return os << "k";
        case (Piece::noPiece): return os << "-";
        default: return os << "";
    }
    return os;
}

const char* pieceToString(Piece piece) {
    switch (piece) {
        case (Piece::whitePawn): return "P";
        case (Piece::blackPawn): return "p";
        case (Piece::whiteKnight): return "N";
        case (Piece::blackKnight): return "n";
        case (Piece::whiteBishop): return "B";
        case (Piece::blackBishop): return "b";
        case (Piece::whiteRook): return "R";
        case (Piece::blackRook): return "r";
        case (Piece::whiteQueen): return "Q";
        case (Piece::blackQueen): return "q";
        case (Piece::whiteKing): return "K";
        case (Piece::blackKing): return "k";
        case (Piece::noPiece): return "-";
        default: return "";
    }
};