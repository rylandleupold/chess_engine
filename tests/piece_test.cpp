#include "gtest/gtest.h"
#include "../src/piece.h"

TEST(piece_test, piece_isWhite_test) {
    Piece blackPieces[6] = {
        Piece::blackPawn, Piece::blackKnight, Piece::blackBishop,
        Piece::blackRook, Piece::blackQueen, Piece::blackKing
    };
    Piece whitePieces[6] = {
        Piece::whitePawn, Piece::whiteKnight, Piece::whiteBishop,
        Piece::whiteRook, Piece::whiteQueen, Piece::whiteKing
    };

    for (int i=0; i<sizeof(blackPieces) / sizeof(Piece); i++) {
        ASSERT_FALSE(isWhite(blackPieces[i]));
        ASSERT_TRUE(isWhite(whitePieces[i]));
    }

    ASSERT_FALSE(isWhite(Piece::noPiece));
}