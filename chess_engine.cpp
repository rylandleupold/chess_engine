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
	Position p("r1bqkbnr/ppp1pppp/3p4/2nN4/4P3/6N1/PPPPKPPP/R1BQ1B1R b kq - 11 14");
	p.occupied.print();
	p.occupiedByColor[Color::black].print();
	p.occupiedByColor[Color::white].print();
	p.print();
}
