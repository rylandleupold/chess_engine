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
    MoveGenerator m;

    // W attacked by all B pieces
    Position wAttacked1 = Position("8/3r4/8/8/1np1p3/3K4/4b3/1q2n3 w - - 0 1");
    Bitboard wExpected1;
    wExpected1.set(std::vector<Square> {D7, B4, C4, E4, E2, E1, B1});
    ASSERT_EQ(m.attacksToKing(wAttacked1.pieceBitboards, wAttacked1.occupied, Color::white), wExpected1);

    // W attacked by B pieces, some blocked by other B pieces
    Position wAttacked2 = Position("3q4/3r4/q7/4n3/1nr1p3/r1pK4/8/1b6 w - - 0 1");
    Bitboard wExpected2;
    wExpected2.set(std::vector<Square> {D7, E5, E4, B4, B1});
    ASSERT_EQ(m.attacksToKing(wAttacked2.pieceBitboards, wAttacked2.occupied, Color::white), wExpected2);

    // W attacked by no B pieces, but with no squares to move to
    Position wAttacked3 = Position("5q2/5r2/4n3/3b4/8/r2pK1kq/r4p2/2nq4 w - - 0 1");
    Bitboard wExpected3;
    ASSERT_EQ(m.attacksToKing(wAttacked3.pieceBitboards, wAttacked3.occupied, Color::white), wExpected3);

    // W attacked by B pieces, but all except knights are blocked by W pieces
    Position wAttacked4 = Position("7b/q5k1/1P1r4/1n1Q4/3K1N1r/2P1B3/1N6/q5b1 w - - 0 1");
    Bitboard wExpected4;
    wExpected4.set(std::vector<Square> {B5});
    ASSERT_EQ(m.attacksToKing(wAttacked4.pieceBitboards, wAttacked4.occupied, Color::white), wExpected4);

    // B attacked by all W pieces
    Position bAttacked1 = Position("3Q4/6BN/R4k2/4P1P1/4N3/5R2/8/8 b - - 0 1");
    Bitboard bExpected1;
    bExpected1.set(std::vector<Square> {A6, D8,E4, E5, F3, G5, G7, H7});
    ASSERT_EQ(m.attacksToKing(bAttacked1.pieceBitboards, bAttacked1.occupied, Color::black), bExpected1);

    // B attacked by W pieces, some blocked by other W pieces
    Position bAttacked2 = Position("3B3Q/3N2K1/3P4/R2Nk3/3P4/6B1/4R3/4Q3 b - - 0 1");
    Bitboard bExpected2;
    bExpected2.set(std::vector<Square> {E2, D4, G3, D7});
    ASSERT_EQ(m.attacksToKing(bAttacked2.pieceBitboards, bAttacked2.occupied, Color::black), bExpected2);

    // B attacked by no W pieces, but with no squares to move to
    Position bAttacked3 = Position("5RQ1/1Pk5/8/NBP3P1/4N3/8/8/R7 b - - 0 1");
    Bitboard bExpected3;
    ASSERT_EQ(m.attacksToKing(bAttacked3.pieceBitboards, bAttacked3.occupied, Color::black), bExpected3);

    // B attacked by W pieces, but all except knights are blocked by B pieces
    Position bAttacked4 = Position("8/3N2B1/4rq2/QR1bkp1Q/3p4/8/1B2K3/4Q3 w - - 0 1");
    Bitboard bExpected4;
    bExpected4.set(std::vector<Square> {D7});
    ASSERT_EQ(m.attacksToKing(bAttacked4.pieceBitboards, bAttacked4.occupied, Color::black), bExpected4);
}

TEST(move_generator_test, move_generator_kingDangerSquares_test) {
    MoveGenerator m;

    // All black pieces, check x-ray on white king
    Position p1("8/4K3/1NN5/1Nq2p2/1NkN3b/6N1/3NrN2/4N3 w - - 0 1");
    Bitboard expected1;
    Bitboard p1Occupied = p1.occupied;
    expected1.set(std::vector<Square> {B6, B5, B4, C4, C6, D4, D5, D6, E7, F8, E5, F5, B3, C5, C3, D3, D2, E1, F2, E3, E4, E5, E6, E7, E8, G4, G3, G5, F6, D8});
    ASSERT_EQ(m.kingDangerSquares(p1.pieceBitboards, p1.occupied, Color::white), expected1);
    ASSERT_EQ(p1Occupied, p1.occupied);

    // All black pieces, check blocking by white pieces
    Position p2("8/8/8/8/1ppr4/1b1Qn3/2K5/8 w - - 0 1");
    Bitboard expected2;
    expected2.set(std::vector<Square> {A4, A2, C2, D1, C4, A3, C3, B3, D3, D5, D6, D7, D8, F1, G2, G4, F5, E4, F4, G4, H4});
    ASSERT_EQ(m.kingDangerSquares(p2.pieceBitboards, p2.occupied, Color::white), expected2);

    // Completely empty board except white king
    Position p3("8/8/8/8/8/8/8/K7 w - - 0 1");
    Bitboard expected3;
    ASSERT_EQ(m.kingDangerSquares(p3.pieceBitboards, p3.occupied, Color::white), expected3);

    // All white pieces, check x-ray on black king
    Position p4("Q1N5/P7/2k5/8/B1R1n3/1P6/8/8 w - - 0 1");
    Bitboard expected4;
    expected4.set(std::vector<Square> {A7, B7, C6, D5, E4, B8, C8, B3, B5, C6, D7, E8, A4, C4, B4, D4, E4, C3, C2, C1, C5, C6, C7, C8, B6, D6, E7});
    ASSERT_EQ(m.kingDangerSquares(p4.pieceBitboards, p4.occupied, Color::black), expected4);

    // All white pieces, check blocking black pieces
    Position p5("8/3b4/1Rp1kr1Q/1P4p1/2n3NP/8/B7/7K w - - 0 1");
    Bitboard expected5;
    expected5.set(std::vector<Square> {B1, B3, C4, A6, C6, B5, B7, B8, G1, G2, H2, F2, E3, E5, F6, H6, G5, H5, H4, G5, G6, G7, F8, H7, H8});
    ASSERT_EQ(m.kingDangerSquares(p5.pieceBitboards, p5.occupied, Color::black), expected5);

    // Completely empty board except black king
    Position p6("8/8/8/1k6/8/8/8/8 b - - 0 1");
    Bitboard expected6;
    ASSERT_EQ(m.kingDangerSquares(p6.pieceBitboards, p6.occupied, Color::black), expected6);
}

