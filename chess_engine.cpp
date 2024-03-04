//============================================================================
// Name        : chess_engine.cpp
// Author      : Ryland Leupold
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "src/bitboard.h"
#include "src/move_generator.h"
#include "src/piece.h"
#include "src/position.h"
#include "src/square.h"


int main() {
	Position p("3k1n1R/8/5b2/8/3r3B/8/3Q4/3R2K1 b - - 0 1");
	p.print();
}
