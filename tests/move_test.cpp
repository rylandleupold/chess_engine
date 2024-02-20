#include "../src/move.h"
#include "../src/square.h"
#include "gtest/gtest.h"
#include <bitset>

TEST(move_test, move_constructor_test) {
    std::bitset<16> expected("1011110111000011");
    Move move1(Square::H7, Square::D1, Move::MoveType::queenPromo);
    Move move2(expected.to_ulong());
    ASSERT_EQ(move1.moveBits, expected.to_ulong());
    ASSERT_EQ(move2.moveBits, expected.to_ulong());
}

TEST(move_test, move_operatorEquals_test) {
    Move move1 = Move(Square::A2, Square::D2, Move::MoveType::quiet);
    Move move2 = Move(Square::B3, Square::F3, Move::MoveType::capture);

    ASSERT_NE(move1.moveBits, move2.moveBits);
    move1 = move2;
    ASSERT_EQ(move1.moveBits, move2.moveBits);
    ASSERT_NE(&move1, &move2);
}

TEST(move_test, move_getTarget_test) {
    Move move1(std::bitset<16>("0000010110000110").to_ulong());
    ASSERT_EQ(move1.getTarget(), Square::G1);

    Move move2(std::bitset<16>("0000000000111111").to_ulong());
    ASSERT_EQ(move2.getTarget(), Square::H8);
}

TEST(move_test, move_getOrigin_test) {
    Move move1(std::bitset<16>("0000010100000000").to_ulong());
    ASSERT_EQ(move1.getOrigin(), Square::E3);

    Move move2(std::bitset<16>("0000110101000000").to_ulong());
    ASSERT_EQ(move2.getOrigin(), Square::F7);
}

TEST(move_test, move_getMoveType_test) {
    Move move1(std::bitset<16>("1011000000000000").to_ulong());
    ASSERT_EQ(move1.getMoveType(), Move::MoveType::queenPromo);

    Move move2(std::bitset<16>("0101000000000000").to_ulong());
    ASSERT_EQ(move2.getMoveType(), Move::MoveType::epCapture);
}

TEST(move_test, move_setTarget_test) {
    Move move(Square::A1, Square::H8, Move::MoveType::quiet);
    ASSERT_EQ(move.getTarget(), Square::H8);
    move.setTarget(Square::F6);
    ASSERT_EQ(move.getTarget(), Square::F6);
    ASSERT_EQ(move.getOrigin(), Square::A1);
}

TEST(move_test, move_setOrigin_test) {
    Move move(Square::A1, Square::H8, Move::MoveType::quiet);
    ASSERT_EQ(move.getOrigin(), Square::A1);
    move.setOrigin(Square::G7);
    ASSERT_EQ(move.getOrigin(), Square::G7);
    ASSERT_EQ(move.getTarget(), Square::H8);
}

TEST(move_test, move_setMoveType_test) {
    Move move(Square::A1, Square::H8, Move::MoveType::quiet);
    ASSERT_EQ(move.getMoveType(), Move::MoveType::quiet);
    move.setMoveType(Move::MoveType::capture);
    ASSERT_EQ(move.getMoveType(), Move::MoveType::capture);
    ASSERT_EQ(move.getOrigin(), Square::A1);
    ASSERT_EQ(move.getTarget(), Square::H8);
}

TEST(move_test, move_isCapture_test) {
    Move move(std::bitset<16>("0100000000000000").to_ulong());
    ASSERT_TRUE(move.isCapture());
    move.setMoveType(Move::MoveType::epCapture);
    ASSERT_TRUE(move.isCapture());
    move.setMoveType(Move::MoveType::queenPromoCapture);
    ASSERT_TRUE(move.isCapture());
    move.setMoveType(Move::MoveType::quiet);
    ASSERT_FALSE(move.isCapture());
    move.setMoveType(Move::MoveType::doublePawnPush);
    ASSERT_FALSE(move.isCapture());
    move.setMoveType(Move::MoveType::queenPromo);
    ASSERT_FALSE(move.isCapture());
}

TEST(move_test, move_isPromotion_test) {
    Move move(std::bitset<16>("1000000000000000").to_ulong());
    ASSERT_TRUE(move.isPromotion());
    move.setMoveType(Move::MoveType::bishopPromoCapture);
    ASSERT_TRUE(move.isPromotion());
    move.setMoveType(Move::MoveType::queenCastle);
    ASSERT_FALSE(move.isPromotion());
    move.setMoveType(Move::MoveType::capture);
    ASSERT_FALSE(move.isPromotion());
}