TEST(move_generator_test, move_generator_populateMoveList_double_check_test) {
    MoveGenerator m;

    // White king checked 3 times, no other white pieces
    Position p1 = Position("3r4/8/8/b7/4n3/8/3K4/8 w - - 0 1");
    std::vector<Move> expected1 {
        Move(D2, C1, Move::MoveType::quiet),
        Move(D2, C2, Move::MoveType::quiet),
        Move(D2, E2, Move::MoveType::quiet),
        Move(D2, E3, Move::MoveType::quiet)};
    std::vector<Move> actual1 {};
    m.populateMoveList(actual1, p1);
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
    m.populateMoveList(actual2, p2);
    ASSERT_EQ(expected2, actual2);

    // White king is in checkmate
    Position p3 = Position("8/8/8/rq2b3/8/8/p1Pp4/1Kn5 w - - 0 1");
    std::vector<Move> expected3{};
    std::vector<Move> actual3{};
    m.populateMoveList(actual3, p3);
    ASSERT_EQ(expected3, actual3);

    // Black king checked 3 times, no other black pieces
    Position p4 = Position("3B4/1Q2k3/8/8/4R3/8/8/8 b - - 0 1");
    std::vector<Move> expected4 {
        Move(E7, D8, Move::MoveType::capture),
        Move(E7, D6, Move::MoveType::quiet),
        Move(E7, F8, Move::MoveType::quiet)};
    std::vector<Move> actual4 {};
    m.populateMoveList(actual4, p4);
    ASSERT_EQ(expected4, actual4);

    // Black can capture some, but not others, white blocked by some black pieces
    Position p5 = Position("2R1B3/1P6/Rpkp2R1/1P6/4n3/3N1Q2/8/8 b - - 0 1");
    std::vector<Move> expected5 {
        Move(C6, B7, Move::MoveType::capture),
        Move(C6, D5, Move::MoveType::quiet)};
    std::vector<Move> actual5 {};
    m.populateMoveList(actual5, p5);
    ASSERT_EQ(expected5, actual5);

    // Black king, one white piece defended by x-ray, another is not
    Position p6 = Position("8/8/3N1N2/4k3/3P4/2B2r2/7Q/5R2 b - - 0 1");
    std::vector<Move> expected6 {
        Move(E5, F6, Move::MoveType::capture),
        Move(E5, E6, Move::MoveType::quiet)};
    std::vector<Move> actual6 {};
    m.populateMoveList(actual6, p6);
    ASSERT_EQ(expected6, actual6);
}

TEST(move_generator_test, move_generator_populatePawnMoves_test) {
    MoveGenerator m;

    Bitboard captureMask = Bitboard((uint64_t) 0xFFFFFFFFFFFFFFFF);
    Bitboard pushMask = Bitboard((uint64_t) 0xFFFFFFFFFFFFFFFF);
    Bitboard pinned = Bitboard();

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
    m.populatePawnMoves(
        actual,
        p, 
        pushMask, 
        captureMask,
        pinned);
    
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
    m.populatePawnMoves(
        actual,
        p, 
        pushMask, 
        captureMask,
        pinned);
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
    m.populatePawnMoves(
        actual,
        p, 
        pushMask, 
        captureMask,
        pinned);
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
    m.populatePawnMoves(
        actual,
        p, 
        pushMask, 
        captureMask,
        pinned);
    ASSERT_EQ(expected, actual);
}

TEST(move_generator_test, move_generator_populatePawnEnPassantMoves_test) {
    MoveGenerator m;

    Bitboard captureMask = Bitboard((uint64_t) 0xFFFFFFFFFFFFFFFF);
    Bitboard pushMask = Bitboard((uint64_t) 0xFFFFFFFFFFFFFFFF);
    Bitboard pinned = Bitboard();

    // Both white pawns can capture EP
    Position p = Position("2k5/8/3P4/1PpP4/2P5/8/5P2/3K4 w - c6 0 5");
    std::vector<Move> expected = {
        Move(B5, C6, Move::MoveType::epCapture),
        Move(D5, C6, Move::MoveType::epCapture)
    };

    std::vector<Move> actual;
    m.populatePawnEnPassantMoves(
        actual,
        p,
        pushMask,
        captureMask,
        pinned);
    ASSERT_EQ(expected, actual);

    // Both black pawns can capture EP
    p = Position("1k6/8/8/8/3p1pPp/1P3P2/8/5K2 b - g3 0 1");
    expected.clear();
    expected = {
        Move(F4, G3, Move::MoveType::epCapture),
        Move(H4, G3, Move::MoveType::epCapture)
    };

    actual.clear();
    m.populatePawnEnPassantMoves(
        actual,
        p,
        pushMask,
        captureMask,
        pinned);
    ASSERT_EQ(expected, actual);

    // Nobody can capture EP
    p = Position("4k3/4P3/1R4P1/5p2/3P1p1p/8/8/5K2 w - f6 0 3");
    expected.clear();
    actual.clear();
    m.populatePawnEnPassantMoves(
        actual,
        p,
        pushMask,
        captureMask,
        pinned);
    ASSERT_EQ(expected, actual);

    // Only 1 pawn can capture east EP 
    p = Position("4k3/8/1R6/8/1pP4p/3pPP2/8/5K2 b - c3 0 3");
    expected.clear();
    expected = {
        Move(B4, C3, Move::MoveType::epCapture),
    };

    actual.clear();
    m.populatePawnEnPassantMoves(
        actual,
        p,
        pushMask,
        captureMask,
        pinned);
    ASSERT_EQ(expected, actual);

    // Only 1 pawn can capture west EP 
    p = Position("4k3/8/1R6/8/2Pp4/1p2P3/1p3P2/5K2 b - c3 0 3");
    expected.clear();
    expected = {
        Move(D4, C3, Move::MoveType::epCapture),
    };

    actual.clear();
    m.populatePawnEnPassantMoves(
        actual,
        p,
        pushMask,
        captureMask,
        pinned);
    ASSERT_EQ(expected, actual);
}

