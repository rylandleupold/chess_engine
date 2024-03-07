#ifndef POSITION_H
#define POSITION_H

#include <array>
#include <iostream>
#include <map>
#include <string>
#include "bitboard.h"
#include "castling_rights.h"
#include "fen_parser.h"
#include "move.h"
#include "piece.h"
#include "square.h"

class MoveGenerator;

class Position {
private:
	std::array<std::string, 8> getCombinedBitboardsStr();
	std::array<std::string, 8> getPieceListStr();
	void initializeAttacksTo();
	void initializeAttacksFrom();
	void initializeOccupiedFromPieceList();
	void initializePieceBitboardFromPieceList();

public:
	std::array<Bitboard, 12> pieceBitboards;
	std::array<Piece, 64> pieceList ={
		Piece::whiteRook, Piece::whiteKnight, Piece::whiteBishop, Piece::whiteQueen, Piece::whiteKing, Piece::whiteBishop, Piece::whiteKnight, Piece::whiteRook,
		Piece::whitePawn, Piece::whitePawn, Piece::whitePawn, Piece::whitePawn, Piece::whitePawn, Piece::whitePawn, Piece::whitePawn, Piece::whitePawn,
		Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece,
		Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece,
		Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece,
		Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece,
		Piece::blackPawn, Piece::blackPawn, Piece::blackPawn, Piece::blackPawn, Piece::blackPawn, Piece::blackPawn, Piece::blackPawn, Piece::blackPawn,
		Piece::blackRook, Piece::blackKnight, Piece::blackBishop, Piece::blackQueen, Piece::blackKing, Piece::blackBishop, Piece::blackKnight, Piece::blackRook
	};
	// TODO: initialize attacksTo and attacksFrom in constructor
	Bitboard attacksTo [64];
	Bitboard attacksFrom [64];
	Bitboard occupied;
	Bitboard occupiedByColor [2];

	std::vector<Move> moveHistory;
	std::vector<CastlingRights> castlingRightsHistory;
	std::vector<int> halfmoveClockHistory;
	std::vector<Piece> capturedPieceHistory;
	std::vector<Square> enPassantTargetHistory;

	int fullMoveCounter;
	int halfmoveClock;
	Color colorToMove;
	CastlingRights castlingRights;
	Square enPassantTarget;

	Position();
	Position(std::string fenString);

	void makeMove(Move move);
	void unmakeMove();

	uint64_t perft(int depth, const MoveGenerator& m);
	uint64_t perftWithMoveCounts(int depth, const MoveGenerator& m, std::map<Move::MoveType, int>& moveTypeMap);
	void divide(int depth, const MoveGenerator& m, std::map<std::string, uint64_t>& nodesPerMove);

	void print();
	void printCombinedBitboards();
	void printPieceList();

	friend bool operator==(const Position& p1, const Position& p2);
	friend bool operator!=(const Position& p1, const Position& p2);
};

#endif
