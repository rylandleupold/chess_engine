#include "gtest/gtest.h"
#include "../src/position.h"

TEST(position_test, position_constructor_test) {
    Position p1;
    Position p2 = Position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    ASSERT_EQ(p1.castlingRights, p2.castlingRights);
    ASSERT_EQ(p1.fullMoveCounter, p2.fullMoveCounter);
    ASSERT_EQ(p1.halfmoveClock, p2.halfmoveClock);
    ASSERT_EQ(p1.colorToMove, p2.colorToMove);
    ASSERT_EQ(p1.enPassantTarget, p2.enPassantTarget);
    ASSERT_EQ(p1.pieceList, p2.pieceList);
    ASSERT_EQ(p1.occupied, p2.occupied);
    for (Piece p=Piece::blackPawn; p<Piece::noPiece; p=Piece(p+1)) {
        ASSERT_EQ(p1.pieceBitboards[p], p2.pieceBitboards[p]);
    }
    ASSERT_EQ(p1.occupiedByColor[Color::white], p2.occupiedByColor[Color::white]);
    ASSERT_EQ(p1.occupiedByColor[Color::black], p2.occupiedByColor[Color::black]);
}

TEST(position_test, position_makeMove_quiet_test) {
    Position actual = Position("rn1qkb1r/pppb1ppp/4pn2/3p4/3P4/4P2N/PPPB1PPP/RN1QKB1R w KQkq - 0 1");
    Position expected = Position("rn1qkb1r/pppb1ppp/4pn2/B2p4/3P4/4P2N/PPP2PPP/RN1QKB1R b KQkq - 1 1");
    actual.makeMove(Move(D2, A5, Move::MoveType::quiet));
    ASSERT_EQ(actual, expected);

    Position expected2 = Position("r2qkb1r/pppb1ppp/2n1pn2/B2p4/3P4/4P2N/PPP2PPP/RN1QKB1R w KQkq - 2 2");
    actual.makeMove(Move(B8, C6, Move::MoveType::quiet));
    ASSERT_EQ(actual, expected2);
}

TEST(position_test, position_makeMove_doublePawnPush_test) {
    Position actual = Position("rn1qkb1r/pppb1ppp/4pn2/B2p4/3P4/4P2N/PPP2PPP/RN1QKB1R b KQkq - 1 1");
    Position expected = Position("rn1qkb1r/pp1b1ppp/4pn2/B1pp4/3P4/4P2N/PPP2PPP/RN1QKB1R w KQkq c6 0 2");
    actual.makeMove(Move(C7, C5, Move::MoveType::doublePawnPush));
    ASSERT_EQ(actual, expected);

    Position expected2 = Position("rn1qkb1r/pp1b1ppp/4pn2/B1pp4/3P2P1/4P2N/PPP2P1P/RN1QKB1R b KQkq g3 0 2");
    actual.makeMove(Move(G2, G4, Move::MoveType::doublePawnPush));
    ASSERT_EQ(actual, expected2);
}

TEST(position_test, position_makeMove_kingCastle_test) {
    Position actual = Position("rn1qk2r/pp1b1ppp/3bpn2/B1pp4/3P2P1/4P2N/PPP1BP1P/RN1QK2R b KQkq - 2 3");
    Position expected = Position("rn1q1rk1/pp1b1ppp/3bpn2/B1pp4/3P2P1/4P2N/PPP1BP1P/RN1QK2R w KQ - 3 4");
    actual.makeMove(Move(E8, G8, Move::MoveType::kingCastle));
    ASSERT_EQ(actual, expected);

    Position expected2 = Position("rn1q1rk1/pp1b1ppp/3bpn2/B1pp4/3P2P1/4P2N/PPP1BP1P/RN1Q1RK1 b - - 4 4");
    actual.makeMove(Move(E1, G1, Move::MoveType::kingCastle));
    ASSERT_EQ(actual, expected2);
}

