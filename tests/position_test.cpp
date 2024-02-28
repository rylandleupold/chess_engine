#include "gtest/gtest.h"
#include "../src/position.h"

TEST(position_test, position_constructor_test) {
    Position p1;
    Position p2 = Position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    ASSERT_EQ(p1.castlingRights, p2.castlingRights);
    ASSERT_EQ(p1.fullMoveCounter, p2.fullMoveCounter);
    ASSERT_EQ(p1.halfmoveClock, p2.halfmoveClock);
    ASSERT_EQ(p1.whiteToMove, p2.whiteToMove);
    ASSERT_EQ(p1.enPassantTarget, p2.enPassantTarget);
    ASSERT_EQ(p1.pieceList, p2.pieceList);
    ASSERT_EQ(p1.occupied, p2.occupied);
    for (Piece p=Piece::blackPawn; p<=Piece::noPiece; p=Piece(p+1)) {
        ASSERT_EQ(p1.pieceBitboards[p], p2.pieceBitboards[p]);
    }
    ASSERT_EQ(p1.occupiedByColor[Color::white], p2.occupiedByColor[Color::white]);
    ASSERT_EQ(p1.occupiedByColor[Color::black], p2.occupiedByColor[Color::black]);
}

TEST(position_test, position_atacksToKing_test) {
    // W attacked by all B pieces
    Position wAttacked1 = Position("8/3r4/8/8/1np1p3/3K4/4b3/1q2n3 w - - 0 1");
    Bitboard wExpected1;
    wExpected1.set(std::vector<Square> {D7, B4, C4, E4, E2, E1, B1});
    ASSERT_EQ(wAttacked1.attacksToKing(Square::D3, Color::white), wExpected1);

    // W attacked by B pieces, some blocked by other B pieces
    Position wAttacked2 = Position("3q4/3r4/q7/4n3/1nr1p3/r1pK4/8/1b6 w - - 0 1");
    Bitboard wExpected2;
    wExpected2.set(std::vector<Square> {D7, E5, E4, B4, B1});
    ASSERT_EQ(wAttacked2.attacksToKing(Square::D3, Color::white), wExpected2);

    // W attacked by no B pieces, but with no squares to move to
    Position wAttacked3 = Position("5q2/5r2/4n3/3b4/8/r2pK1kq/r4p2/2nq4 w - - 0 1");
    Bitboard wExpected3;
    ASSERT_EQ(wAttacked3.attacksToKing(Square::E3, Color::white), wExpected3);

    // W attacked by B pieces, but all except knights are blocked by W pieces
    Position wAttacked4 = Position("7b/q5k1/1P1r4/1n1Q4/3K1N1r/2P1B3/1N6/q5b1 w - - 0 1");
    Bitboard wExpected4;
    wExpected4.set(std::vector<Square> {B5});
    ASSERT_EQ(wAttacked4.attacksToKing(Square::D4, Color::white), wExpected4);

    // B attacked by all W pieces
    Position bAttacked1 = Position("3Q4/6BN/R4k2/4P1P1/4N3/5R2/8/8 b - - 0 1");
    Bitboard bExpected1;
    bExpected1.set(std::vector<Square> {A6, D8,E4, E5, F3, G5, G7, H7});
    ASSERT_EQ(bAttacked1.attacksToKing(Square::F6, Color::black), bExpected1);

    // B attacked by W pieces, some blocked by other W pieces
    Position bAttacked2 = Position("3B3Q/3N2K1/3P4/R2Nk3/3P4/6B1/4R3/4Q3 b - - 0 1");
    Bitboard bExpected2;
    bExpected2.set(std::vector<Square> {E2, D4, G3, D7});
    ASSERT_EQ(bAttacked2.attacksToKing(Square::E5, Color::black), bExpected2);

    // B attacked by no W pieces, but with no squares to move to
    Position bAttacked3 = Position("5RQ1/1Pk5/8/NBP3P1/4N3/8/8/R7 b - - 0 1");
    Bitboard bExpected3;
    ASSERT_EQ(bAttacked3.attacksToKing(Square::C7, Color::black), bExpected3);

    // B attacked by W pieces, but all except knights are blocked by B pieces
    Position bAttacked4 = Position("8/3N2B1/4rq2/QR1bkp1Q/3p4/8/1B2K3/4Q3 w - - 0 1");
    Bitboard bExpected4;
    bExpected4.set(std::vector<Square> {D7});
    ASSERT_EQ(bAttacked4.attacksToKing(Square::E5, Color::black), bExpected4);
}