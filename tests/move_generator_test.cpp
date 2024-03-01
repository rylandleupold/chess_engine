#include "gtest/gtest.h"
#include "../src/castling_rights.h"
#include "../src/move_generator.h"
#include "../src/position.h"
#include <bitset>
#include <set>

TEST(move_generator_test, move_generator_king_moves_test) {
    MoveGenerator m;
    Bitboard kingCorner;
    kingCorner.set(Square::A2);
    kingCorner.set(Square::B1);
    kingCorner.set(Square::B2);
    ASSERT_EQ(m.kingAttacks(Square::A1), kingCorner);

    Bitboard kingRank1;
    kingRank1.set(Square::C1);
    kingRank1.set(Square::C2);
    kingRank1.set(Square::D2);
    kingRank1.set(Square::E2);
    kingRank1.set(Square::E1);
    ASSERT_EQ(m.kingAttacks(Square::D1), kingRank1);

    Bitboard kingRank8;
    kingRank8.set(Square::D8);
    kingRank8.set(Square::D7);
    kingRank8.set(Square::E7);
    kingRank8.set(Square::F7);
    kingRank8.set(Square::F8);
    ASSERT_EQ(m.kingAttacks(Square::E8), kingRank8);

    Bitboard kingFileA;
    kingFileA.set(Square::A7);
    kingFileA.set(Square::B7);
    kingFileA.set(Square::B6);
    kingFileA.set(Square::B5);
    kingFileA.set(Square::A5);

    ASSERT_EQ(m.kingAttacks(Square::A6), kingFileA);

    Bitboard kingFileH;
    kingFileH.set(Square::H7);
    kingFileH.set(Square::G7);
    kingFileH.set(Square::G6);
    kingFileH.set(Square::G5);
    kingFileH.set(Square::H5);
    ASSERT_EQ(m.kingAttacks(Square::H6), kingFileH);

    Bitboard kingMiddle;
    kingMiddle.set(Square::B5);
    kingMiddle.set(Square::B6);
    kingMiddle.set(Square::C6);
    kingMiddle.set(Square::D6);
    kingMiddle.set(Square::D5);
    kingMiddle.set(Square::D4);
    kingMiddle.set(Square::C4);
    kingMiddle.set(Square::B4);
    ASSERT_EQ(m.kingAttacks(Square::C5), kingMiddle);
}

TEST(move_generator_test, move_generator_knight_moves_test) {
    MoveGenerator m;
    Bitboard knightCorner;
    knightCorner.set(Square::G6);
    knightCorner.set(Square::F7);
    ASSERT_EQ(m.knightAttacks(Square::H8), knightCorner);

    Bitboard knightRank1;
    knightRank1.set(Square::D3);
    knightRank1.set(Square::F3);
    knightRank1.set(Square::C2);
    knightRank1.set(Square::G2);
    ASSERT_EQ(m.knightAttacks(Square::E1), knightRank1);

    Bitboard knightRank8;
    knightRank8.set(Square::B7);
    knightRank8.set(Square::F7);
    knightRank8.set(Square::C6);
    knightRank8.set(Square::E6);
    ASSERT_EQ(m.knightAttacks(Square::D8), knightRank8);

    Bitboard knightFileA;
    knightFileA.set(Square::B1);
    knightFileA.set(Square::B5);
    knightFileA.set(Square::C2);
    knightFileA.set(Square::C4);
    ASSERT_EQ(m.knightAttacks(Square::A3), knightFileA);

    Bitboard knightFileH;
    knightFileH.set(Square::G8);
    knightFileH.set(Square::G4);
    knightFileH.set(Square::F7);
    knightFileH.set(Square::F5);
    ASSERT_EQ(m.knightAttacks(Square::H6), knightFileH);

    Bitboard knightFileG;
    knightFileG.set(Square::H7);
    knightFileG.set(Square::H3);
    knightFileG.set(Square::F7);
    knightFileG.set(Square::F3);
    knightFileG.set(Square::E4);
    knightFileG.set(Square::E6);
    ASSERT_EQ(m.knightAttacks(Square::G5), knightFileG);

    Bitboard knightRank2;
    knightRank2.set(Square::A1);
    knightRank2.set(Square::A3);
    knightRank2.set(Square::E1);
    knightRank2.set(Square::E3);
    knightRank2.set(Square::B4);
    knightRank2.set(Square::D4);
    ASSERT_EQ(m.knightAttacks(Square::C2), knightRank2);

    Bitboard knightMiddle;
    knightMiddle.set(Square::C7);
    knightMiddle.set(Square::E7);
    knightMiddle.set(Square::C3);
    knightMiddle.set(Square::E3);
    knightMiddle.set(Square::F6);
    knightMiddle.set(Square::F4);
    knightMiddle.set(Square::B6);
    knightMiddle.set(Square::B4);
    ASSERT_EQ(m.knightAttacks(Square::D5), knightMiddle);
}

