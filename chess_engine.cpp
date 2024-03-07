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
    Position position3 = Position("rnb2k1r/pp1Pbppp/2p5/q7/P1B5/8/1PP1NnPP/RNBQK2R w KQ - 1 9");
	position3.print();
	std::vector<Move> moveList;
	MoveGenerator mg;
	mg.populateMoveList(moveList, position3);
	for (Move move : moveList) {
		std::cout << move.toString() << "\n";
	}
}
