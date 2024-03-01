#ifndef POSITION_H
#define POSITION_H

#include <array>
#include <iostream>
#include <map>
#include <string>
#include "bitboard.h"
#include "castling_rights.h"
#include "fen_parser.h"
#include "move_generator.h"
#include "piece.h"
#include "square.h"

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

	int fullMoveCounter;
	int halfmoveClock;
	Color colorToMove;
	CastlingRights castlingRights;
	Square enPassantTarget;
	MoveGenerator* moveGenerator;

	Position();
	Position(std::string fenString);

	void print();
	void printCombinedBitboards();
	void printPieceList();
};

#endif
