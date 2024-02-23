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
    ASSERT_EQ(m.kingMoves(Square::A1), kingCorner);

    Bitboard kingRank1;
    kingRank1.set(Square::C1);
    kingRank1.set(Square::C2);
    kingRank1.set(Square::D2);
    kingRank1.set(Square::E2);
    kingRank1.set(Square::E1);
    ASSERT_EQ(m.kingMoves(Square::D1), kingRank1);

    Bitboard kingRank8;
    kingRank8.set(Square::D8);
    kingRank8.set(Square::D7);
    kingRank8.set(Square::E7);
    kingRank8.set(Square::F7);
    kingRank8.set(Square::F8);
    ASSERT_EQ(m.kingMoves(Square::E8), kingRank8);

    Bitboard kingFileA;
    kingFileA.set(Square::A7);
    kingFileA.set(Square::B7);
    kingFileA.set(Square::B6);
    kingFileA.set(Square::B5);
    kingFileA.set(Square::A5);

    ASSERT_EQ(m.kingMoves(Square::A6), kingFileA);

    Bitboard kingFileH;
    kingFileH.set(Square::H7);
    kingFileH.set(Square::G7);
    kingFileH.set(Square::G6);
    kingFileH.set(Square::G5);
    kingFileH.set(Square::H5);
    ASSERT_EQ(m.kingMoves(Square::H6), kingFileH);

    Bitboard kingMiddle;
    kingMiddle.set(Square::B5);
    kingMiddle.set(Square::B6);
    kingMiddle.set(Square::C6);
    kingMiddle.set(Square::D6);
    kingMiddle.set(Square::D5);
    kingMiddle.set(Square::D4);
    kingMiddle.set(Square::C4);
    kingMiddle.set(Square::B4);
    ASSERT_EQ(m.kingMoves(Square::C5), kingMiddle);
}

TEST(move_generator_test, move_generator_knight_moves_test) {
    MoveGenerator m;
    Bitboard knightCorner;
    knightCorner.set(Square::G6);
    knightCorner.set(Square::F7);
    ASSERT_EQ(m.knightMoves(Square::H8), knightCorner);

    Bitboard knightRank1;
    knightRank1.set(Square::D3);
    knightRank1.set(Square::F3);
    knightRank1.set(Square::C2);
    knightRank1.set(Square::G2);
    ASSERT_EQ(m.knightMoves(Square::E1), knightRank1);

    Bitboard knightRank8;
    knightRank8.set(Square::B7);
    knightRank8.set(Square::F7);
    knightRank8.set(Square::C6);
    knightRank8.set(Square::E6);
    ASSERT_EQ(m.knightMoves(Square::D8), knightRank8);

    Bitboard knightFileA;
    knightFileA.set(Square::B1);
    knightFileA.set(Square::B5);
    knightFileA.set(Square::C2);
    knightFileA.set(Square::C4);
    ASSERT_EQ(m.knightMoves(Square::A3), knightFileA);

    Bitboard knightFileH;
    knightFileH.set(Square::G8);
    knightFileH.set(Square::G4);
    knightFileH.set(Square::F7);
    knightFileH.set(Square::F5);
    ASSERT_EQ(m.knightMoves(Square::H6), knightFileH);

    Bitboard knightFileG;
    knightFileG.set(Square::H7);
    knightFileG.set(Square::H3);
    knightFileG.set(Square::F7);
    knightFileG.set(Square::F3);
    knightFileG.set(Square::E4);
    knightFileG.set(Square::E6);
    ASSERT_EQ(m.knightMoves(Square::G5), knightFileG);

    Bitboard knightRank2;
    knightRank2.set(Square::A1);
    knightRank2.set(Square::A3);
    knightRank2.set(Square::E1);
    knightRank2.set(Square::E3);
    knightRank2.set(Square::B4);
    knightRank2.set(Square::D4);
    ASSERT_EQ(m.knightMoves(Square::C2), knightRank2);

    Bitboard knightMiddle;
    knightMiddle.set(Square::C7);
    knightMiddle.set(Square::E7);
    knightMiddle.set(Square::C3);
    knightMiddle.set(Square::E3);
    knightMiddle.set(Square::F6);
    knightMiddle.set(Square::F4);
    knightMiddle.set(Square::B6);
    knightMiddle.set(Square::B4);
    ASSERT_EQ(m.knightMoves(Square::D5), knightMiddle);
}