TEST(move_generator_test, move_generator_populateKnightMoves_test) {
    MoveGenerator m;

    Bitboard captureMask = Bitboard((uint64_t) 0xFFFFFFFFFFFFFFFF);
    Bitboard pushMask = Bitboard((uint64_t) 0xFFFFFFFFFFFFFFFF);
    Bitboard pinned = Bitboard();

    // White knights in corner, side, and middle, quiet, capture, and blocked by own pieces
    Position p = Position("N3r1k1/2P3N1/1P1N2b1/1b3R2/2P4N/1b6/5P2/NK5N w - - 0 1");
    std::vector<Move> expected = {
        Move(A1, B3, Move::MoveType::capture),
        Move(A1, C2, Move::MoveType::quiet),

        Move(H1, G3, Move::MoveType::quiet),

        Move(H4, G6, Move::MoveType::capture),
        Move(H4, G2, Move::MoveType::quiet),
        Move(H4, F3, Move::MoveType::quiet),

        Move(D6, B5, Move::MoveType::capture),
        Move(D6, E8, Move::MoveType::capture),
        Move(D6, E4, Move::MoveType::quiet),
        Move(D6, B7, Move::MoveType::quiet),
        Move(D6, F7, Move::MoveType::quiet),
        Move(D6, C8, Move::MoveType::quiet),

        Move(G7, E8, Move::MoveType::capture),
        Move(G7, H5, Move::MoveType::quiet),
        Move(G7, E6, Move::MoveType::quiet)
    };

    std::vector<Move> actual;
    m.populateKnightMoves(actual, p, pushMask, captureMask, pinned);
    ASSERT_EQ(expected, actual);

    // Black knights in corner, side, and middle, quiet, capture, and blocked by own pieces
    p = Position("n6n/3q1p1k/bR2Q1p1/2n3n1/5P1N/1N5b/1Kp3n1/n3q3 b - - 0 1");
    expected.clear();
    expected = {
        Move(A1, B3, Move::MoveType::capture),

        Move(G2, F4, Move::MoveType::capture),
        Move(G2, H4, Move::MoveType::capture),
        Move(G2, E3, Move::MoveType::quiet),

        Move(C5, B3, Move::MoveType::capture),
        Move(C5, E6, Move::MoveType::capture),
        Move(C5, D3, Move::MoveType::quiet),
        Move(C5, A4, Move::MoveType::quiet),
        Move(C5, E4, Move::MoveType::quiet),
        Move(C5, B7, Move::MoveType::quiet),

        Move(G5, E6, Move::MoveType::capture),
        Move(G5, F3, Move::MoveType::quiet),
        Move(G5, E4, Move::MoveType::quiet),

        Move(A8, B6, Move::MoveType::capture),
        Move(A8, C7, Move::MoveType::quiet)
    };

    actual.clear();
    m.populateKnightMoves(actual, p, pushMask, captureMask, pinned);
    ASSERT_EQ(expected, actual);
}

TEST(move_generator_test, move_generator_populateBishopMoves_test) {
    MoveGenerator m;

    Bitboard captureMask = Bitboard((uint64_t) 0xFFFFFFFFFFFFFFFF);
    Bitboard pushMask = Bitboard((uint64_t) 0xFFFFFFFFFFFFFFFF);
    Bitboard pinned = Bitboard();

    // White bishops in corner, side, and middle, quiet, capture, and blocked by own pieces
    Position p = Position("pk5B/1p6/B4N1r/6n1/2NR3B/2b1B3/8/B1n3KB w - - 0 1");
    std::vector<Move> expected = {
        Move(A1, C3, Move::MoveType::capture),
        Move(A1, B2, Move::MoveType::quiet),

        Move(H1, B7, Move::MoveType::capture),
        Move(H1, G2, Move::MoveType::quiet),
        Move(H1, F3, Move::MoveType::quiet),
        Move(H1, E4, Move::MoveType::quiet),
        Move(H1, D5, Move::MoveType::quiet),
        Move(H1, C6, Move::MoveType::quiet),
        
        Move(E3, C1, Move::MoveType::capture),
        Move(E3, G5, Move::MoveType::capture),
        Move(E3, D2, Move::MoveType::quiet),
        Move(E3, F2, Move::MoveType::quiet),
        Move(E3, F4, Move::MoveType::quiet),

        Move(H4, G5, Move::MoveType::capture),
        Move(H4, E1, Move::MoveType::quiet),
        Move(H4, F2, Move::MoveType::quiet),
        Move(H4, G3, Move::MoveType::quiet),

        Move(A6, B7, Move::MoveType::capture),
        Move(A6, B5, Move::MoveType::quiet),

        Move(H8, G7, Move::MoveType::quiet),
    };

    std::vector<Move> actual;
    m.populateBishopMoves(actual, p, pushMask, captureMask, pinned);
    ASSERT_EQ(expected, actual);

    // Black bishops in corner, side, and middle, quiet, capture, and blocked by own pieces
    p = Position("b2Kb2b/4RP2/2n5/2b3b1/5r1Q/2P1n3/1q6/B5k1 b - - 0 1");
    expected.clear();
    expected = {
        Move(C5, E7, Move::MoveType::capture),
        Move(C5, A3, Move::MoveType::quiet),
        Move(C5, B4, Move::MoveType::quiet),
        Move(C5, D4, Move::MoveType::quiet),
        Move(C5, B6, Move::MoveType::quiet),
        Move(C5, D6, Move::MoveType::quiet),
        Move(C5, A7, Move::MoveType::quiet),

        Move(G5, H4, Move::MoveType::capture),
        Move(G5, E7, Move::MoveType::capture),
        Move(G5, F6, Move::MoveType::quiet),
        Move(G5, H6, Move::MoveType::quiet),

        Move(A8, B7, Move::MoveType::quiet),

        Move(E8, F7, Move::MoveType::capture),
        Move(E8, D7, Move::MoveType::quiet),
        
        Move(H8, C3, Move::MoveType::capture),
        Move(H8, D4, Move::MoveType::quiet),
        Move(H8, E5, Move::MoveType::quiet),
        Move(H8, F6, Move::MoveType::quiet),
        Move(H8, G7, Move::MoveType::quiet),
    };

    actual.clear();
    m.populateBishopMoves(actual, p, pushMask, captureMask, pinned);
    ASSERT_EQ(expected, actual);
}

