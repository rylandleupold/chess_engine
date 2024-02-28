#include "../src/castling_rights.h"
#include "gtest/gtest.h"
#include <bitset>
#include <set>

TEST(castling_rights_test, castling_rights_canCastle_test) {
    CastlingRights crAll;
    ASSERT_TRUE(crAll.canCastle(true, true));
    ASSERT_TRUE(crAll.canCastle(true, false));
    ASSERT_TRUE(crAll.canCastle(false, true));
    ASSERT_TRUE(crAll.canCastle(false, false));

    CastlingRights crNone(std::bitset<4>("0000"));

    ASSERT_FALSE(crNone.canCastle(true, true));
    ASSERT_FALSE(crNone.canCastle(true, false));
    ASSERT_FALSE(crNone.canCastle(false, true));
    ASSERT_FALSE(crNone.canCastle(false, false));
}

TEST(castling_rights_test, castling_rights_setCastlingRight_test) {
    CastlingRights cr(std::bitset<4>("0000"));
    ASSERT_FALSE(cr.canCastle(true, true));
    ASSERT_FALSE(cr.canCastle(true, false));
    ASSERT_FALSE(cr.canCastle(false, true));
    ASSERT_FALSE(cr.canCastle(false, false));

    cr.setCastlingRight(true, true);
    ASSERT_TRUE(cr.canCastle(true, true));
    ASSERT_FALSE(cr.canCastle(true, false));
    ASSERT_FALSE(cr.canCastle(false, true));
    ASSERT_FALSE(cr.canCastle(false, false));

    cr.setCastlingRight(true, false);
    ASSERT_TRUE(cr.canCastle(true, false));
    ASSERT_FALSE(cr.canCastle(false, true));
    ASSERT_FALSE(cr.canCastle(false, false));

    cr.setCastlingRight(false, true);
    ASSERT_TRUE(cr.canCastle(false, true));
    ASSERT_FALSE(cr.canCastle(false, false));

    cr.setCastlingRight(false, false);
    ASSERT_TRUE(cr.canCastle(false, false));
}

TEST(castling_rights_test, castling_rights_unsetCastlingRight_test) {
    CastlingRights cr(std::bitset<4>("1111"));
    ASSERT_TRUE(cr.canCastle(true, true));
    ASSERT_TRUE(cr.canCastle(true, false));
    ASSERT_TRUE(cr.canCastle(false, true));
    ASSERT_TRUE(cr.canCastle(false, false));

    cr.unsetCastlingRight(true, true);
    ASSERT_FALSE(cr.canCastle(true, true));

    cr.unsetCastlingRight(true, false);
    ASSERT_FALSE(cr.canCastle(true, false));

    cr.unsetCastlingRight(false, true);
    ASSERT_FALSE(cr.canCastle(false, true));

    cr.unsetCastlingRight(false, false);
    ASSERT_FALSE(cr.canCastle(false, false));
}

TEST(castling_rights_test, castling_rights_toString_test) {
    CastlingRights crAll;
    ASSERT_EQ(crAll.toString(), "qkQK");

    CastlingRights crNone = CastlingRights(std::bitset<4>("0000"));
    ASSERT_EQ(crNone.toString(), "----");

    CastlingRights cr3;
    cr3.unsetCastlingRight(true, false);
    cr3.unsetCastlingRight(false, false);
    ASSERT_EQ(cr3.toString(), "-k-K");
}

TEST(castling_rights_test, castling_rights_operatorEquals_test) {
    CastlingRights crAll;
    CastlingRights crNone = CastlingRights(std::bitset<4>("0000"));
    ASSERT_NE(crAll, crNone);

    CastlingRights crAll2 = CastlingRights(std::bitset<4>("1111"));
    ASSERT_EQ(crAll, crAll2);

    crAll.unsetCastlingRight(true, true);
    crAll.unsetCastlingRight(false, true);
    crNone.setCastlingRight(true, false);
    crNone.setCastlingRight(false, false);
    ASSERT_EQ(crAll, crNone);
}