TEST(move_generator_test, move_generator_bishopAttacks_test) {
    MoveGenerator m;
    Bitboard occupied;

    Bitboard expectedCorner;
    expectedCorner.set(
        std::vector<Square> {
            Square::B2, Square::C3, Square::D4, Square::E5, Square::F6, Square::G7, Square::H8});
    ASSERT_EQ(m.bishopAttacks(Square::A1, occupied), expectedCorner);

    Bitboard expectedCorner2;
    expectedCorner2.set(
        std::vector<Square> {
            Square::G2, Square::F3, Square::E4, Square::D5, Square::C6, Square::B7, Square::A8});
    ASSERT_EQ(m.bishopAttacks(Square::H1, occupied), expectedCorner2);

    Bitboard expectedSide;
    expectedSide.set(
        std::vector<Square> {
            Square::G5, Square::G3, Square::F6, Square::F2, Square::E7, Square::E1, Square::D8});
    ASSERT_EQ(m.bishopAttacks(Square::H4, occupied), expectedSide);

    Bitboard expectedSide2;
    expectedSide2.set(
        std::vector<Square> {
            Square::B7, Square::D7, Square::A6, Square::E6, Square::F5, Square::G4, Square::H3});
    ASSERT_EQ(m.bishopAttacks(Square::C8, occupied), expectedSide2);

    Bitboard expectedMiddle;
    expectedMiddle.set(
        std::vector<Square> {
            Square::C5, Square::E5, Square::B6, Square::F6, Square::A7, Square::G7, Square::H8, 
            Square::C3, Square::E3, Square::B2, Square::F2, Square::A1, Square::G1});
    ASSERT_EQ(m.bishopAttacks(Square::D4, occupied), expectedMiddle);
}

TEST(move_generator_test, move_generator_bishopAttacks_blocked_test) {
    MoveGenerator m;
    Bitboard occupied;
    occupied.set(Square::F6);
    occupied.set(Square::H8);
    Bitboard expectedCorner;
    expectedCorner.set(
        std::vector<Square> {Square::B2, Square::C3, Square::D4, Square::E5, Square::F6});
    ASSERT_EQ(m.bishopAttacks(Square::A1, occupied), expectedCorner);

    occupied = Bitboard(Square::F3);
    Bitboard expectedCorner2;
    expectedCorner2.set(std::vector<Square> {Square::G2, Square::F3});
    ASSERT_EQ(m.bishopAttacks(Square::H1, occupied), expectedCorner2);

    Bitboard expectedSide;
    occupied = Bitboard(Square::G5);
    occupied.set(Square::F2);
    expectedSide.set(std::vector<Square> {Square::G5, Square::G3, Square::F2});
    ASSERT_EQ(m.bishopAttacks(Square::H4, occupied), expectedSide);

    occupied = Bitboard(Square::B7);
    occupied.set(Square::E6);
    occupied.set(Square::F5);
    Bitboard expectedSide2;
    expectedSide2.set(std::vector<Square> {Square::B7, Square::D7, Square::E6});
    ASSERT_EQ(m.bishopAttacks(Square::C8, occupied), expectedSide2);

    Bitboard expectedMiddle;
    occupied = Bitboard();
    occupied.set(std::vector<Square> {Square::C3, Square::B6, Square::A7, Square::F2, Square::G1});
    expectedMiddle.set(
        std::vector<Square> {
            Square::C5, Square::E5, Square::B6, Square::F6, Square::G7, Square::H8, 
            Square::C3, Square::E3, Square::F2});
    ASSERT_EQ(m.bishopAttacks(Square::D4, occupied), expectedMiddle);
}

TEST(move_generator_test, move_generator_rookAttacks_test) {
    MoveGenerator m;
    Bitboard occupied;

    Bitboard expectedCorner;
    expectedCorner.set(std::vector<Square> {A7, A6, A5, A4, A3, A2, A1, B8, C8, D8, E8, F8, G8, H8});
    ASSERT_EQ(m.rookAttacks(Square::A8, occupied), expectedCorner);

    Bitboard expectedCorner2;
    expectedCorner2.set(std::vector<Square> {A1, B1, C1, D1, E1, F1, G1, H2, H3, H4, H5, H6, H7, H8});
    ASSERT_EQ(m.rookAttacks(Square::H1, occupied), expectedCorner2);

    Bitboard expectedSide;
    expectedSide.set(std::vector<Square> {A1, B1, D1, E1, F1, G1, H1, C2, C3, C4, C5, C6, C7, C8});
    ASSERT_EQ(m.rookAttacks(Square::C1, occupied), expectedSide);

    Bitboard expectedSide2;
    expectedSide2.set(std::vector<Square> {H8, H6, H5, H4, H3, H2, H1, G7, F7, E7, D7, C7, B7, A7});
    ASSERT_EQ(m.rookAttacks(Square::H7, occupied), expectedSide2);

    Bitboard expectedMiddle;
    expectedMiddle.set(std::vector<Square> {E1, E2, E3, E4, E6, E7, E8, A5, B5, C5, D5, F5, G5, H5});
    ASSERT_EQ(m.rookAttacks(Square::E5, occupied), expectedMiddle);
}

