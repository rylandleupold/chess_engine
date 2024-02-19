#include "bitboard.h"

Bitboard::Bitboard() {
	bits = 0ULL;
}

Bitboard::Bitboard(uint64_t bits) {
	bits = bits;
}

void Bitboard::set(Square square) {
	bits = bits | ((uint64_t) 1ULL << square);
}

bool Bitboard::isSet(Square square) {
	return ((uint64_t) 1ULL << square) & bits;
}

int Bitboard::lsb() {
	return _BitScanForward64(0, bits);
}

int Bitboard::msb() {
	return _BitScanReverse64(0, bits);
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