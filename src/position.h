#ifndef POSITION_H
#define POSITION_H

#include <map>
#include "bitboard.h"
#include "piece.h"

class Position {
public:
	Bitboard WP;
	Bitboard WN;
	Bitboard WB;
	Bitboard WR;
	Bitboard WQ;
	Bitboard WK;
	Bitboard BP;
	Bitboard BN;
	Bitboard BB;
	Bitboard BR;
	Bitboard BQ;
	Bitboard BK;

	Piece board [64];

	int move;
	bool whiteToMove;


	Position();

	void print();
};

#endif