TEST(position_test, position_makeMove_queenCastle_test) {
    Position actual = Position("r3kb1r/pppbqppp/n3pn2/3p4/3P4/2N1PQ1N/PPPB1PPP/R3KB1R w KQkq - 4 3");
    Position expected = Position("r3kb1r/pppbqppp/n3pn2/3p4/3P4/2N1PQ1N/PPPB1PPP/2KR1B1R b kq - 5 3");
    actual.makeMove(Move(E1, C1, Move::MoveType::queenCastle));
    ASSERT_EQ(actual, expected);

    Position expected2 = Position("2kr1b1r/pppbqppp/n3pn2/3p4/3P4/2N1PQ1N/PPPB1PPP/2KR1B1R w - - 6 4");
    actual.makeMove(Move(E8, C8, Move::MoveType::queenCastle));
    ASSERT_EQ(actual, expected2);
}

TEST(position_test, position_makeMove_capture_test) {
    Position actual = Position("r2qkb1r/ppp2ppp/4pn2/B2pP3/b1P5/2N1P2N/PP3PPP/R2QKB1R b KQkq - 2 4");
    Position expected = Position("r2qkb1r/ppp2ppp/4pn2/B2pP3/2P5/2N1P2N/PP3PPP/R2bKB1R w KQkq - 0 5");
    actual.makeMove(Move(A4, D1, Move::MoveType::capture));
    ASSERT_EQ(actual, expected);

    Position expected2 = Position("r2qkb1r/ppp2ppp/4pP2/B2p4/2P5/2N1P2N/PP3PPP/R2bKB1R b KQkq - 0 5");
    actual.makeMove(Move(E5, F6, Move::MoveType::capture));
    ASSERT_EQ(actual, expected2);
}

TEST(position_test, position_makeMove_epCapture_test) {
    Position actual = Position("r2qkb1r/pp3ppp/4pn2/B1pPP3/8/2N1P2N/PP3PPP/R2bKB1R w KQkq c6 0 6");
    Position expected = Position("r2qkb1r/pp3ppp/2P1pn2/B3P3/8/2N1P2N/PP3PPP/R2bKB1R b KQkq - 0 6");
    actual.makeMove(Move(D5, C6, Move::MoveType::epCapture));
    ASSERT_EQ(actual, expected);

    Position actual2 = Position("r2qkb1r/pp3p1p/2P1pn2/B3P3/2B2Pp1/2N1P2N/PP4PP/R2bK2R b KQkq f3 0 8");
    Position expected2 = Position("r2qkb1r/pp3p1p/2P1pn2/B3P3/2B5/2N1Pp1N/PP4PP/R2bK2R w KQkq - 0 9");
    actual2.makeMove(Move(G4, F3, Move::MoveType::epCapture));
    ASSERT_EQ(actual2, expected2);
}