TEST(move_generator_test, move_generator_populateRookMoves_test) {
    MoveGenerator m;

    Bitboard captureMask = Bitboard((uint64_t) 0xFFFFFFFFFFFFFFFF);
    Bitboard pushMask = Bitboard((uint64_t) 0xFFFFFFFFFFFFFFFF);
    Bitboard pinned = Bitboard();

    // White rooks in corner, side, and middle, captures, pushes and blocked by white pieces
    Position p = Position("3b1RR1/5B2/N7/3R1nk1/8/3B4/1K6/R1n1q3 w - - 0 1");
    std::vector<Move> expected = {
        Move(A1, C1, Move::MoveType::capture),
        Move(A1, B1, Move::MoveType::quiet),
        Move(A1, A2, Move::MoveType::quiet),
        Move(A1, A3, Move::MoveType::quiet),
        Move(A1, A4, Move::MoveType::quiet),
        Move(A1, A5, Move::MoveType::quiet),

        Move(D5, F5, Move::MoveType::capture),
        Move(D5, D8, Move::MoveType::capture),
        Move(D5, D4, Move::MoveType::quiet),
        Move(D5, A5, Move::MoveType::quiet),
        Move(D5, B5, Move::MoveType::quiet),
        Move(D5, C5, Move::MoveType::quiet),
        Move(D5, E5, Move::MoveType::quiet),
        Move(D5, D6, Move::MoveType::quiet),
        Move(D5, D7, Move::MoveType::quiet),
      
        Move(F8, D8, Move::MoveType::capture),
        Move(F8, E8, Move::MoveType::quiet),

        Move(G8, G5, Move::MoveType::capture),
        Move(G8, G6, Move::MoveType::quiet),
        Move(G8, G7, Move::MoveType::quiet),
        Move(G8, H8, Move::MoveType::quiet),
    };

    std::vector<Move> actual;
    m.populateRookMoves(actual, p, pushMask, captureMask, pinned);
    ASSERT_EQ(expected, actual);

    // Black rooks on corner, side, and middle, captures, pushes, and blocked by black
    p = Position("3r2k1/1B6/1r2n3/1B2R3/3QrP2/4P3/p7/rnKNR2r b - - 0 1");
    expected.clear();
    expected = {
        Move(H1, E1, Move::MoveType::capture),
        Move(H1, F1, Move::MoveType::quiet),
        Move(H1, G1, Move::MoveType::quiet),
        Move(H1, H2, Move::MoveType::quiet),
        Move(H1, H3, Move::MoveType::quiet),
        Move(H1, H4, Move::MoveType::quiet),
        Move(H1, H5, Move::MoveType::quiet),
        Move(H1, H6, Move::MoveType::quiet),
        Move(H1, H7, Move::MoveType::quiet),
        Move(H1, H8, Move::MoveType::quiet),

        Move(E4, E3, Move::MoveType::capture),
        Move(E4, D4, Move::MoveType::capture),
        Move(E4, F4, Move::MoveType::capture),
        Move(E4, E5, Move::MoveType::capture),

        Move(B6, B5, Move::MoveType::capture),
        Move(B6, B7, Move::MoveType::capture),
        Move(B6, A6, Move::MoveType::quiet),
        Move(B6, C6, Move::MoveType::quiet),
        Move(B6, D6, Move::MoveType::quiet),

        Move(D8, D4, Move::MoveType::capture),
        Move(D8, D5, Move::MoveType::quiet),
        Move(D8, D6, Move::MoveType::quiet),
        Move(D8, D7, Move::MoveType::quiet),
        Move(D8, A8, Move::MoveType::quiet),
        Move(D8, B8, Move::MoveType::quiet),
        Move(D8, C8, Move::MoveType::quiet),
        Move(D8, E8, Move::MoveType::quiet),
        Move(D8, F8, Move::MoveType::quiet),
    };

    actual.clear();
    m.populateRookMoves(actual, p, pushMask, captureMask, pinned);
    ASSERT_EQ(expected, actual);
}