TEST(move_generator_test, move_generator_rookAttacks_blocked_test) {
    MoveGenerator m;

    Bitboard occupied;
    occupied.set(std::vector<Square> {F8, G8, A4});
    Bitboard expectedCorner;
    expectedCorner.set(std::vector<Square> {A7, A6, A5, A4, B8, C8, D8, E8, F8});
    ASSERT_EQ(m.rookAttacks(Square::A8, occupied), expectedCorner);

    occupied = Bitboard();
    occupied.set(std::vector<Square> {H3, H7, B1, C8, C7});
    Bitboard expectedCorner2;
    expectedCorner2.set(std::vector<Square> {B1, C1, D1, E1, F1, G1, H2, H3});
    ASSERT_EQ(m.rookAttacks(Square::H1, occupied), expectedCorner2);

    occupied = Bitboard();
    occupied.set(std::vector<Square> {B1, C2});
    Bitboard expectedSide;
    expectedSide.set(std::vector<Square> {B1, D1, E1, F1, G1, H1, C2});
    ASSERT_EQ(m.rookAttacks(Square::C1, occupied), expectedSide);

    occupied = Bitboard();
    occupied.set(std::vector<Square> {H5, H1, B7});
    Bitboard expectedSide2;
    expectedSide2.set(std::vector<Square> {H8, H6, H5, G7, F7, E7, D7, C7, B7});
    ASSERT_EQ(m.rookAttacks(Square::H7, occupied), expectedSide2);

    occupied = Bitboard();
    occupied.set(std::vector<Square> {B1, E1, E3, F5, G5, E8});
    Bitboard expectedMiddle;
    expectedMiddle.set(std::vector<Square> {E3, E4, E6, E7, E8, A5, B5, C5, D5, F5});
    ASSERT_EQ(m.rookAttacks(Square::E5, occupied), expectedMiddle);
}

TEST(move_generator_test, move_generator_queenAttacks_test) {
    MoveGenerator m;
    Bitboard occupied;

    Bitboard expectedCorner;
    expectedCorner.set(
        std::vector<Square> {
            A2, A3, A4, A5, A6, A7, A8, B2, C3, D4, E5, F6, G7, H8, B1, C1, D1, E1, F1, G1, H1});
    ASSERT_EQ(m.queenAttacks(Square::A1, occupied), expectedCorner);

    Bitboard expectedSide;
    expectedSide.set(
        std::vector<Square> {
            H8, H7, H5, H4, H3, H2, H1, G6, F6, E6, D6, C6, B6, A6, G7, F8, G5, F4, E3, D2, C1});
    ASSERT_EQ(m.queenAttacks(Square::H6, occupied), expectedSide);

    Bitboard expectedMiddle;
    expectedMiddle.set(
        std::vector<Square> {
            D1, D2, D4, D5, D6, D7, D8, A3, B3, C3, E3, F3, G3, H3, C4, C2, B5, B1, A6, E4, E2, F5, F1, G6, H7});
    ASSERT_EQ(m.queenAttacks(Square::D3, occupied), expectedMiddle);
}

TEST(move_generator_test, move_generator_queenAttacks_blocked_test) {
    MoveGenerator m;
    Bitboard occupied;
    occupied.set(std::vector<Square> {A3, A4, G7, H8, F1, G1, A1});
    Bitboard expectedCorner;
    expectedCorner.set(std::vector<Square> {A2, A3, B2, C3, D4, E5, F6, G7, B1, C1, D1, E1, F1});
    ASSERT_EQ(m.queenAttacks(Square::A1, occupied), expectedCorner);

    occupied = Bitboard();
    occupied.set(std::vector<Square> {A2, B2, H3, H2, F6, A6, E3, G8, });
    Bitboard expectedSide;
    expectedSide.set(
        std::vector<Square> {
            H8, H7, H5, H4, H3, G6, F6, G7, F8, G5, F4, E3});
    ASSERT_EQ(m.queenAttacks(Square::H6, occupied), expectedSide);

    occupied = Bitboard();
    occupied.set(std::vector<Square> {C2, A3, B3, E2, D5, D7, G6, H7, F3});
    Bitboard expectedMiddle;
    expectedMiddle.set(
        std::vector<Square> {
            D1, D2, D4, D5, B3, C3, E3, F3, C4, C2, B5, A6, E4, E2, F5, G6});
    ASSERT_EQ(m.queenAttacks(Square::D3, occupied), expectedMiddle);
}

TEST(move_generator_test, move_generator_pawnCapturesWest_test) {
    MoveGenerator m;
    Bitboard blackPawns;
    Bitboard whitePawns;
    ASSERT_EQ(m.pawnCapturesWest(blackPawns, Color::black), Bitboard(0ULL));
    ASSERT_EQ(m.pawnCapturesWest(whitePawns, Color::white), Bitboard(0ULL));

    blackPawns.set(std::vector<Square> {A7, B6, C4, D2, D4, F7, G5, H2});
    Bitboard expectedBlack;
    expectedBlack.set(std::vector<Square> {A5, B3, C1, C3, E6, F4, G1});
    ASSERT_EQ(m.pawnCapturesWest(blackPawns, Color::black), expectedBlack);

    whitePawns.set(std::vector<Square> {A4, B2, C5, D3, F6, F5, H7});
    Bitboard expectedWhite;
    expectedWhite.set(std::vector<Square> {A3, B6, C4, E7, E6, G8});
    ASSERT_EQ(m.pawnCapturesWest(whitePawns, Color::white), expectedWhite);
}

