//============================================================================
// Name        : chess_engine.cpp
// Author      : Ryland Leupold
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "src/position.h"
#include "src/bitboard.h"
#include "src/square.h"
#include "src/piece.h"

int main() {
	Bitboard b;
	b.set(Square::G8);
	b.set(Square::H8);
	b.set(Square::B5);
	b.set(Square::F2);

	b.print();

	Position p;
	p.pieceBitboards[Piece::whitePawn].print();
	p.pieceBitboards[Piece::blackPawn].print();

	p.printCombinedBitboards();
	p.printPieceList();
}
