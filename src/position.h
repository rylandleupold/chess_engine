#ifndef POSITION_H
#define POSITION_H

#include <map>
#include <string>
#include <array>
#include "bitboard.h"
#include "piece.h"

class Position {
private:
	std::array<std::string, 8> getCombinedBitboardsStr();
	std::array<std::string, 8> getPieceListStr();

public:
	std::map<Piece, Bitboard> pieceBitboards;
	Piece pieceList [64] ={
		Piece::whiteRook, Piece::whiteKnight, Piece::whiteBishop, Piece::whiteQueen, Piece::whiteKing, Piece::whiteBishop, Piece::whiteKnight, Piece::whiteRook,
		Piece::whitePawn, Piece::whitePawn, Piece::whitePawn, Piece::whitePawn, Piece::whitePawn, Piece::whitePawn, Piece::whitePawn, Piece::whitePawn,
		Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece,
		Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece,
		Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece,
		Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece, Piece::noPiece,
		Piece::blackPawn, Piece::blackPawn, Piece::blackPawn, Piece::blackPawn, Piece::blackPawn, Piece::blackPawn, Piece::blackPawn, Piece::blackPawn,
		Piece::blackRook, Piece::blackKnight, Piece::blackBishop, Piece::blackQueen, Piece::blackKing, Piece::blackBishop, Piece::blackKnight, Piece::blackRook
	};

	int move;
	bool whiteToMove;

	Position();

	void print();
	void printCombinedBitboards();
	void printBitboard(Piece piece);
	void printPieceList();
};

#endif
