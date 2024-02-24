#ifndef MOVE_GENERATOR_H
#define MOVE_GENERATOR_H

#include <map>
#include <array>
#include "bitboard.h"
#include "direction.h"
#include "square.h"

class MoveGenerator {
private:
    Bitboard KNIGHT_MOVES[64];
    Bitboard KING_MOVES[64];
    std::array<std::array<Bitboard, 64>, 8> SLIDING_PIECE_MOVES;
    // std::map<Direction, std::array<Bitboard, 64>> SLIDING_PIECE_MOVES;


    void populateKnightMovesArray();
    void populateKingMovesArray();
    void populateSlidingPieceMovesArray();
public:
    MoveGenerator();

    Bitboard kingAttacks(Square origin);
    Bitboard knightAttacks(Square origin);
    Bitboard bishopAttacks(Square origin, Bitboard occupied);
    Bitboard rookAttacks(Square origin, Bitboard occupied);
    Bitboard queenAttacks(Square origin, Bitboard occupied);
    Bitboard positiveRayAttacks(Square origin, Direction direction, Bitboard occupied);
    Bitboard negativeRayAttacks(Square origin, Direction direction, Bitboard occupied);
    Bitboard slidingPieceAttacks(Square origin, Direction direction);
};

#endif