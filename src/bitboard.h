#ifndef BITBOARD_H
#define BITBOARD_H

#include <bitset>
#include <cstdint>
#include <iostream>
#include <string>
#include <map>
#include "square.h"
#include "immintrin.h"

class Bitboard {
public:
	uint64_t bits;
	Bitboard();
	Bitboard(uint64_t bits);

	void set(Square Square);

	bool isSet(Square square);
	bool isEmpty();

	int popCount();

	Square lsb();
	Square msb();

	void print();
};

#endif
