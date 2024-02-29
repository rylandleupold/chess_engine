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

TEST(bitboard_test, bitboard_setVector_test) {
    std::vector<Square> setSquares = {Square::A1, Square::H8, Square::C5, Square::E6};
    Bitboard expected;
    expected.set(Square::A1);
    expected.set(Square::H8);
    expected.set(Square::C5);
    expected.set(Square::E6);

    Bitboard bitboard;
    bitboard.set(setSquares);
    ASSERT_EQ(bitboard, expected);
}

TEST(bitboard_test, bitboard_unset_test) {
    Bitboard b(Square::A1);
    b.unset(Square::A1);
    ASSERT_EQ(b, Bitboard());

    Bitboard b2(Square::H8);
    b2.unset(Square::H8);
    ASSERT_EQ(b2, Bitboard());

    Bitboard b3;
    b3.set(std::vector<Square> {A2, C3, D5, E7, E8, F6});
    b3.unset(Square::F6);
    b3.unset(Square::C3);
    b3.unset(Square::E7);
    b3.unset(Square::F6);

    ASSERT_TRUE(b3.isSet(Square::A2));
    ASSERT_TRUE(b3.isSet(Square::D5));
    ASSERT_TRUE(b3.isSet(Square::E8));
    ASSERT_FALSE(b3.isSet(Square::C3));
    ASSERT_FALSE(b3.isSet(Square::E7));
    ASSERT_FALSE(b3.isSet(Square::F6));

    Bitboard b4(Square::H8);
    b4.unset(Square::noSquare);
    ASSERT_EQ(b4, Bitboard(Square::H8));
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

TEST(bitboard_test, bitboard_clearLsb_test) {
    std::bitset<64> bitset;
    bitset.set(Square::B3);
    bitset.set(Square::G3);
    bitset.set(Square::H8);

    Bitboard bitboard((uint64_t) bitset.to_ullong());

    ASSERT_EQ(bitboard.lsb(), Square::B3);
    bitboard.clearLsb();
    ASSERT_EQ(bitboard.lsb(), Square::G3);
    bitboard.clearLsb();
    ASSERT_EQ(bitboard.lsb(), Square::H8);
    bitboard.clearLsb();
    ASSERT_EQ(bitboard.lsb(), Square::noSquare);
    bitboard.clearLsb();
    ASSERT_EQ(bitboard.lsb(), Square::noSquare);
}

TEST(bitboard_test, bitboard_getSetSquares_test) {
    Bitboard bitboard;
    bitboard.set(Square::A1);
    bitboard.set(Square::B5);
    bitboard.set(Square::D4);
    bitboard.set(Square::G6);
    bitboard.set(Square::H8);

    std::vector<Square> expected = {
        Square::A1,
        Square::D4,
        Square::B5,
        Square::G6,
        Square::H8
    };
    std::vector<Square> actual1 = bitboard.getSetSquares();
    ASSERT_EQ(actual1, expected);
    ASSERT_EQ(actual1.size(), 5);

    // Make sure getSetSquares() does not clear bits
    std::vector<Square> actual2 = bitboard.getSetSquares();
    ASSERT_EQ(actual2, expected);
    ASSERT_EQ(actual2.size(), 5);
    ASSERT_FALSE(bitboard.isEmpty());
}

TEST(bitboard_test, bitboard_shiftN_test) {
    Bitboard bitboard1;
    bitboard1.set(Square::A1);
    ASSERT_EQ(bitboard1.shiftN(), Bitboard(Square::A2));
    ASSERT_EQ(bitboard1, Bitboard(Square::A1));

    Bitboard bitboard2;
    bitboard2.set(Square::H8);
    ASSERT_EQ(bitboard2.shiftN(), Bitboard(0));

    Bitboard bitboard3;
    bitboard3.set(Square::B2);
    bitboard3.set(Square::D3);
    bitboard3.set(Square::F4);
    bitboard3.set(Square::G8);

    Bitboard expected;
    expected.set(Square::B3);
    expected.set(Square::D4);
    expected.set(Square::F5);

    ASSERT_EQ(bitboard3.shiftN(), expected);
}

TEST(bitboard_test, bitboard_shiftS_test) {
    Bitboard bitboard1;
    bitboard1.set(Square::A8);
    ASSERT_EQ(bitboard1.shiftS(), Bitboard(Square::A7));
    ASSERT_EQ(bitboard1, Bitboard(Square::A8));

    Bitboard bitboard2;
    bitboard2.set(Square::H1);
    ASSERT_EQ(bitboard2.shiftS(), Bitboard(0));

    Bitboard bitboard3;
    bitboard3.set(Square::B2);
    bitboard3.set(Square::D3);
    bitboard3.set(Square::F4);
    bitboard3.set(Square::G1);

    Bitboard expected;
    expected.set(Square::B1);
    expected.set(Square::D2);
    expected.set(Square::F3);

    ASSERT_EQ(bitboard3.shiftS(), expected);
}

TEST(bitboard_test, bitboard_shiftE_test) {
    Bitboard bitboard1;
    bitboard1.set(Square::A5);
    ASSERT_EQ(bitboard1.shiftE(), Bitboard(Square::B5));
    ASSERT_EQ(bitboard1, Bitboard(Square::A5));

    Bitboard bitboard2;
    bitboard2.set(Square::G4);
    ASSERT_EQ(bitboard2.shiftE(), Bitboard(Square::H4));

    Bitboard bitboard3;
    bitboard3.set(Square::H4);
    ASSERT_EQ(bitboard3.shiftE(), Bitboard(0));

    Bitboard bitboard4;
    bitboard4.set(Square::B2);
    bitboard4.set(Square::D3);
    bitboard4.set(Square::F4);
    bitboard4.set(Square::H1);

    Bitboard expected;
    expected.set(Square::C2);
    expected.set(Square::E3);
    expected.set(Square::G4);

    ASSERT_EQ(bitboard4.shiftE(), expected);
}

TEST(bitboard_test, bitboard_shiftW_test) {
    Bitboard bitboard1;
    bitboard1.set(Square::B5);
    ASSERT_EQ(bitboard1.shiftW(), Bitboard(Square::A5));
    ASSERT_EQ(bitboard1, Bitboard(Square::B5));

    Bitboard bitboard2;
    bitboard2.set(Square::H4);
    ASSERT_EQ(bitboard2.shiftW(), Bitboard(Square::G4));

    Bitboard bitboard3;
    bitboard3.set(Square::A4);
    ASSERT_EQ(bitboard3.shiftW(), Bitboard(0));

    Bitboard bitboard4;
    bitboard4.set(Square::B2);
    bitboard4.set(Square::D3);
    bitboard4.set(Square::F4);
    bitboard4.set(Square::A1);

    Bitboard expected;
    expected.set(Square::A2);
    expected.set(Square::C3);
    expected.set(Square::E4);

    ASSERT_EQ(bitboard4.shiftW(), expected);
}

TEST(bitboard_test, bitboard_shiftNE_test) {
    Bitboard bitboard1;
    bitboard1.set(Square::A7);
    ASSERT_EQ(bitboard1.shiftNE(), Bitboard(Square::B8));
    ASSERT_EQ(bitboard1, Bitboard(Square::A7));

    Bitboard bitboard2;
    bitboard2.set(Square::C1);
    ASSERT_EQ(bitboard2.shiftNE(), Bitboard(Square::D2));

    Bitboard bitboard3;
    bitboard3.set(Square::H4);
    ASSERT_EQ(bitboard3.shiftNE(), Bitboard(0));

    Bitboard bitboard4;
    bitboard4.set(Square::B2);
    bitboard4.set(Square::D3);
    bitboard4.set(Square::F4);
    bitboard4.set(Square::H1);

    Bitboard expected;
    expected.set(Square::C3);
    expected.set(Square::E4);
    expected.set(Square::G5);

    ASSERT_EQ(bitboard4.shiftNE(), expected);
}

TEST(bitboard_test, bitboard_shiftNW_test) {
    Bitboard bitboard1;
    bitboard1.set(Square::H7);
    ASSERT_EQ(bitboard1.shiftNW(), Bitboard(Square::G8));
    ASSERT_EQ(bitboard1, Bitboard(Square::H7));

    Bitboard bitboard2;
    bitboard2.set(Square::C1);
    ASSERT_EQ(bitboard2.shiftNW(), Bitboard(Square::B2));

    Bitboard bitboard3;
    bitboard3.set(Square::A4);
    ASSERT_EQ(bitboard3.shiftNW(), Bitboard(0));

    Bitboard bitboard4;
    bitboard4.set(Square::B2);
    bitboard4.set(Square::D3);
    bitboard4.set(Square::F4);
    bitboard4.set(Square::A1);

    Bitboard expected;
    expected.set(Square::A3);
    expected.set(Square::C4);
    expected.set(Square::E5);

    ASSERT_EQ(bitboard4.shiftNW(), expected);
}

TEST(bitboard_test, bitboard_shiftSE_test) {
    Bitboard bitboard1;
    bitboard1.set(Square::A7);
    ASSERT_EQ(bitboard1.shiftSE(), Bitboard(Square::B6));
    ASSERT_EQ(bitboard1, Bitboard(Square::A7));

    Bitboard bitboard2;
    bitboard2.set(Square::C8);
    ASSERT_EQ(bitboard2.shiftSE(), Bitboard(Square::D7));

    Bitboard bitboard3;
    bitboard3.set(Square::H2);
    ASSERT_EQ(bitboard3.shiftSE(), Bitboard(0));

    Bitboard bitboard4;
    bitboard4.set(Square::B2);
    bitboard4.set(Square::D3);
    bitboard4.set(Square::F4);
    bitboard4.set(Square::H8);

    Bitboard expected;
    expected.set(Square::C1);
    expected.set(Square::E2);
    expected.set(Square::G3);

    ASSERT_EQ(bitboard4.shiftSE(), expected);
}

TEST(bitboard_test, bitboard_shiftSW_test) {
    Bitboard bitboard1;
    bitboard1.set(Square::H7);
    ASSERT_EQ(bitboard1.shiftSW(), Bitboard(Square::G6));
    ASSERT_EQ(bitboard1, Bitboard(Square::H7));

    Bitboard bitboard2;
    bitboard2.set(Square::B8);
    ASSERT_EQ(bitboard2.shiftSW(), Bitboard(Square::A7));

    Bitboard bitboard3;
    bitboard3.set(Square::A5);
    ASSERT_EQ(bitboard3.shiftSW(), Bitboard(0));

    Bitboard bitboard4;
    bitboard4.set(Square::B2);
    bitboard4.set(Square::D3);
    bitboard4.set(Square::F4);
    bitboard4.set(Square::A2);

    Bitboard expected;
    expected.set(Square::A1);
    expected.set(Square::C2);
    expected.set(Square::E3);

    ASSERT_EQ(bitboard4.shiftSW(), expected);
}

TEST(bitboard_test, bitboard_operatorEquals_test) {
    Bitboard b1(0ULL);
    Bitboard b2;
    ASSERT_TRUE(b1 == b2);

    Bitboard b3;
    b3.set(Square::C5);
    Bitboard b4(Square:: C5);
    ASSERT_TRUE(b3 == b4);
    ASSERT_FALSE(b1 == b3);

    Bitboard b5(Square::A6);
    Bitboard b6(Square::H7);
    b5 = b6;
    ASSERT_EQ(b5, b6);
    ASSERT_EQ(b5.lsb(), Square::H7);
    ASSERT_EQ(b5.popCount(), 1);
    ASSERT_EQ(b6.lsb(), Square::H7);
    ASSERT_EQ(b6.popCount(), 1);
}

TEST(bitboard_test, bitboard_operatorBitwiseOr_test) {
    Bitboard b1(Square::A1);
    Bitboard b2(Square::H8);

    Bitboard expected(Square::A1);
    expected.set(Square::H8);

    ASSERT_EQ(b1 | b2, expected);
    
    b1 |= b2;
    ASSERT_EQ(b1, expected);

    ASSERT_EQ(Bitboard() | Bitboard(), Bitboard(0ULL));
}

TEST(bitboard_test, bitboard_operatorBitwiseAnd_test) {
    Bitboard b1(Square::A8);
    b1.set(Square::C5);
    Bitboard b2(Square::H1);
    b2.set(Square::C5);

    Bitboard expected(Square::C5);

    ASSERT_EQ(b1 & b2, expected);
    ASSERT_TRUE(b1.isSet(Square::A8));
    ASSERT_TRUE(b2.isSet(Square::H1));

    b1 &= b2;
    ASSERT_EQ(b1, expected);
    ASSERT_EQ(Bitboard() & Bitboard(), Bitboard(0ULL));
}

TEST(bitboard_test, bitboard_operatorBitwiseXOr_test) {
    Bitboard b1(Square::A8);
    b1.set(Square::C5);
    Bitboard b2(Square::H1);
    b2.set(Square::C5);

    Bitboard expected(Square::A8);
    expected.set(Square::H1);

    ASSERT_EQ(b1 ^ b2, expected);
    ASSERT_TRUE(b1.isSet(Square::C5));
    ASSERT_TRUE(b2.isSet(Square::C5));

    b1 ^= b2;
    ASSERT_EQ(b1, expected);
    ASSERT_EQ(Bitboard() ^ Bitboard(), Bitboard(0ULL));
}

TEST(bitboard_test, bitboard_operatorBitwiseNot_test) {
    Bitboard emptyBitboard;
    Bitboard fullBitboard;
    for (Square s=Square::A1; s<=Square::H8; s=Square(s+1)) {
        fullBitboard.set(s);
    }

    ASSERT_EQ(~emptyBitboard, fullBitboard);
    ASSERT_EQ(~fullBitboard, emptyBitboard);
}
