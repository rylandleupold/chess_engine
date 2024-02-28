#include "gtest/gtest.h"
#include <array>
#include <string>
#include "../src/fen_parser.h"

std::string startPos = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

// EP capture on C6, partial casting rights
std::string pos2 = "rn2kbnr/pp1b1ppp/4q3/1BpPp3/8/2N2N2/PPPP1PPP/R1BQKR2 w Qkq c6 0 7";

// Black to move, non-zero halfmove clock
std::string pos3 = "r1bqkbnr/ppp1pppp/3p4/2nN4/4P3/6N1/PPPPKPPP/R1BQ1B1R b kq - 11 14";

TEST(fen_parser_test, fen_parser_populatePieceList_test) {
    FenParser f = FenParser(startPos);
    std::array<Piece, 64> expected = {
        Piece::whiteRook, Piece::whiteKnight, Piece::whiteBishop, Piece::whiteQueen, Piece::whiteKing, Piece::whiteBishop, Piece::whiteKnight, Piece::whiteRook,
		Piece::whitePawn, Piece::whitePawn, Piece::whitePawn, Piece::whitePawn, Piece::whitePawn, Piece::whitePawn, Piece::whitePawn, Piece::whitePawn,
		Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece,
		Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece,
		Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece,
		Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece,
		Piece::blackPawn, Piece::blackPawn, Piece::blackPawn, Piece::blackPawn, Piece::blackPawn, Piece::blackPawn, Piece::blackPawn, Piece::blackPawn,
		Piece::blackRook, Piece::blackKnight, Piece::blackBishop, Piece::blackQueen, Piece::blackKing, Piece::blackBishop, Piece::blackKnight, Piece::blackRook
    };
    ASSERT_EQ(f.getPieceList(), expected);

    FenParser f2 = FenParser(pos2);
    std::array<Piece, 64> expected2 = {
        Piece::whiteRook, Piece::noPiece, Piece::whiteBishop, Piece::whiteQueen, Piece::whiteKing, Piece::whiteRook, Piece::noPiece, Piece::noPiece,
		Piece::whitePawn, Piece::whitePawn, Piece::whitePawn, Piece::whitePawn, Piece::noPiece, Piece::whitePawn, Piece::whitePawn, Piece::whitePawn,
		Piece::noPiece, Piece::noPiece, Piece::whiteKnight, Piece::noPiece, Piece::noPiece, Piece::whiteKnight, Piece::noPiece, Piece::noPiece,
		Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece,
		Piece::noPiece, Piece::whiteBishop, Piece::blackPawn, Piece::whitePawn, Piece::blackPawn, Piece::noPiece, Piece::noPiece, Piece::noPiece,
		Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::blackQueen, Piece::noPiece, Piece::noPiece, Piece::noPiece,
		Piece::blackPawn, Piece::blackPawn, Piece::noPiece, Piece::blackBishop, Piece::noPiece, Piece::blackPawn, Piece::blackPawn, Piece::blackPawn,
		Piece::blackRook, Piece::blackKnight, Piece::noPiece, Piece::noPiece, Piece::blackKing, Piece::blackBishop, Piece::blackKnight, Piece::blackRook
    };
    ASSERT_EQ(f2.getPieceList(), expected2);

    FenParser f3 = FenParser(pos3);
    std::array<Piece, 64> expected3 = {
        Piece::whiteRook, Piece::noPiece, Piece::whiteBishop, Piece::whiteQueen, Piece::noPiece, Piece::whiteBishop, Piece::noPiece, Piece::whiteRook,
		Piece::whitePawn, Piece::whitePawn, Piece::whitePawn, Piece::whitePawn, Piece::whiteKing, Piece::whitePawn, Piece::whitePawn, Piece::whitePawn,
		Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::whiteKnight, Piece::noPiece,
		Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::whitePawn, Piece::noPiece, Piece::noPiece, Piece::noPiece,
		Piece::noPiece, Piece::noPiece, Piece::blackKnight, Piece::whiteKnight, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece,
		Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::blackPawn, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece,
		Piece::blackPawn, Piece::blackPawn, Piece::blackPawn, Piece::noPiece, Piece::blackPawn, Piece::blackPawn, Piece::blackPawn, Piece::blackPawn,
		Piece::blackRook, Piece::noPiece, Piece::blackBishop, Piece::blackQueen, Piece::blackKing, Piece::blackBishop, Piece::blackKnight, Piece::blackRook
    };
    ASSERT_EQ(f3.getPieceList(), expected3);

    FenParser f4 = FenParser("rnbkbnr/ppppppp/5/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    ASSERT_THROW(f4.getPieceList(), std::exception);
}

TEST(fen_parser_test, fen_parser_getSideToMove_test) {
    FenParser f = FenParser(startPos);
    ASSERT_EQ(f.getSideToMove(), Color::white);

    FenParser f2 = FenParser(pos3);
    ASSERT_EQ(f2.getSideToMove(), Color::black);

    FenParser f3 = FenParser("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR M KQkq - 0 1");
    ASSERT_THROW(f3.getSideToMove(), std::exception);
}

TEST(fen_parser_test, fen_parser_castlingRights_test) {
    FenParser f1 = FenParser(startPos);
    CastlingRights expected1;
    ASSERT_EQ(f1.getCastlingRights(), expected1);

    FenParser f2 = FenParser(pos2);
    CastlingRights expected2;
    expected2.unsetCastlingRight(true, true);
    ASSERT_EQ(f2.getCastlingRights(), expected2);

    FenParser f3 = FenParser(pos3);
    CastlingRights expected3 = CastlingRights(std::bitset<4>("1111"));
    expected3.unsetCastlingRight(true, true);
    expected3.unsetCastlingRight(true, false);
    ASSERT_EQ(f3.getCastlingRights(), expected3);

    FenParser f4 = FenParser("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1");
    ASSERT_EQ(f4.getCastlingRights(), CastlingRights(std::bitset<4>("0000")));
}

TEST(fen_parser_test, fen_parser_epTargetSquare_test) {
    FenParser f1 = FenParser(startPos);
    ASSERT_EQ(f1.getEpTargetSquare(), Square::noSquare);

    FenParser f2 = FenParser(pos2);
    ASSERT_EQ(f2.getEpTargetSquare(), Square::C6);

    FenParser f3 = FenParser(pos3);
    ASSERT_EQ(f3.getEpTargetSquare(), Square::noSquare);   

    FenParser f4 = FenParser("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq h8 0 1");
    ASSERT_EQ(f4.getEpTargetSquare(), Square::H8);
}

TEST(fen_parser_test, fen_parser_halfmoveClock_test) {
    FenParser f1 = FenParser(startPos);
    ASSERT_EQ(f1.getHalfmoveClock(), 0);

    FenParser f2 = FenParser(pos2);
    ASSERT_EQ(f2.getHalfmoveClock(), 0);

    FenParser f3 = FenParser(pos3);
    ASSERT_EQ(f3.getHalfmoveClock(), 11);

    FenParser f4 = FenParser("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 987654321 1");
    ASSERT_EQ(f4.getHalfmoveClock(), 987654321);

    ASSERT_THROW(FenParser("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - -1 1").getHalfmoveClock(), std::exception);
    ASSERT_THROW(FenParser("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - notaninteger 1").getHalfmoveClock(), std::exception);
}

TEST(fen_parser_test, fen_parser_fullMoveCounter_test) {
    FenParser f1 = FenParser(startPos);
    ASSERT_EQ(f1.getFullMoveCounter(), 1);

    FenParser f2 = FenParser(pos2);
    ASSERT_EQ(f2.getFullMoveCounter(), 7);

    FenParser f3 = FenParser(pos3);
    ASSERT_EQ(f3.getFullMoveCounter(), 14);

    FenParser f4 = FenParser("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 957382");
    ASSERT_EQ(f4.getFullMoveCounter(), 957382);   

    ASSERT_THROW(FenParser("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 notanint").getFullMoveCounter(), std::exception); 
    ASSERT_THROW(FenParser("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0").getFullMoveCounter(), std::exception); 
}

