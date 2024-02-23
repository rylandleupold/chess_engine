#ifndef BITBOARD_H
#define BITBOARD_H

#include <bitset>
#include <cstdint>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "immintrin.h"
#include "mask.h"
#include "piece.h"
#include "square.h"

class Bitboard {
public:
	static const uint64_t RANK_8 = 0;


	uint64_t bits;

	Bitboard();
	Bitboard(uint64_t bits);
	Bitboard(Square square);
	Bitboard(Piece piece);

	void set(Square Square);

	bool isSet(Square square);
	bool isEmpty();

	int popCount();
	std::vector<Square> getSetSquares();

	Square lsb();
	Square msb();

	void clearLsb();

	Bitboard shiftNW();
	Bitboard shiftN();
	Bitboard shiftNE();
	Bitboard shiftE();
	Bitboard shiftSE();
	Bitboard shiftS();
	Bitboard shiftSW();
	Bitboard shiftW();

	void print();
	friend bool operator==(const Bitboard& b1, const Bitboard& b2);
	void operator=(const Bitboard& b);
	friend Bitboard operator|(const Bitboard& b1, const Bitboard& b2);
	void operator|=(const Bitboard& b);
	friend Bitboard operator|(const Bitboard& b1, const Bitboard& b2);

};

#endif