TEST(move_generator_test, move_generator_populateQueenMoves_test) {
    MoveGenerator m;

    Bitboard captureMask = Bitboard((uint64_t) 0xFFFFFFFFFFFFFFFF);
    Bitboard pushMask = Bitboard((uint64_t) 0xFFFFFFFFFFFFFFFF);
    Bitboard pinned = Bitboard();

    // White queens in corner, side, and middle, pushes, captures, and blocked by white pieces
    Position p = Position("k5B1/3q4/1pN1Q3/B3b3/3n3R/6rQ/8/Q1p1R2K w - - 0 1");
    std::vector<Move> expected = {
        Move(A1, C1, Move::MoveType::capture),
        Move(A1, D4, Move::MoveType::capture),
        Move(A1, B1, Move::MoveType::quiet),
        Move(A1, A2, Move::MoveType::quiet),
        Move(A1, B2, Move::MoveType::quiet),
        Move(A1, A3, Move::MoveType::quiet),
        Move(A1, C3, Move::MoveType::quiet),
        Move(A1, A4, Move::MoveType::quiet),

        Move(H3, G3, Move::MoveType::capture),
        Move(H3, F1, Move::MoveType::quiet),
        Move(H3, G2, Move::MoveType::quiet),
        Move(H3, H2, Move::MoveType::quiet),
        Move(H3, G4, Move::MoveType::quiet),
        Move(H3, F5, Move::MoveType::quiet),

        Move(E6, E5, Move::MoveType::capture),
        Move(E6, D7, Move::MoveType::capture),
        Move(E6, A2, Move::MoveType::quiet),
        Move(E6, B3, Move::MoveType::quiet),
        Move(E6, C4, Move::MoveType::quiet),
        Move(E6, G4, Move::MoveType::quiet),
        Move(E6, D5, Move::MoveType::quiet),
        Move(E6, F5, Move::MoveType::quiet),
        Move(E6, D6, Move::MoveType::quiet),
        Move(E6, F6, Move::MoveType::quiet),
        Move(E6, G6, Move::MoveType::quiet),
        Move(E6, H6, Move::MoveType::quiet),
        Move(E6, E7, Move::MoveType::quiet),
        Move(E6, F7, Move::MoveType::quiet),
        Move(E6, E8, Move::MoveType::quiet),
    };
    std::vector<Move> actual;
    m.populateQueenMoves(actual, p, pushMask, captureMask, pinned);

    ASSERT_EQ(expected, actual);

    // Black queens in corner, side, and middle, pushes, captures, and blocked by black pieces
    p = Position("qnk1NR1q/pp6/5B2/p3b3/1q2b2P/1Qp3P1/8/K2Nq3 b - - 0 1");
    expected.clear();
    expected = {
        Move(E1, D1, Move::MoveType::capture),
        Move(E1, G3, Move::MoveType::capture),
        Move(E1, F1, Move::MoveType::quiet),
        Move(E1, G1, Move::MoveType::quiet),
        Move(E1, H1, Move::MoveType::quiet),
        Move(E1, D2, Move::MoveType::quiet),
        Move(E1, E2, Move::MoveType::quiet),
        Move(E1, F2, Move::MoveType::quiet),
        Move(E1, E3, Move::MoveType::quiet),

        Move(B4, B3, Move::MoveType::capture),
        Move(B4, F8, Move::MoveType::capture),
        Move(B4, A3, Move::MoveType::quiet),
        Move(B4, A4, Move::MoveType::quiet),
        Move(B4, C4, Move::MoveType::quiet),
        Move(B4, D4, Move::MoveType::quiet),
        Move(B4, B5, Move::MoveType::quiet),
        Move(B4, C5, Move::MoveType::quiet),
        Move(B4, B6, Move::MoveType::quiet),
        Move(B4, D6, Move::MoveType::quiet),
        Move(B4, E7, Move::MoveType::quiet),

        Move(H8, H4, Move::MoveType::capture),
        Move(H8, F6, Move::MoveType::capture),
        Move(H8, F8, Move::MoveType::capture),
        Move(H8, H5, Move::MoveType::quiet),
        Move(H8, H6, Move::MoveType::quiet),
        Move(H8, G7, Move::MoveType::quiet),
        Move(H8, H7, Move::MoveType::quiet),
        Move(H8, G8, Move::MoveType::quiet),
    };
    actual.clear();
    m.populateQueenMoves(actual, p, pushMask, captureMask, pinned);

    ASSERT_EQ(expected, actual);
}

