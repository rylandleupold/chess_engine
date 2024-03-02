#ifndef BITBOARD_H
#define BITBOARD_H

#include <bitset>
#include <cstdint>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "direction.h"
#include "immintrin.h"
#include "mask.h"
#include "piece.h"
#include "square.h"

class Bitboard {
public:
	uint64_t bits;

	Bitboard();
	Bitboard(uint64_t bits);
	Bitboard(Square square);
	Bitboard(Piece piece);

	void set(Square square);
	void set(std::vector<Square>);
	void unset(Square square);

	bool isSet(Square square) const;
	bool isEmpty() const;

	int popCount() const;
	std::vector<Square> getSetSquares() const;

	Square lsb() const;
	Square msb() const;

	void clearLsb();

	Bitboard shiftNW() const;
	Bitboard shiftN() const;
	Bitboard shiftNE() const;
	Bitboard shiftE() const;
	Bitboard shiftSE() const;
	Bitboard shiftS() const;
	Bitboard shiftSW() const;
	Bitboard shiftW() const;
	Bitboard shift(Direction d) const;

	void print() const;
	void print(char c) const;
	friend bool operator==(const Bitboard& b1, const Bitboard& b2);
	friend bool operator!=(const Bitboard& b1, const Bitboard& b2);
	void operator=(const Bitboard& b);
	friend Bitboard operator|(const Bitboard& b1, const Bitboard& b2);
	void operator|=(const Bitboard& b);
	friend Bitboard operator&(const Bitboard& b1, const Bitboard& b2);
	void operator&=(const Bitboard& b);
	friend Bitboard operator^(const Bitboard& b1, const Bitboard& b2);
	void operator^=(const Bitboard& b);
	Bitboard operator~() const;
};

#endif