TEST(move_generator_test, move_generator_pawnCatpuresEast_test) {
    MoveGenerator m;
    Bitboard blackPawns;
    Bitboard whitePawns;
    ASSERT_EQ(m.pawnCapturesEast(blackPawns, Color::black), Bitboard(0ULL));
    ASSERT_EQ(m.pawnCapturesEast(whitePawns, Color::white), Bitboard(0ULL));

    blackPawns.set(std::vector<Square> {A7, B6, C4, D7, D6, F2, H3});
    Bitboard expectedBlack;
    expectedBlack.set(std::vector<Square> {B6, C5, D3, E6, E5, G1});
    ASSERT_EQ(m.pawnCapturesEast(blackPawns, Color::black), expectedBlack);

    whitePawns.set(std::vector<Square> {A2, B4, B7, D3, E2, F7, G5, H2});
    Bitboard expectedWhite;
    expectedWhite.set(std::vector<Square> {B3, C5, C8, E4, F3, G8, H6});
    ASSERT_EQ(m.pawnCapturesEast(whitePawns, Color::white), expectedWhite);
}

TEST(move_generator_test, move_generator_pawnCatpures_test) {
    MoveGenerator m;
    Bitboard blackPawns;
    Bitboard whitePawns;
    ASSERT_EQ(m.pawnCaptures(blackPawns, Color::black), Bitboard(0ULL));
    ASSERT_EQ(m.pawnCaptures(whitePawns, Color::white), Bitboard(0ULL));

    blackPawns.set(std::vector<Square> {A7, B6, C4, D7, D6, F2, H3});
    Bitboard expectedBlack;
    expectedBlack.set(std::vector<Square> {B6, A5, C5, B3, D3, C6, E6, C5, E5, E1, G1, G2});
    ASSERT_EQ(m.pawnCaptures(blackPawns, Color::black), expectedBlack);

    whitePawns.set(std::vector<Square> {A2, B4, B7, D3, E2, F7, G5, H2});
    Bitboard expectedWhite;
    expectedWhite.set(std::vector<Square> {B3, A5, C5, A8, C8, C4, E4, D3, F3, E8, G8, F6, H6, G3});
    ASSERT_EQ(m.pawnCaptures(whitePawns, Color::white), expectedWhite);
}

TEST(move_generator_test, move_generator_pawnPushes_test) {
    MoveGenerator m;
    Bitboard blackPawns;
    Bitboard whitePawns;
    Bitboard occupied;
    ASSERT_EQ(m.pawnPushes(blackPawns, Color::black, occupied), Bitboard(0ULL));
    ASSERT_EQ(m.pawnPushes(whitePawns, Color::white, occupied), Bitboard(0ULL));

    blackPawns.set(std::vector<Square> {A7, B6, C4, D7, D5, F2, H3});
    Bitboard expectedBlack;
    expectedBlack.set(std::vector<Square> {A6, B5, C3, D6, D4, F1, H2});
    ASSERT_EQ(m.pawnPushes(blackPawns, Color::black, occupied), expectedBlack);

    whitePawns.set(std::vector<Square> {A2, B4, B7, D3, E2, F7, G5, H2});
    Bitboard expectedWhite;
    expectedWhite.set(std::vector<Square> {A3, B5, B8, D4, E3, F8, G6, H3});
    ASSERT_EQ(m.pawnPushes(whitePawns, Color::white, occupied), expectedWhite);
}

TEST(move_generator_test, move_generator_pawnPushes_blocked_test) {
    MoveGenerator m;
    Bitboard blackPawns;
    Bitboard whitePawns;
    Bitboard occupiedBlack;
    Bitboard occupiedWhite;

    blackPawns.set(std::vector<Square> {A7, B6, C4, D7, D5, F2, H3});
    occupiedBlack.set(std::vector<Square> {A5, B5, B3, B4, D3, D6, F1, H1});
    Bitboard expectedBlack;
    expectedBlack.set(std::vector<Square> {A6, C3, D4, H2});
    ASSERT_EQ(m.pawnPushes(blackPawns, Color::black, occupiedBlack), expectedBlack);

    whitePawns.set(std::vector<Square> {A2, B4, B7, D3, E2, F7, G5, H2});
    occupiedWhite.set(std::vector<Square> {A3, B5, C4, E4, C3, F8, H5});
    Bitboard expectedWhite;
    expectedWhite.set(std::vector<Square> {B8, D4, E3, G6, H3});
    ASSERT_EQ(m.pawnPushes(whitePawns, Color::white, occupiedWhite), expectedWhite);
}

TEST(move_generator_test, move_generator_pawnDoublePushes_test) {
    MoveGenerator m;
    Bitboard blackPawns;
    Bitboard whitePawns;
    Bitboard occupied;
    ASSERT_EQ(m.pawnPushes(blackPawns, Color::black, occupied), Bitboard(0ULL));
    ASSERT_EQ(m.pawnPushes(whitePawns, Color::white, occupied), Bitboard(0ULL));

    blackPawns.set(std::vector<Square> {A7, B6, C7, D7, F2, H3});
    Bitboard expectedBlack;
    expectedBlack.set(std::vector<Square> {A5, C5, D5});
    ASSERT_EQ(m.pawnDoublePushes(blackPawns, Color::black, occupied), expectedBlack);

    whitePawns.set(std::vector<Square> {A2, B2, D3, E2, F7, G5, H2});
    Bitboard expectedWhite;
    expectedWhite.set(std::vector<Square> {A4, B4, E4, H4});
    ASSERT_EQ(m.pawnDoublePushes(whitePawns, Color::white, occupied), expectedWhite);
}