TEST(move_generator_test, move_generator_populateKingCastlingMoves_white_test) {
    MoveGenerator m;

    std::vector<Position> wKingCastleBothSides = {
        Position("1k6/1r5r/8/8/8/8/8/R3K2R w KQ - 0 1"),
        Position("1k6/8/8/8/b1rb2r1/8/1PP2PP1/R3K2R w KQ - 0 1"),
        Position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq - 0 1"),
    };
    std::vector<Position> wKingCastleKS = {
        Position("4k3/8/8/8/2r5/8/8/R3K2R w KQ - 0 1"),
        Position("4k3/8/8/8/q1r5/8/8/R3K2R w KQ - 0 1"),
        Position("4k3/8/8/8/8/8/8/R1b1K2R w KQ - 0 1"),
        Position("4k3/8/8/8/8/8/8/R2nK2R w KQ - 0 1"),
        Position("4k3/8/8/8/8/8/8/RQ2K2R w KQ - 0 1"),
        Position("4k3/8/8/8/8/8/8/R3K2R w K - 0 1")
    };
    std::vector<Position> wKingCastleQS = {
        Position("4k3/8/8/8/2b3r1/8/8/R3K2R w KQ - 0 1"),
        Position("4k1q1/8/8/8/8/8/8/R3K2R w KQ - 0 1"),
        Position("4k3/8/b7/8/8/8/8/R3K2R w KQ - 0 1"),
        Position("4k3/8/8/8/8/8/8/R3K1NR w KQ - 0 1"),
        Position("4k3/8/8/8/8/8/8/R3Kn1R w KQ - 0 1"),
        Position("4k3/8/8/8/8/8/8/R3K2R w Q - 0 1")
    };  
    std::vector<Position> wKingCastleNoSide = {
        Position("1k6/7r/8/8/6r1/b7/8/R3K2R w KQ - 0 1"),
        Position("1k6/8/8/5r1b/8/8/8/R3K2R w KQ - 0 1"),
        Position("4k3/8/8/8/8/8/8/R3K2R w kq - 1 1"),
        Position("4k3/8/8/8/8/8/8/Rb2Kn1R w KQ - 1 1"),
        Position("4k3/8/8/8/8/8/8/RrNBKBbR w KQ - 1 1"),
    };

    std::vector<Move> expected = {
        Move(E1, G1, Move::MoveType::kingCastle),
        Move(E1, C1, Move::MoveType::queenCastle),
    };
    std::vector<Move> actual;
    for (Position p : wKingCastleBothSides) {
        actual.clear();
        m.populateKingCastlingMoves(
            actual, p, m.kingDangerSquares(p.pieceBitboards, p.occupied, p.colorToMove));
        ASSERT_EQ(expected, actual);
    }

    expected = {
        Move(E1, G1, Move::MoveType::kingCastle),
    };
    for (Position p : wKingCastleKS) {
        actual.clear();
        m.populateKingCastlingMoves(
            actual, p, m.kingDangerSquares(p.pieceBitboards, p.occupied, p.colorToMove));
        ASSERT_EQ(expected, actual);
    }

    expected = {
        Move(E1, C1, Move::MoveType::queenCastle),
    };
    for (Position p : wKingCastleQS) {
        actual.clear();
        m.populateKingCastlingMoves(
            actual, p, m.kingDangerSquares(p.pieceBitboards, p.occupied, p.colorToMove));
        ASSERT_EQ(expected, actual);
    }

    expected.clear();
    for (Position p : wKingCastleNoSide) {
        actual.clear();
        m.populateKingCastlingMoves(
            actual, p, m.kingDangerSquares(p.pieceBitboards, p.occupied, p.colorToMove));
        ASSERT_EQ(expected, actual);
    }
}

TEST(move_generator_test, move_generator_populateKingCastlingMoves_black_test) {
    MoveGenerator m;

    std::vector<Position> bKingCastleBothSides = {
        Position("r3k2r/8/8/8/8/8/8/R3K2R b KQkq - 0 1"),
        Position("r3k2r/8/8/8/8/8/1R6/4K3 b kq - 0 1"),
        Position("r3k2r/2ppbpp1/8/2Q2B2/8/1R6/8/4K3 b kq - 0 1"),
    };
    std::vector<Position> bKingCastleKS = {
        Position("r3k2r/8/8/5B2/8/1R6/8/4K3 b kq - 0 1"),
        Position("r3k2r/8/8/5B2/8/3R4/8/4K3 b kq - 0 1"),
        Position("r3k2r/8/8/8/8/3Q4/8/4K3 b kq - 0 1"),
        Position("rq2k2r/8/8/8/8/8/8/4K3 b kq - 0 1"),
        Position("rN1bk2r/8/8/8/8/8/8/4K3 b kq - 0 1")
    };
    std::vector<Position> bKingCastleQS = {
        Position("r3k2r/8/8/8/6R1/8/8/4K3 b kq - 0 1"),
        Position("r3k2r/8/8/8/1B6/8/8/4K3 b kq - 0 1"),
        Position("r3k2r/8/8/R7/1B6/8/8/4K3 b kq - 0 1"),
        Position("r3k1br/8/8/8/8/8/8/4K3 b kq - 0 1"),
        Position("r3kN1r/8/8/8/8/8/8/4K3 b kq - 0 1"),
    };  
    std::vector<Position> bKingCastleNoSide = {
        Position("rbB1kNbr/8/8/8/8/8/8/4K3 b kq - 0 1"),
        Position("r3k2r/8/8/2Q3R1/8/8/8/4K3 b kq - 0 1"),
        Position("r3k2r/8/8/8/8/8/8/4K3 b KQ - 1 1"),
    };

    std::vector<Move> expected = {
        Move(E8, G8, Move::MoveType::kingCastle),
        Move(E8, C8, Move::MoveType::queenCastle),
    };
    std::vector<Move> actual;
    for (Position p : bKingCastleBothSides) {
        actual.clear();
        m.populateKingCastlingMoves(
            actual, p, m.kingDangerSquares(p.pieceBitboards, p.occupied, p.colorToMove));
        ASSERT_EQ(expected, actual);
    }

    expected = {
        Move(E8, G8, Move::MoveType::kingCastle),
    };
    for (Position p : bKingCastleKS) {
        actual.clear();
        m.populateKingCastlingMoves(
            actual, p, m.kingDangerSquares(p.pieceBitboards, p.occupied, p.colorToMove));
        ASSERT_EQ(expected, actual);
    }

    expected = {
        Move(E8, C8, Move::MoveType::queenCastle),
    };
    for (Position p : bKingCastleQS) {
        actual.clear();
        m.populateKingCastlingMoves(
            actual, p, m.kingDangerSquares(p.pieceBitboards, p.occupied, p.colorToMove));
        ASSERT_EQ(expected, actual);
    }

    expected.clear();
    for (Position p : bKingCastleNoSide) {
        actual.clear();
        m.populateKingCastlingMoves(
            actual, p, m.kingDangerSquares(p.pieceBitboards, p.occupied, p.colorToMove));
        ASSERT_EQ(expected, actual);
    }
}

