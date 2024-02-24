#include "../src/castling_rights.h"
#include "gtest/gtest.h"
#include "../src/move_generator.h"
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