TEST(move_generator_test, move_generator_pawnDoublePushes_blocked_test) {
    MoveGenerator m;
    Bitboard blackPawns;
    Bitboard whitePawns;
    Bitboard occupiedBlack;
    Bitboard occupiedWhite;

    blackPawns.set(std::vector<Square> {A7, B6, C7, D7, F7, H7});
    occupiedBlack.set(std::vector<Square> {A5, B5, C6, D4, F8, H6, H5});
    Bitboard expectedBlack;
    expectedBlack.set(std::vector<Square> {D5, F5});
    ASSERT_EQ(m.pawnDoublePushes(blackPawns, Color::black, occupiedBlack), expectedBlack);

    whitePawns.set(std::vector<Square> {A2, B2, D3, E2, F7, G2, H2});
    occupiedWhite.set(std::vector<Square> {A3, A4, B5, C4, E4, C3, G3, H7});
    Bitboard expectedWhite;
    expectedWhite.set(std::vector<Square> {B4, H4});
    ASSERT_EQ(m.pawnDoublePushes(whitePawns, Color::white, occupiedWhite), expectedWhite);
}

TEST(move_generator_test, move_generator_atacksToKing_test) {
    // W attacked by all B pieces
    Position wAttacked1 = Position("8/3r4/8/8/1np1p3/3K4/4b3/1q2n3 w - - 0 1");
    Bitboard wExpected1;
    wExpected1.set(std::vector<Square> {D7, B4, C4, E4, E2, E1, B1});
    ASSERT_EQ(wAttacked1.moveGenerator->attacksToKing(wAttacked1.pieceBitboards, wAttacked1.occupied, Color::white), wExpected1);

    // W attacked by B pieces, some blocked by other B pieces
    Position wAttacked2 = Position("3q4/3r4/q7/4n3/1nr1p3/r1pK4/8/1b6 w - - 0 1");
    Bitboard wExpected2;
    wExpected2.set(std::vector<Square> {D7, E5, E4, B4, B1});
    ASSERT_EQ(wAttacked2.moveGenerator->attacksToKing(wAttacked2.pieceBitboards, wAttacked2.occupied, Color::white), wExpected2);

    // W attacked by no B pieces, but with no squares to move to
    Position wAttacked3 = Position("5q2/5r2/4n3/3b4/8/r2pK1kq/r4p2/2nq4 w - - 0 1");
    Bitboard wExpected3;
    ASSERT_EQ(wAttacked3.moveGenerator->attacksToKing(wAttacked3.pieceBitboards, wAttacked3.occupied, Color::white), wExpected3);

    // W attacked by B pieces, but all except knights are blocked by W pieces
    Position wAttacked4 = Position("7b/q5k1/1P1r4/1n1Q4/3K1N1r/2P1B3/1N6/q5b1 w - - 0 1");
    Bitboard wExpected4;
    wExpected4.set(std::vector<Square> {B5});
    ASSERT_EQ(wAttacked4.moveGenerator->attacksToKing(wAttacked4.pieceBitboards, wAttacked4.occupied, Color::white), wExpected4);

    // B attacked by all W pieces
    Position bAttacked1 = Position("3Q4/6BN/R4k2/4P1P1/4N3/5R2/8/8 b - - 0 1");
    Bitboard bExpected1;
    bExpected1.set(std::vector<Square> {A6, D8,E4, E5, F3, G5, G7, H7});
    ASSERT_EQ(bAttacked1.moveGenerator->attacksToKing(bAttacked1.pieceBitboards, bAttacked1.occupied, Color::black), bExpected1);

    // B attacked by W pieces, some blocked by other W pieces
    Position bAttacked2 = Position("3B3Q/3N2K1/3P4/R2Nk3/3P4/6B1/4R3/4Q3 b - - 0 1");
    Bitboard bExpected2;
    bExpected2.set(std::vector<Square> {E2, D4, G3, D7});
    ASSERT_EQ(bAttacked2.moveGenerator->attacksToKing(bAttacked2.pieceBitboards, bAttacked2.occupied, Color::black), bExpected2);

    // B attacked by no W pieces, but with no squares to move to
    Position bAttacked3 = Position("5RQ1/1Pk5/8/NBP3P1/4N3/8/8/R7 b - - 0 1");
    Bitboard bExpected3;
    ASSERT_EQ(bAttacked3.moveGenerator->attacksToKing(bAttacked3.pieceBitboards, bAttacked3.occupied, Color::black), bExpected3);

    // B attacked by W pieces, but all except knights are blocked by B pieces
    Position bAttacked4 = Position("8/3N2B1/4rq2/QR1bkp1Q/3p4/8/1B2K3/4Q3 w - - 0 1");
    Bitboard bExpected4;
    bExpected4.set(std::vector<Square> {D7});
    ASSERT_EQ(bAttacked4.moveGenerator->attacksToKing(bAttacked4.pieceBitboards, bAttacked4.occupied, Color::black), bExpected4);
}