TEST(position_test, position_makeMove_promotion_test) {
    // Black promoting
    Position actual = Position("r2qkb1r/ppP2p1p/4pn2/B3P3/2B5/2N1P2N/PPb1K1pP/R6R b kq - 2 11");
    Position expectedKnight = Position("r2qkb1r/ppP2p1p/4pn2/B3P3/2B5/2N1P2N/PPb1K2P/R5nR w kq - 0 12");
    Position expectedBishop = Position("r2qkb1r/ppP2p1p/4pn2/B3P3/2B5/2N1P2N/PPb1K2P/R5bR w kq - 0 12");
    Position expectedRook = Position("r2qkb1r/ppP2p1p/4pn2/B3P3/2B5/2N1P2N/PPb1K2P/R5rR w kq - 0 12");
    Position expectedQueen = Position("r2qkb1r/ppP2p1p/4pn2/B3P3/2B5/2N1P2N/PPb1K2P/R5qR w kq - 0 12");

    actual.makeMove(Move(G2, G1, Move::MoveType::knightPromo));
    ASSERT_EQ(actual, expectedKnight);

    actual = Position("r2qkb1r/ppP2p1p/4pn2/B3P3/2B5/2N1P2N/PPb1K1pP/R6R b kq - 2 11");
    actual.makeMove(Move(G2, G1, Move::MoveType::bishopPromo));
    ASSERT_EQ(actual, expectedBishop);
    
    actual = Position("r2qkb1r/ppP2p1p/4pn2/B3P3/2B5/2N1P2N/PPb1K1pP/R6R b kq - 2 11");
    actual.makeMove(Move(G2, G1, Move::MoveType::rookPromo));
    ASSERT_EQ(actual, expectedRook);

    actual = Position("r2qkb1r/ppP2p1p/4pn2/B3P3/2B5/2N1P2N/PPb1K1pP/R6R b kq - 2 11");
    actual.makeMove(Move(G2, G1, Move::MoveType::queenPromo));
    ASSERT_EQ(actual, expectedQueen);

    // White promoting
    actual = Position("r2qkb1r/ppP2p1p/4pn2/B3P3/2B5/2N1P2N/PPb1K2P/R5qR w kq - 0 12");
    expectedKnight = Position("r1Nqkb1r/pp3p1p/4pn2/B3P3/2B5/2N1P2N/PPb1K2P/R5qR b kq - 0 12");
    expectedBishop = Position("r1Bqkb1r/pp3p1p/4pn2/B3P3/2B5/2N1P2N/PPb1K2P/R5qR b kq - 0 12");
    expectedRook = Position("r1Rqkb1r/pp3p1p/4pn2/B3P3/2B5/2N1P2N/PPb1K2P/R5qR b kq - 0 12");
    expectedQueen = Position("r1Qqkb1r/pp3p1p/4pn2/B3P3/2B5/2N1P2N/PPb1K2P/R5qR b kq - 0 12");

    actual.makeMove(Move(C7, C8, Move::MoveType::knightPromo));
    ASSERT_EQ(actual, expectedKnight);

    actual = Position("r2qkb1r/ppP2p1p/4pn2/B3P3/2B5/2N1P2N/PPb1K2P/R5qR w kq - 0 12");
    actual.makeMove(Move(C7, C8, Move::MoveType::bishopPromo));
    ASSERT_EQ(actual, expectedBishop);
    
    actual = Position("r2qkb1r/ppP2p1p/4pn2/B3P3/2B5/2N1P2N/PPb1K2P/R5qR w kq - 0 12");
    actual.makeMove(Move(C7, C8, Move::MoveType::rookPromo));
    ASSERT_EQ(actual, expectedRook);

    actual = Position("r2qkb1r/ppP2p1p/4pn2/B3P3/2B5/2N1P2N/PPb1K2P/R5qR w kq - 0 12");
    actual.makeMove(Move(C7, C8, Move::MoveType::queenPromo));
    ASSERT_EQ(actual, expectedQueen);
}

