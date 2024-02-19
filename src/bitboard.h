#ifndef BITBOARD_H
#define BITBOARD_H

#include <bitset>
#include <cstdint>
#include <iostream>
#include <string>
#include <map>
#include "intrin.h"
#include "square.h"


class Bitboard {
public:
	uint64_t bits;

	Bitboard();
	Bitboard(uint64_t bits);

	void set(Square Square);
	bool isSet(Square square);
	int lsb();
	int msb();
	void print();
};

#endif
