#ifndef BITBOARD_H
#define BITBOARD_H

#include <bitset>
#include <cstdint>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "piece.h"
#include "square.h"
#include "immintrin.h"

class Bitboard {
public:
	uint64_t bits;

	Bitboard();
	Bitboard(uint64_t bits);
	Bitboard(Piece piece);

	void set(Square Square);

	bool isSet(Square square);
	bool isEmpty();

	int popCount();
	std::vector<Square> getSetSquares();

	Square lsb();
	Square msb();

	void clearLsb();
	
	void print();
};

#endif
