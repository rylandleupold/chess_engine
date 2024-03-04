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

TEST(piece_test, piece_isSlider_test) {
    std::vector<Piece> slidingPieces = {
        Piece::blackBishop, Piece::whiteBishop,
        Piece::blackRook, Piece::whiteRook,
        Piece::blackQueen, Piece::whiteQueen
    };

    std::vector<Piece> notSlidingPieces = {
        Piece::blackPawn, Piece::whitePawn,
        Piece::blackKnight, Piece::whiteKnight,
        Piece::blackKing, Piece::whiteKing,
        Piece::noPiece
    };

    for (Piece p : slidingPieces) {
        ASSERT_TRUE(isSlider(p));
    }
    for (Piece p : notSlidingPieces) {
        ASSERT_FALSE(isSlider(p));
    }
}