TEST(position_test, position_makeMove_promotionCapture_test) {
    // White promotion capture
    Position actual = Position("rn1qkb1r/ppPb1p2/4pn2/B2p2p1/4P3/7N/PPP2PpP/RN1QKB1R w KQkq - 0 7");
    Position expectedKnight = Position("rn1Nkb1r/pp1b1p2/4pn2/B2p2p1/4P3/7N/PPP2PpP/RN1QKB1R b KQkq - 0 7");
    Position expectedBishop = Position("rn1Bkb1r/pp1b1p2/4pn2/B2p2p1/4P3/7N/PPP2PpP/RN1QKB1R b KQkq - 0 7");
    Position expectedRook = Position("rR1qkb1r/pp1b1p2/4pn2/B2p2p1/4P3/7N/PPP2PpP/RN1QKB1R b KQkq - 0 7");
    Position expectedQueen = Position("rQ1qkb1r/pp1b1p2/4pn2/B2p2p1/4P3/7N/PPP2PpP/RN1QKB1R b KQkq - 0 7");

    actual.makeMove(Move(C7, D8, Move::MoveType::knightPromoCapture));
    ASSERT_EQ(actual, expectedKnight);

    actual = Position("rn1qkb1r/ppPb1p2/4pn2/B2p2p1/4P3/7N/PPP2PpP/RN1QKB1R w KQkq - 0 7");
    actual.makeMove(Move(C7, D8, Move::MoveType::bishopPromoCapture));
    ASSERT_EQ(actual, expectedBishop);
    
    actual = Position("rn1qkb1r/ppPb1p2/4pn2/B2p2p1/4P3/7N/PPP2PpP/RN1QKB1R w KQkq - 0 7");
    actual.makeMove(Move(C7, B8, Move::MoveType::rookPromoCapture));
    ASSERT_EQ(actual, expectedRook);

    actual = Position("rn1qkb1r/ppPb1p2/4pn2/B2p2p1/4P3/7N/PPP2PpP/RN1QKB1R w KQkq - 0 7");
    actual.makeMove(Move(C7, B8, Move::MoveType::queenPromoCapture));
    ASSERT_EQ(actual, expectedQueen);

    // Black promotion capture
    actual = Position("rn1Bkb1r/pp1b1p2/4pn2/B2p2p1/4P3/7N/PPP2PpP/RN1QKB1R b KQkq - 0 7");
    expectedKnight = Position("rn1Bkb1r/pp1b1p2/4pn2/B2p2p1/4P3/7N/PPP2P1P/RN1QKn1R w KQkq - 0 8");
    expectedBishop = Position("rn1Bkb1r/pp1b1p2/4pn2/B2p2p1/4P3/7N/PPP2P1P/RN1QKb1R w KQkq - 0 8");
    expectedRook = Position("rn1Bkb1r/pp1b1p2/4pn2/B2p2p1/4P3/7N/PPP2P1P/RN1QKB1r w Qkq - 0 8");
    expectedQueen = Position("rn1Bkb1r/pp1b1p2/4pn2/B2p2p1/4P3/7N/PPP2P1P/RN1QKB1q w Qkq - 0 8");

    actual.makeMove(Move(G2, F1, Move::MoveType::knightPromoCapture));
    ASSERT_EQ(actual, expectedKnight);

    actual = Position("rn1Bkb1r/pp1b1p2/4pn2/B2p2p1/4P3/7N/PPP2PpP/RN1QKB1R b KQkq - 0 7");
    actual.makeMove(Move(G2, F1, Move::MoveType::bishopPromoCapture));
    ASSERT_EQ(actual, expectedBishop);
    
    actual = Position("rn1Bkb1r/pp1b1p2/4pn2/B2p2p1/4P3/7N/PPP2PpP/RN1QKB1R b KQkq - 0 7");
    actual.makeMove(Move(G2, H1, Move::MoveType::rookPromoCapture));
    ASSERT_EQ(actual, expectedRook);

    actual = Position("rn1Bkb1r/pp1b1p2/4pn2/B2p2p1/4P3/7N/PPP2PpP/RN1QKB1R b KQkq - 0 7");
    actual.makeMove(Move(G2, H1, Move::MoveType::queenPromoCapture));
    ASSERT_EQ(actual, expectedQueen);
}

TEST(position_test, position_unmakeMove_quiet_test) {
    Position actual = Position("r2qkb1r/ppp1p1pp/2n1bn2/3p1pB1/3P4/2NBPN2/PPP2PPP/R2QK2R b KQkq - 4 6");
    Position expected = Position("r2qkb1r/ppp1p1pp/2n1bn2/3p1pB1/3P4/2NBPN2/PPP2PPP/R2QK2R b KQkq - 4 6");
    actual.makeMove(Move(F6, E4, Move::MoveType::quiet));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);

    actual = Position("r3kb1r/pppqp1pp/2n1b3/3pNpBn/3P4/2NBP3/PPP2PPP/R2QK2R w KQkq - 7 8");
    expected = Position("r3kb1r/pppqp1pp/2n1b3/3pNpBn/3P4/2NBP3/PPP2PPP/R2QK2R w KQkq - 7 8");
    actual.makeMove(Move(D1, G4, Move::MoveType::quiet));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);
}

