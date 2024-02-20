#include "bitboard.h"

Bitboard::Bitboard() {
	bits = 0ULL;
}

Bitboard::Bitboard(uint64_t b) {
	bits = b;
}

Bitboard::Bitboard(Piece piece) {
	bits = 0ULL;
	std::vector<Square> setSquares;
	switch (piece){
		case Piece::whitePawn:
			for (Square s=Square::A2; s<=Square::H2; s=(Square) (s+1)) {
				setSquares.push_back(s);
			}
			break;
		case Piece::blackPawn:
			for (Square s=Square::A7; s<=Square::H7; s=(Square) (s+1)) {
				setSquares.push_back(s);
			}
			break;
		case Piece::whiteKnight:
			setSquares.push_back(Square::B1);
			setSquares.push_back(Square::G1);
			break;
		case Piece::blackKnight:
			setSquares.push_back(Square::B8);
			setSquares.push_back(Square::G8);
			break;
		case Piece::whiteBishop:
			setSquares.push_back(Square::C1);
			setSquares.push_back(Square::F1);
			break;
		case Piece::blackBishop:
			setSquares.push_back(Square::C8);
			setSquares.push_back(Square::F8);
			break;
		case Piece::whiteRook:
			setSquares.push_back(Square::A1);
			setSquares.push_back(Square::H1);
			break;
		case Piece::blackRook:
			setSquares.push_back(Square::A8);
			setSquares.push_back(Square::H8);
			break;
		case Piece::whiteQueen:
			setSquares.push_back(Square::D1);
			break;
		case Piece::blackQueen:
			setSquares.push_back(Square::D8);
			break;
		case Piece::whiteKing:
			setSquares.push_back(Square::E1);
			break;
		case Piece::blackKing:
			setSquares.push_back(Square::E8);
			break;
		case Piece::noPiece:
		default:
			break;
	}

	for(Square square : setSquares) {
		set(square);
	}
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

int Bitboard::popCount() {
	return (int) __popcnt64(bits);
}

std::vector<Square> Bitboard::getSetSquares() {
	uint64_t temp_bits = bits;
	std::vector<Square> setSquares;
	int square;
	while (!isEmpty()) {
		setSquares.push_back(lsb());
		clearLsb();
	}
	bits = temp_bits;
	return setSquares;
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

void Bitboard::clearLsb() {
	bits = (bits & (bits - 1));
}

void Bitboard::print() {
	std::cout << "___________________" << std::endl;
	std::cout << "      Bitboard     " << std::endl;
	for (int r=7; r>=0; r--) {
		std::string row = "" + std::to_string(r+1) + "| ";
		for (int f=0; f<8; f++) {
			Square square = Square(r*8 + f);
			if (this->isSet(square)) {
				row = row + "X ";
			} else {
				row = row + "- ";
			}
		}
		std::cout << row << std::endl;
	}
	std::cout << "  =================" << std::endl;
	std::cout << "   A B C D E F G H " << std::endl;
}