TEST(move_generator_test, move_generator_rayBetween_test) {
    MoveGenerator m;

    Square origin, target;
    Bitboard expected;
    origin = A1;
    target = H8;
    expected.set(std::vector<Square> {B2, C3, D4, E5, F6, G7});
    ASSERT_EQ(m.rayBetween(origin, target), expected);
    ASSERT_EQ(m.rayBetween(target, origin), expected);

    expected = Bitboard();
    origin = A8;
    target = H1;
    expected.set(std::vector<Square> {B7, C6, D5, E4, F3, G2});
    ASSERT_EQ(m.rayBetween(origin, target), expected);
    ASSERT_EQ(m.rayBetween(target, origin), expected);

    expected = Bitboard();
    origin = C1;
    target = C8;
    expected.set(std::vector<Square> {C2, C3, C4, C5, C6, C7});
    ASSERT_EQ(m.rayBetween(origin, target), expected);
    ASSERT_EQ(m.rayBetween(target, origin), expected);

    expected = Bitboard();
    origin = A7;
    target = H7;
    expected.set(std::vector<Square> {B7, C7, D7, E7, F7, G7});
    ASSERT_EQ(m.rayBetween(origin, target), expected);
    ASSERT_EQ(m.rayBetween(target, origin), expected);

    expected = Bitboard();
    origin = B4;
    target = E7;
    expected.set(std::vector<Square> {C5, D6});
    ASSERT_EQ(m.rayBetween(origin, target), expected);
    ASSERT_EQ(m.rayBetween(target, origin), expected);

    expected = Bitboard();
    origin = G3;
    target = C7;
    expected.set(std::vector<Square> {F4, E5, D6});
    ASSERT_EQ(m.rayBetween(origin, target), expected);
    ASSERT_EQ(m.rayBetween(target, origin), expected);

    expected = Bitboard();
    origin = D3;
    target = F3;
    expected.set(std::vector<Square> {E3});
    ASSERT_EQ(m.rayBetween(origin, target), expected);
    ASSERT_EQ(m.rayBetween(target, origin), expected);

    expected = Bitboard();
    origin = E1;
    target = E7;
    expected.set(std::vector<Square> {E2, E3, E4, E5, E6});
    ASSERT_EQ(m.rayBetween(origin, target), expected);
    ASSERT_EQ(m.rayBetween(target, origin), expected);

    expected = Bitboard();
    origin = B2;
    target = D3;
    ASSERT_EQ(m.rayBetween(origin, target), expected);
    ASSERT_EQ(m.rayBetween(target, origin), expected);

    expected = Bitboard();
    origin = E7;
    target = F3;
    ASSERT_EQ(m.rayBetween(origin, target), expected);
    ASSERT_EQ(m.rayBetween(target, origin), expected);

    expected = Bitboard();
    origin = D4;
    target = D4;
    ASSERT_EQ(m.rayBetween(origin, target), expected);
    ASSERT_EQ(m.rayBetween(target, origin), expected);
}

TEST(move_generator_test, populateMoveList_test) {
    // Example positions from https://peterellisjones.com/posts/generating-legal-chess-moves-efficiently/
    MoveGenerator m;

    Position p = Position("4k3/6N1/5b2/4R3/8/8/8/4K3 b - - 1 1");
    std::vector<Move> expected {
        Move(E8, D7, Move::MoveType::quiet),        
        Move(E8, F7, Move::MoveType::quiet),
        Move(E8, D8, Move::MoveType::quiet),
        Move(E8, F8, Move::MoveType::quiet),
    };
    std::vector<Move> actual;
    m.populateMoveList(actual, p);
    ASSERT_EQ(actual, expected);

    p = Position("4k3/8/6n1/4R3/8/8/8/4K3 b - - 1 1");
    expected.clear();
    expected = {
        Move(E8, D7, Move::MoveType::quiet),        
        Move(E8, F7, Move::MoveType::quiet),
        Move(E8, D8, Move::MoveType::quiet),
        Move(E8, F8, Move::MoveType::quiet),

        Move(G6, E5, Move::MoveType::capture),
        Move(G6, E7, Move::MoveType::quiet),
    };
    actual.clear();
    m.populateMoveList(actual, p);
    ASSERT_EQ(actual, expected);

    p = Position("8/8/8/2k5/3Pp3/8/8/4K3 b - d3 0 1");
    expected.clear();
    expected = {
        Move(C5, D4, Move::MoveType::capture),        
        Move(C5, B4, Move::MoveType::quiet),
        Move(C5, C4, Move::MoveType::quiet),
        Move(C5, B5, Move::MoveType::quiet),
        Move(C5, D5, Move::MoveType::quiet),
        Move(C5, B6, Move::MoveType::quiet),
        Move(C5, C6, Move::MoveType::quiet),
        Move(C5, D6, Move::MoveType::quiet),

        Move(E4, D3, Move::MoveType::epCapture),
    };
    actual.clear();
    m.populateMoveList(actual, p);
    ASSERT_EQ(actual, expected);

    p = Position("8/8/8/1k6/3Pp3/8/8/4KQ2 b - d3 0 1");
    expected.clear();
    expected = {
        Move(B5, A4, Move::MoveType::quiet),
        Move(B5, B4, Move::MoveType::quiet),
        Move(B5, A5, Move::MoveType::quiet),
        Move(B5, B6, Move::MoveType::quiet),
        Move(B5, C6, Move::MoveType::quiet),

        Move(E4, D3, Move::MoveType::epCapture),
    };
    actual.clear();
    m.populateMoveList(actual, p);
    ASSERT_EQ(actual, expected);
}