TEST(position_test, position_unmakeMove_doublePawnPush_test) {
    Position actual = Position("r3kb1r/pppqp1pp/2n1b3/3pNpBn/3P4/2NBP3/PPP2PPP/R2QK2R w KQkq - 7 8");
    Position expected = Position("r3kb1r/pppqp1pp/2n1b3/3pNpBn/3P4/2NBP3/PPP2PPP/R2QK2R w KQkq - 7 8");
    actual.makeMove(Move(B2, B4, Move::MoveType::doublePawnPush));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);

    actual = Position("r3kb1r/pppqp1pp/2n1b3/3pNpBn/1P1P4/2NBP3/P1P2PPP/R2QK2R b KQkq b3 0 8");
    expected = Position("r3kb1r/pppqp1pp/2n1b3/3pNpBn/1P1P4/2NBP3/P1P2PPP/R2QK2R b KQkq b3 0 8");
    actual.makeMove(Move(A7, A5, Move::MoveType::doublePawnPush));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);
}

TEST(position_test, position_unmakeMove_kingCastle_test) {
    Position actual = Position("r3k2r/p1pqp2p/2n1b1pb/1p1pNpBn/1P1P4/P1NBP3/2P2PPP/R2QK2R b KQkq b3 0 8");
    Position expected = Position("r3k2r/p1pqp2p/2n1b1pb/1p1pNpBn/1P1P4/P1NBP3/2P2PPP/R2QK2R b KQkq b3 0 8");
    actual.makeMove(Move(E8, G8, Move::MoveType::kingCastle));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);

    actual = Position("r4rk1/p1pqp2p/2n1b1pb/1p1pNpBn/1P1P4/P1NBP3/2P2PPP/R2QK2R w KQ - 1 9");
    expected = Position("r4rk1/p1pqp2p/2n1b1pb/1p1pNpBn/1P1P4/P1NBP3/2P2PPP/R2QK2R w KQ - 1 9");
    actual.makeMove(Move(E1, G1, Move::MoveType::kingCastle));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);
}

TEST(position_test, position_unmakeMove_queenCastle_test) {
    Position actual = Position("r3k2r/p1pqpb1p/2n3pb/1p1pNpBn/1P1P4/P1NBP3/2P1QPPP/R3K2R b KQkq - 2 9");
    Position expected = Position("r3k2r/p1pqpb1p/2n3pb/1p1pNpBn/1P1P4/P1NBP3/2P1QPPP/R3K2R b KQkq - 2 9");
    actual.makeMove(Move(E8, C8, Move::MoveType::queenCastle));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);

    actual = Position("2kr3r/p1pqpb1p/2n3pb/1p1pNpBn/1P1P4/P1NBP3/2P1QPPP/R3K2R w KQ - 3 10");
    expected = Position("2kr3r/p1pqpb1p/2n3pb/1p1pNpBn/1P1P4/P1NBP3/2P1QPPP/R3K2R w KQ - 3 10");
    actual.makeMove(Move(E1, C1, Move::MoveType::queenCastle));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);
}

TEST(position_test, position_unmakeMove_capture_test) {
    Position actual = Position("2kr3r/p1pqpb1p/2n3p1/1N1pNp1n/1P1P3B/P2Bb3/2P1QPPP/R3K2R w KQ - 0 12");
    Position expected = Position("2kr3r/p1pqpb1p/2n3p1/1N1pNp1n/1P1P3B/P2Bb3/2P1QPPP/R3K2R w KQ - 0 12");
    actual.makeMove(Move(E5, D7, Move::MoveType::capture));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);

    actual = Position("2kr3r/p1pqpb1p/2n3N1/1N1p1p1n/1P1P3B/P2Bb3/2P1QPPP/R3K2R b KQ - 0 12");
    expected = Position("2kr3r/p1pqpb1p/2n3N1/1N1p1p1n/1P1P3B/P2Bb3/2P1QPPP/R3K2R b KQ - 0 12");
    actual.makeMove(Move(C6, B4, Move::MoveType::capture));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);
}

