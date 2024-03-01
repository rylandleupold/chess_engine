#include "gtest/gtest.h"
#include "../src/position.h"

TEST(position_test, position_constructor_test) {
    Position p1;
    Position p2 = Position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    ASSERT_EQ(p1.castlingRights, p2.castlingRights);
    ASSERT_EQ(p1.fullMoveCounter, p2.fullMoveCounter);
    ASSERT_EQ(p1.halfmoveClock, p2.halfmoveClock);
    ASSERT_EQ(p1.colorToMove, p2.colorToMove);
    ASSERT_EQ(p1.enPassantTarget, p2.enPassantTarget);
    ASSERT_EQ(p1.pieceList, p2.pieceList);
    ASSERT_EQ(p1.occupied, p2.occupied);
    for (Piece p=Piece::blackPawn; p<Piece::noPiece; p=Piece(p+1)) {
        ASSERT_EQ(p1.pieceBitboards[p], p2.pieceBitboards[p]);
    }
    ASSERT_EQ(p1.occupiedByColor[Color::white], p2.occupiedByColor[Color::white]);
    ASSERT_EQ(p1.occupiedByColor[Color::black], p2.occupiedByColor[Color::black]);
}