TEST(move_generator_test, move_generator_populatePinnedPieceMoves_test) {
    MoveGenerator m;

    Bitboard captureMask = Bitboard((uint64_t) 0xFFFFFFFFFFFFFFFF);
    Bitboard pushMask = Bitboard((uint64_t) 0xFFFFFFFFFFFFFFFF);

    // Black pawn pushes, double pushes and captures
    Position p = Position("2k5/2pp4/4B3/8/8/2R5/8/6K1 b - - 0 1");
    std::vector<Move> expected = {
        Move(C7, C5, Move::MoveType::doublePawnPush),
        Move(C7, C6, Move::MoveType::quiet),
        Move(D7, E6, Move::MoveType::capture),
    };
    Bitboard expectedPinned;
    expectedPinned.set(std::vector<Square> {C7, D7});
    std::vector<Move> actual;
    Bitboard actualPinned = m.populatePinnedPieceMoves(actual, p, pushMask, captureMask);
    ASSERT_EQ(actual, expected);
    ASSERT_EQ(actualPinned, expectedPinned);

    //White pawn pushes and captures
    p = Position("8/8/3r4/q7/1P6/3P4/3K1P1r/8 w - - 0 1");
    expected.clear();
    expected = {
        Move(B4, A5, Move::MoveType::capture),
        Move(D3, D4, Move::MoveType::quiet),
    };
    expectedPinned = Bitboard();
    expectedPinned.set(std::vector<Square> {B4, D3, F2});
    actual.clear();
    actualPinned = m.populatePinnedPieceMoves(actual, p, pushMask, captureMask);
    ASSERT_EQ(actual, expected);
    ASSERT_EQ(actualPinned, expectedPinned);

    // Black EP Capture
    p = Position("8/8/6k1/8/3Pp3/8/8/1Q5K b - d3 0 1");
    expected.clear();
    expected = {Move(E4, D3, Move::MoveType::epCapture)};
    expectedPinned = Bitboard();
    expectedPinned.set(std::vector<Square> {E4});
    actual.clear();
    actualPinned = m.populatePinnedPieceMoves(actual, p, pushMask, captureMask);
    ASSERT_EQ(actual, expected);
    ASSERT_EQ(actualPinned, expectedPinned);

    // White EP Capture
    p = Position("2k5/6b1/8/4Pp2/8/8/1K6/8 w - f6 0 2");
    expected.clear();
    expected = {Move(E5, F6, Move::MoveType::epCapture)};
    expectedPinned = Bitboard();
    expectedPinned.set(std::vector<Square> {E5});
    actual.clear();
    actualPinned = m.populatePinnedPieceMoves(actual, p, pushMask, captureMask);
    ASSERT_EQ(actual, expected);
    ASSERT_EQ(actualPinned, expectedPinned);

    // Knights
    p = Position("8/3k4/8/3n4/6n1/7B/8/3Q4 b - - 0 1");
    expected.clear();
    expectedPinned = Bitboard();
    expectedPinned.set(std::vector<Square> {D5, G4});
    actual.clear();
    actualPinned = m.populatePinnedPieceMoves(actual, p, pushMask, captureMask);
    ASSERT_EQ(actual, expected);
    ASSERT_EQ(actualPinned, expectedPinned);

    // Bishops
    p = Position("8/2r5/6q1/2B5/4B3/8/2K5/8 w - - 0 1");
    expected.clear();
    expected = {
        Move(E4, G6, Move::MoveType::capture),
        Move(E4, D3, Move::MoveType::quiet),
        Move(E4, F5, Move::MoveType::quiet),
    };
    expectedPinned = Bitboard();
    expectedPinned.set(std::vector<Square> {C5, E4});
    actual.clear();
    actualPinned = m.populatePinnedPieceMoves(actual, p, pushMask, captureMask);
    ASSERT_EQ(actual, expected);
    ASSERT_EQ(actualPinned, expectedPinned);

    // Rooks
    p = Position("8/4Rrk1/8/3N2r1/3r4/6Q1/1Q6/4K3 b - - 0 1");
    expected.clear();
    expected = {
        Move(G5, G3, Move::MoveType::capture),
        Move(G5, G4, Move::MoveType::quiet),
        Move(G5, G6, Move::MoveType::quiet),
        Move(F7, E7, Move::MoveType::capture),
    };
    expectedPinned = Bitboard();
    expectedPinned.set(std::vector<Square> {G5, F7, D4});
    actual.clear();
    actualPinned = m.populatePinnedPieceMoves(actual, p, pushMask, captureMask);
    ASSERT_EQ(actual, expected);
    ASSERT_EQ(actualPinned, expectedPinned);

    // Queen
    p = Position("8/3r4/1q2b3/2QQ4/3K1Q1q/8/1Q3n2/b7 w - - 0 1");
    expected.clear();
    expected = {
        Move(B2, A1, Move::MoveType::capture),
        Move(B2, C3, Move::MoveType::quiet),
        Move(F4, H4, Move::MoveType::capture),
        Move(F4, E4, Move::MoveType::quiet),
        Move(F4, G4, Move::MoveType::quiet),
        Move(C5, B6, Move::MoveType::capture),
        Move(D5, D7, Move::MoveType::capture),
        Move(D5, D6, Move::MoveType::quiet),
    };
    expectedPinned = Bitboard();
    expectedPinned.set(std::vector<Square> {B2, F4, C5, D5});
    actual.clear();
    actualPinned = m.populatePinnedPieceMoves(actual, p, pushMask, captureMask);
    ASSERT_EQ(actual, expected);
    ASSERT_EQ(actualPinned, expectedPinned);
}

TEST(move_generator_test, move_generator_populateMoveList_pinnedPieces_singleCheck_test) {
    MoveGenerator m;
    Position p = Position("4B1k1/b2r2q1/8/1pP1R3/2NK2Qq/8/5N2/6q1 w - b6 0 1");

    std::vector<Move> expected = {
        // King moves out of check
        Move(D4, C3, Move::MoveType::quiet),
        Move(D4, E3, Move::MoveType::quiet),
        Move(D4, E4, Move::MoveType::quiet),
        // Knight blocks check
        Move(C4, D6, Move::MoveType::quiet),
        // Bishop captures checker
        Move(E8, D7, Move::MoveType::capture),
    };
    std::vector<Move> actual;
    m.populateMoveList(actual, p);
    ASSERT_EQ(actual, expected);
}