TEST(move_generator_test, move_generator_kingDangerSquares_test) {
    // All black pieces, check x-ray on white king
    Position p1("8/4K3/1NN5/1Nq2p2/1NkN3b/6N1/3NrN2/4N3 w - - 0 1");
    Bitboard expected1;
    Bitboard p1Occupied = p1.occupied;
    expected1.set(std::vector<Square> {B6, B5, B4, C4, C6, D4, D5, D6, E7, F8, E5, F5, B3, C5, C3, D3, D2, E1, F2, E3, E4, E5, E6, E7, E8, G4, G3, G5, F6, D8});
    ASSERT_EQ(p1.moveGenerator->kingDangerSquares(p1.pieceBitboards, p1.occupied, Color::white), expected1);
    ASSERT_EQ(p1Occupied, p1.occupied);

    // All black pieces, check blocking by white pieces
    Position p2("8/8/8/8/1ppr4/1b1Qn3/2K5/8 w - - 0 1");
    Bitboard expected2;
    expected2.set(std::vector<Square> {A4, A2, C2, D1, C4, A3, C3, B3, D3, D5, D6, D7, D8, F1, G2, G4, F5, E4, F4, G4, H4});
    ASSERT_EQ(p2.moveGenerator->kingDangerSquares(p2.pieceBitboards, p2.occupied, Color::white), expected2);

    // Completely empty board except white king
    Position p3("8/8/8/8/8/8/8/K7 w - - 0 1");
    Bitboard expected3;
    ASSERT_EQ(p3.moveGenerator->kingDangerSquares(p3.pieceBitboards, p3.occupied, Color::white), expected3);

    // All white pieces, check x-ray on black king
    Position p4("Q1N5/P7/2k5/8/B1R1n3/1P6/8/8 w - - 0 1");
    Bitboard expected4;
    expected4.set(std::vector<Square> {A7, B7, C6, D5, E4, B8, C8, B3, B5, C6, D7, E8, A4, C4, B4, D4, E4, C3, C2, C1, C5, C6, C7, C8, B6, D6, E7});
    ASSERT_EQ(p4.moveGenerator->kingDangerSquares(p4.pieceBitboards, p4.occupied, Color::black), expected4);

    // All white pieces, check blocking black pieces
    Position p5("8/3b4/1Rp1kr1Q/1P4p1/2n3NP/8/B7/7K w - - 0 1");
    Bitboard expected5;
    expected5.set(std::vector<Square> {B1, B3, C4, A6, C6, B5, B7, B8, G1, G2, H2, F2, E3, E5, F6, H6, G5, H5, H4, G5, G6, G7, F8, H7, H8});
    ASSERT_EQ(p5.moveGenerator->kingDangerSquares(p5.pieceBitboards, p5.occupied, Color::black), expected5);

    // Completely empty board except black king
    Position p6("8/8/8/1k6/8/8/8/8 b - - 0 1");
    Bitboard expected6;
    ASSERT_EQ(p6.moveGenerator->kingDangerSquares(p6.pieceBitboards, p6.occupied, Color::black), expected6);
}

TEST(move_generator_test, move_generator_populateMoveList_double_check_test) {
    // White king checked 3 times, no other white pieces
    Position p1 = Position("3r4/8/8/b7/4n3/8/3K4/8 w - - 0 1");
    std::vector<Move> expected1 {
        Move(D2, C1, Move::MoveType::quiet),
        Move(D2, C2, Move::MoveType::quiet),
        Move(D2, E2, Move::MoveType::quiet),
        Move(D2, E3, Move::MoveType::quiet)};
    std::vector<Move> actual1 {};
    p1.moveGenerator->populateMoveList(actual1, p1);
    ASSERT_EQ(expected1, actual1);

    // Test white blocking some black attacks to king
    Position p2 = Position("k4r2/8/1b3P1q/2Qn4/8/3pK3/r2R4/8 w - - 0 1");
    std::vector<Move> expected2 {
        Move(E3, D3, Move::MoveType::capture),
        Move(E3, F2, Move::MoveType::quiet),
        Move(E3, F3, Move::MoveType::quiet),
        Move(E3, D4, Move::MoveType::quiet),
        Move(E3, E4, Move::MoveType::quiet)};
    std::vector<Move> actual2 {};
    p2.moveGenerator->populateMoveList(actual2, p2);
    ASSERT_EQ(expected2, actual2);

    // White king is in checkmate
    Position p3 = Position("8/8/8/rq2b3/8/8/2Pp4/1Kn5 w - - 0 1");
    std::vector<Move> expected3{};
    std::vector<Move> actual3{};
    p3.moveGenerator->populateMoveList(actual3, p3);
    ASSERT_EQ(expected3, actual3);

    // Black king checked 3 times, no other black pieces
    Position p4 = Position("3B4/1Q2k3/8/8/4R3/8/8/8 b - - 0 1");
    std::vector<Move> expected4 {
        Move(E7, D8, Move::MoveType::capture),
        Move(E7, D6, Move::MoveType::quiet),
        Move(E7, F8, Move::MoveType::quiet)};
    std::vector<Move> actual4 {};
    p4.moveGenerator->populateMoveList(actual4, p4);
    ASSERT_EQ(expected4, actual4);

    // Black can capture some, but not others, white blocked by some black pieces
    Position p5 = Position("2R1B3/1P6/Rpkp2R1/1P6/4n3/3N1Q2/8/8 b - - 0 1");
    std::vector<Move> expected5 {
        Move(C6, B7, Move::MoveType::capture),
        Move(C6, D5, Move::MoveType::quiet)};
    std::vector<Move> actual5 {};
    p5.moveGenerator->populateMoveList(actual5, p5);
    ASSERT_EQ(expected5, actual5);

    // Black king, one white piece defended by x-ray, another is not
    Position p6 = Position("8/8/3N1N2/4k3/3P4/2B2r2/7Q/5R2 b - - 0 1");
    std::vector<Move> expected6 {
        Move(E5, F6, Move::MoveType::capture),
        Move(E5, E6, Move::MoveType::quiet)};
    std::vector<Move> actual6 {};
    p6.moveGenerator->populateMoveList(actual6, p6);
    ASSERT_EQ(expected6, actual6);
}

