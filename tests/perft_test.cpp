#include "gtest/gtest.h"
#include "../src/move_generator.h"
#include "../src/position.h"

// Example positions taken from https://www.chessprogramming.org/Perft_Results

TEST(perft_test, perft_startPosition_test) {
    Position startPos;
    std::map<Move::MoveType, int> map;
    MoveGenerator m;

    ASSERT_EQ(startPos.perft(1, m), 20);
    ASSERT_EQ(startPos.perft(2, m), 400);
    ASSERT_EQ(startPos.perft(3, m), 8902);
    ASSERT_EQ(startPos.perft(4, m), 197281);
    ASSERT_EQ(startPos.perft(5, m), 4865609);
    ASSERT_EQ(startPos.perft(6, m), 119060324);
}

TEST(perft_test, perft_position2_test) {
    Position position2 = Position("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
    MoveGenerator m;

    ASSERT_EQ(position2.perft(1, m), 48);
    ASSERT_EQ(position2.perft(2, m), 2039);
    ASSERT_EQ(position2.perft(3, m), 97862);
    ASSERT_EQ(position2.perft(4, m), 4085603);
    ASSERT_EQ(position2.perft(5, m), 193690690);
}

TEST(perft_test, perft_position3_test) {
    Position position3 = Position("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 5");
    MoveGenerator m;

    ASSERT_EQ(position3.perft(1, m), 14);
    ASSERT_EQ(position3.perft(2, m), 191);
    ASSERT_EQ(position3.perft(3, m), 2812);
    ASSERT_EQ(position3.perft(4, m), 43238);
    ASSERT_EQ(position3.perft(5, m), 674624);
    ASSERT_EQ(position3.perft(6, m), 11030083);
}

TEST(perft_test, perft_position4_test) {
    Position position4 = Position("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
    MoveGenerator m;
    
    ASSERT_EQ(position4.perft(1, m), 6);
    ASSERT_EQ(position4.perft(2, m), 264);
    ASSERT_EQ(position4.perft(3, m), 9467);
    ASSERT_EQ(position4.perft(4, m), 422333);
    ASSERT_EQ(position4.perft(5, m), 15833292);
    ASSERT_EQ(position4.perft(6, m), 706045033);
}

TEST(perft_test, perft_position5_test) {
    Position position5 = Position("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");
    MoveGenerator m;

    ASSERT_EQ(position5.perft(1, m), 44);
    ASSERT_EQ(position5.perft(2, m), 1486);
    ASSERT_EQ(position5.perft(3, m), 62379);
    ASSERT_EQ(position5.perft(4, m), 2103487);
    ASSERT_EQ(position5.perft(5, m), 89941194);
}

TEST(perft_test, perft_position6_test) {
    Position position6 = Position("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
    MoveGenerator m;

    ASSERT_EQ(position6.perft(1, m), 46);
    ASSERT_EQ(position6.perft(2, m), 2079);
    ASSERT_EQ(position6.perft(3, m), 89890);
    ASSERT_EQ(position6.perft(4, m), 3894594);
    ASSERT_EQ(position6.perft(5, m), 164075551);
}