TEST(position_test, position_unmakeMove_epCapture_test) {
    Position actual = Position("r3k2r/p1pqp2p/2n1b1pb/1p1pN1Bn/1P1P1pP1/P1NBP3/2P2P1P/R2QK2R b KQkq g3 0 9");
    Position expected = Position("r3k2r/p1pqp2p/2n1b1pb/1p1pN1Bn/1P1P1pP1/P1NBP3/2P2P1P/R2QK2R b KQkq g3 0 9");
    actual.makeMove(Move(F4, G3, Move::MoveType::epCapture));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);

    actual = Position("r3k2r/2pqp2p/4bnpb/pP1pnpB1/1P1P4/2NBP3/2P2PPP/R2QK2R w KQkq a6 0 11");
    expected = Position("r3k2r/2pqp2p/4bnpb/pP1pnpB1/1P1P4/2NBP3/2P2PPP/R2QK2R w KQkq a6 0 11");
    actual.makeMove(Move(B5, A6, Move::MoveType::epCapture));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);
}

TEST(position_test, position_unmakeMove_promotion_test) {
    Position actual = Position("r3k2r/1Ppqp2p/4bnpb/p2pn1B1/1P1PB3/2N5/2PK1pPP/R2Q3R b kq - 1 14");
    Position expected = Position("r3k2r/1Ppqp2p/4bnpb/p2pn1B1/1P1PB3/2N5/2PK1pPP/R2Q3R b kq - 1 14");
    actual.makeMove(Move(F2, F1, Move::MoveType::knightPromo));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);
    actual.makeMove(Move(F2, F1, Move::MoveType::bishopPromo));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);
    actual.makeMove(Move(F2, F1, Move::MoveType::rookPromo));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);
    actual.makeMove(Move(F2, F1, Move::MoveType::queenPromo));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);

    actual = Position("r3k2r/1Ppqp2p/4bnpb/p2pn1B1/1P1PB3/2N5/2PK2PP/R2Q1b1R w kq - 0 15");
    expected = Position("r3k2r/1Ppqp2p/4bnpb/p2pn1B1/1P1PB3/2N5/2PK2PP/R2Q1b1R w kq - 0 15");
    actual.makeMove(Move(B7, B8, Move::MoveType::knightPromo));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);
    actual.makeMove(Move(B7, B8, Move::MoveType::bishopPromo));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);
    actual.makeMove(Move(B7, B8, Move::MoveType::rookPromo));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);
    actual.makeMove(Move(B7, B8, Move::MoveType::queenPromo));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);
}

TEST(position_test, position_unmakeMove_promotionCapture_test) {
    Position actual = Position("3r1qbr/p1p1P1kp/6pb/1p3p1n/4N3/P2NP1B1/2p1KPPP/RQ1R4 b - - 0 20");
    Position expected = Position("3r1qbr/p1p1P1kp/6pb/1p3p1n/4N3/P2NP1B1/2p1KPPP/RQ1R4 b - - 0 20");
    actual.makeMove(Move(C2, B1, Move::MoveType::knightPromoCapture));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);
    actual.makeMove(Move(C2, B1, Move::MoveType::bishopPromoCapture));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);
    actual.makeMove(Move(C2, D1, Move::MoveType::rookPromoCapture));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);
    actual.makeMove(Move(C2, D1, Move::MoveType::queenPromoCapture));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);

    actual = Position("3r1qbr/p1p1P1kp/6pb/1p3p1n/4N3/P2NP1B1/4KPPP/Rn1R4 w - - 0 21");
    expected = Position("3r1qbr/p1p1P1kp/6pb/1p3p1n/4N3/P2NP1B1/4KPPP/Rn1R4 w - - 0 21");
    actual.makeMove(Move(E7, D8, Move::MoveType::knightPromoCapture));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);
    actual.makeMove(Move(E7, F8, Move::MoveType::bishopPromoCapture));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);
    actual.makeMove(Move(E7, D8, Move::MoveType::rookPromoCapture));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);
    actual.makeMove(Move(E7, F8, Move::MoveType::queenPromoCapture));
    actual.unmakeMove();
    ASSERT_EQ(actual, expected);
}
