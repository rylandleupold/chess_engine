#ifndef MOVE_GENERATOR_H
#define MOVE_GENERATOR_H

#include <vector>
#include "square.h"
#include "bitboard.h"

class MoveGenerator {
private:
    Bitboard KNIGHT_MOVES[64];
    Bitboard KING_MOVES[64];
    

    void populateKnightMovesArray();
    void populateKingMovesArray();
public:
    MoveGenerator();

    Bitboard kingMoves(Square kingSquare);
    Bitboard knightMoves(Square knightSquare);
};

#endif