TEST(move_generator_test, move_generator_populatePawnMoves_test) {
    Bitboard captureMask = Bitboard((uint64_t) 0xFFFFFFFFFFFFFFFF);
    Bitboard pushMask = Bitboard((uint64_t) 0xFFFFFFFFFFFFFFFF);

    // Test white pushes, double pushes, and promotion
    Position p = Position("1k6/4P3/2Pq4/3Pp2P/3p2b1/nP4n1/P2PP1P1/3K4 w - - 0 1");
    std::vector<Move> expected = {
        Move(E2, E4, Move::MoveType::doublePawnPush),
        Move(D2, D3, Move::MoveType::quiet),
        Move(E2, E3, Move::MoveType::quiet),
        Move(B3, B4, Move::MoveType::quiet),
        Move(H5, H6, Move::MoveType::quiet),
        Move(C6, C7, Move::MoveType::quiet),
        Move(E7, E8, Move::MoveType::queenPromo),
        Move(E7, E8, Move::MoveType::rookPromo),
        Move(E7, E8, Move::MoveType::bishopPromo),
        Move(E7, E8, Move::MoveType::knightPromo),
    };

    std::vector<Move> actual;
    p.moveGenerator->populatePawnMoves(
        actual, 
        p.pieceBitboards[Piece::whitePawn], 
        p.occupied, 
        p.occupiedByColor[Color::black], 
        p.colorToMove, 
        pushMask, 
        captureMask);
    
    ASSERT_EQ(expected, actual);

    // Test white captures and promoCaptures east and west
    p = Position("k2bnrbq/3P1P1P/4rn2/1qRnP3/2P1P3/1p6/1P6/7K w - - 0 1");
    expected.clear();
    expected = {
        Move(C4, D5, Move::MoveType::capture),
        Move(E5, F6, Move::MoveType::capture),
        Move(C4, B5, Move::MoveType::capture),
        Move(E4, D5, Move::MoveType::capture),

        Move(D7, E8, Move::MoveType::queenPromoCapture),
        Move(D7, E8, Move::MoveType::rookPromoCapture),
        Move(D7, E8, Move::MoveType::bishopPromoCapture),
        Move(D7, E8, Move::MoveType::knightPromoCapture),

        Move(F7, G8, Move::MoveType::queenPromoCapture),
        Move(F7, G8, Move::MoveType::rookPromoCapture),
        Move(F7, G8, Move::MoveType::bishopPromoCapture),
        Move(F7, G8, Move::MoveType::knightPromoCapture),

        Move(F7, E8, Move::MoveType::queenPromoCapture),
        Move(F7, E8, Move::MoveType::rookPromoCapture),
        Move(F7, E8, Move::MoveType::bishopPromoCapture),
        Move(F7, E8, Move::MoveType::knightPromoCapture),

        Move(H7, G8, Move::MoveType::queenPromoCapture),
        Move(H7, G8, Move::MoveType::rookPromoCapture),
        Move(H7, G8, Move::MoveType::bishopPromoCapture),
        Move(H7, G8, Move::MoveType::knightPromoCapture),       
    };

    actual.clear();
    p.moveGenerator->populatePawnMoves(
        actual, 
        p.pieceBitboards[Piece::whitePawn], 
        p.occupied, 
        p.occupiedByColor[Color::black], 
        p.colorToMove, 
        pushMask, 
        captureMask);
    ASSERT_EQ(expected, actual);

    // Test black pushes, double pushes, and promotions
    p = Position("7k/1p1pp1p1/1P4P1/1N2P3/p1pB1p2/5R2/K6p/8 b - - 0 1");
    expected.clear();
    expected = {
        
        Move(D7, D5, Move::MoveType::doublePawnPush),
        Move(A4, A3, Move::MoveType::quiet),
        Move(C4, C3, Move::MoveType::quiet),
        Move(D7, D6, Move::MoveType::quiet),
        Move(E7, E6, Move::MoveType::quiet),
        Move(H2, H1, Move::MoveType::queenPromo),
        Move(H2, H1, Move::MoveType::rookPromo),
        Move(H2, H1, Move::MoveType::bishopPromo),
        Move(H2, H1, Move::MoveType::knightPromo),
    };

    actual.clear();
    p.moveGenerator->populatePawnMoves(
        actual, 
        p.pieceBitboards[Piece::blackPawn], 
        p.occupied, 
        p.occupiedByColor[Color::white], 
        p.colorToMove, 
        pushMask, 
        captureMask);
    ASSERT_EQ(expected, actual);

    // Test black captures and promoCaptures east and west
    p = Position("5k2/3p4/2QbPp2/2p1Nnq1/1nRB4/6p1/pp1p2p1/NRQK2R1 b - - 0 1");
    expected.clear();
    expected = {
        Move(C5, D4, Move::MoveType::capture),
        Move(D7, E6, Move::MoveType::capture),
        Move(F6, E5, Move::MoveType::capture),
        Move(D7, C6, Move::MoveType::capture),

        Move(A2, B1, Move::MoveType::queenPromoCapture),
        Move(A2, B1, Move::MoveType::rookPromoCapture),
        Move(A2, B1, Move::MoveType::bishopPromoCapture),
        Move(A2, B1, Move::MoveType::knightPromoCapture),

        Move(B2, C1, Move::MoveType::queenPromoCapture),
        Move(B2, C1, Move::MoveType::rookPromoCapture),
        Move(B2, C1, Move::MoveType::bishopPromoCapture),
        Move(B2, C1, Move::MoveType::knightPromoCapture),

        Move(B2, A1, Move::MoveType::queenPromoCapture),
        Move(B2, A1, Move::MoveType::rookPromoCapture),
        Move(B2, A1, Move::MoveType::bishopPromoCapture),
        Move(B2, A1, Move::MoveType::knightPromoCapture),

        Move(D2, C1, Move::MoveType::queenPromoCapture),
        Move(D2, C1, Move::MoveType::rookPromoCapture),
        Move(D2, C1, Move::MoveType::bishopPromoCapture),
        Move(D2, C1, Move::MoveType::knightPromoCapture),       
    };

    actual.clear();
    p.moveGenerator->populatePawnMoves(
        actual, 
        p.pieceBitboards[Piece::blackPawn], 
        p.occupied, 
        p.occupiedByColor[Color::white], 
        p.colorToMove, 
        pushMask, 
        captureMask);
    ASSERT_EQ(expected, actual);
}

