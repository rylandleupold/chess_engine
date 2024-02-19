#include "../src/bitboard.h"
#include "../src/square.h"
#include "gtest/gtest.h"
#include <bitset>
#include <set>

TEST(bitboard_test, bitboard_isSet_test)
{
    std::bitset<64> bitset;
    std::set<Square> setSquares = {Square::A1, Square::H8, Square::F7, Square::B3};
    for (Square s : setSquares) {
        bitset.set(s);
    }
    
    Bitboard b((uint64_t) bitset.to_ullong());

    ASSERT_NE((uint64_t) 0ULL, b.bits);
    for (int i=0; i<64; i++) {
        Square s = Square(i);
        if (setSquares.find(s) != setSquares.end()) {
            ASSERT_TRUE(b.isSet(s));
        } else {
            ASSERT_FALSE(b.isSet(s));
        }
    }
}


TEST(bitboard_test, bitboard_set_test) {
    std::set<Square> setSquares = {Square::A1, Square::H8, Square::C5, Square::E6};
    std::bitset<64> expectedBits;
    Bitboard bitboard;

    for (Square s : setSquares) {
        expectedBits.set(s);
        bitboard.set(s);
        ASSERT_TRUE(bitboard.isSet(s));
    }
    ASSERT_EQ(bitboard.bits, expectedBits.to_ullong());
}

TEST(bitboard_test, bitboard_set_multiple_times_test) {
    std::set<Square> setSquares = {Square::A1, Square::H8, Square::C5, Square::E6};
    std::bitset<64> expectedBits;
    Bitboard bitboard;

    for (Square s : setSquares) {
        expectedBits.set(s);
        bitboard.set(s);
        bitboard.set(s);
        ASSERT_TRUE(bitboard.isSet(s));
    }
    ASSERT_EQ(bitboard.bits, expectedBits.to_ullong());
}

TEST(bitboard_test, bitboard_isEmpty_test) {
    Bitboard b1;
    ASSERT_TRUE(b1.isEmpty());

    Bitboard b2(0ULL);
    ASSERT_TRUE(b2.isEmpty());

    Bitboard b3(12ULL);
    ASSERT_FALSE(b3.isEmpty());    
}

TEST(bitboard_test, bitboard_lsb_test) {
    std::bitset<64> bitset;
    bitset.set(Square::B2);
    bitset.set(Square::G4);

    Bitboard bitboard((uint64_t) bitset.to_ullong());

    // Test twice to ensure lsb is not cleared when checking
    ASSERT_EQ(bitboard.lsb(), Square::B2);
    ASSERT_EQ(bitboard.lsb(), Square::B2);
}

TEST(bitboard_test, bitboard_empty_lsb_test) {
    Bitboard bitboard;
    // Test twice to ensure lsb is not cleared when checking
    ASSERT_EQ(bitboard.lsb(), Square::noSquare);
    ASSERT_EQ(bitboard.lsb(), Square::noSquare);
}

TEST(bitboard_test, bitboard_msb_test) {
    std::bitset<64> bitset;
    bitset.set(Square::C2);
    bitset.set(Square::G8);

    Bitboard bitboard((uint64_t) bitset.to_ullong());

    // Test twice to ensure msb is not cleared when checking
    ASSERT_EQ(bitboard.msb(), Square::G8);
    ASSERT_EQ(bitboard.msb(), Square::G8);
}

TEST(bitboard_test, bitboard_empty_msb_test) {
    Bitboard bitboard;
    // Test twice to ensure lsb is not cleared when checking
    ASSERT_EQ(bitboard.msb(), Square::noSquare);
    ASSERT_EQ(bitboard.msb(), Square::noSquare);
}

TEST(bitboard_test, bitboard_popCount_test) {
    std::bitset<64> bitset;
    bitset.set(Square::C2);
    bitset.set(Square::G8);
    bitset.set(Square::H3);
    bitset.set(Square::B7);

    Bitboard bitboard((uint64_t) bitset.to_ullong());

    // Test twice to ensure popCount does not alter bits
    ASSERT_EQ(bitboard.popCount(), 4);
    ASSERT_EQ(bitboard.popCount(), 4);

    Bitboard emptyBitboard;
    ASSERT_EQ(emptyBitboard.popCount(), 0);
}



