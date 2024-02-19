#include "bitboard.h"

Bitboard::Bitboard() {
	bits = 0ULL;
}

Bitboard::Bitboard(uint64_t b) {
	bits = b;
}

void Bitboard::set(Square square) {
	if (square == Square::noSquare) {
		return;
	}
	bits = bits | ((uint64_t) 1ULL << square);
}

bool Bitboard::isSet(Square square) {
	return (square == Square::noSquare) ? false : ((uint64_t) 1ULL << square) & bits;
}

bool Bitboard::isEmpty() {
	return (bits == 0ULL);
}

Square Bitboard::lsb() {
	// Number of trailing zeros, or noSquare if bits is empty
	int trailingZeros = _tzcnt_u64(bits);
	return (trailingZeros == 64) ? Square::noSquare : Square(trailingZeros);
}

Square Bitboard::msb() {
	// Number of bits in bitboard - number of leading 0s, or noSquare if bits is empty
	int leadingZeros = _lzcnt_u64(bits);
	return (leadingZeros == -1) ? Square::noSquare : Square(63 - leadingZeros);
}

int Bitboard::popCount() {
	return (int) __popcnt64(bits);
}

void Bitboard::print() {
	std::cout << "Bitboard" << std::endl;
	for (int r=7; r>=0; r--) {
		std::string row = "";
		for (int f=0; f<8; f++) {
			Square square = Square(r*8 + f);
			if (this->isSet(square)) {
				row = row + "X";
			} else {
				row = row + "-";
			}
		}
		std::cout << row << std::endl;
	}
}