TEST(move_generator_test, move_generator_populatePawnEnPassantMoves_test) {
    Bitboard captureMask = Bitboard((uint64_t) 0xFFFFFFFFFFFFFFFF);
    Bitboard pushMask = Bitboard((uint64_t) 0xFFFFFFFFFFFFFFFF);

    // Both white pawns can capture EP
    Position p = Position("2k5/8/3P4/1PpP4/2P5/8/5P2/3K4 w - c6 0 5");
    std::vector<Move> expected = {
        Move(B5, C6, Move::MoveType::epCapture),
        Move(D5, C6, Move::MoveType::epCapture)
    };

    std::vector<Move> actual;
    p.moveGenerator->populatePawnEnPassantMoves(
        actual,
        p.pieceBitboards[Piece::whitePawn],
        Color::white,
        p.enPassantTarget,
        pushMask,
        captureMask);
    ASSERT_EQ(expected, actual);

    // Both black pawns can capture EP
    p = Position("1k6/8/8/8/3p1pPp/1P3P2/8/5K2 b - g3 0 1");
    expected.clear();
    expected = {
        Move(F4, G3, Move::MoveType::epCapture),
        Move(H4, G3, Move::MoveType::epCapture)
    };

    actual.clear();
    p.moveGenerator->populatePawnEnPassantMoves(
        actual,
        p.pieceBitboards[Piece::blackPawn],
        Color::black,
        p.enPassantTarget,
        pushMask,
        captureMask);
    ASSERT_EQ(expected, actual);

    // Nobody can capture EP
    p = Position("4k3/4P3/1R4P1/5p2/3P1p1p/8/8/5K2 w - f6 0 3");
    expected.clear();
    actual.clear();
    p.moveGenerator->populatePawnEnPassantMoves(
        actual,
        p.pieceBitboards[Piece::whitePawn],
        Color::white,
        p.enPassantTarget,
        pushMask,
        captureMask);
    ASSERT_EQ(expected, actual);

    // Only 1 pawn can capture east EP 
    p = Position("4k3/8/1R6/8/1pP4p/3pPP2/8/5K2 b - c3 0 3");
    expected.clear();
    expected = {
        Move(B4, C3, Move::MoveType::epCapture),
    };

    actual.clear();
    p.moveGenerator->populatePawnEnPassantMoves(
        actual,
        p.pieceBitboards[Piece::blackPawn],
        Color::black,
        p.enPassantTarget,
        pushMask,
        captureMask);
    ASSERT_EQ(expected, actual);

    // Only 1 pawn can capture west EP 
    p = Position("4k3/8/1R6/8/2Pp4/1p2P3/1p3P2/5K2 b - c3 0 3");
    expected.clear();
    expected = {
        Move(D4, C3, Move::MoveType::epCapture),
    };

    actual.clear();
    p.moveGenerator->populatePawnEnPassantMoves(
        actual,
        p.pieceBitboards[Piece::blackPawn],
        Color::black,
        p.enPassantTarget,
        pushMask,
        captureMask);
    ASSERT_EQ(expected, actual);

}
