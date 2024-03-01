#ifndef MOVE_GENERATOR_H
#define MOVE_GENERATOR_H

#include <map>
#include <array>
#include "bitboard.h"
#include "color.h"
#include "direction.h"
#include "move.h"
#include "position.h"
#include "square.h"

class MoveGenerator {
private:
    std::array<Bitboard, 64> KNIGHT_MOVES;
    std::array<Bitboard, 64> KING_MOVES;
    std::array<std::array<Bitboard, 64>, 8> SLIDING_PIECE_MOVES;

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
    Bitboard pawnCapturesWest(Bitboard pawns, Color color);
    Bitboard pawnCapturesEast(Bitboard pawns, Color color);
    Bitboard pawnCaptures(Bitboard pawns, Color color);
    Bitboard pawnPushes(Bitboard pawns, Color color, Bitboard occupied);
    
    void populateMoveList(std::vector<Move>& moveList, Position& p);
    void populateKingMoves(std::vector<Move>& moveList, Bitboard kingBitboard, Bitboard dangerSquares, Bitboard occupied, Bitboard opPieces);
    Bitboard attacksToKing(const std::array<Bitboard, 12>& pieceBitboards, Bitboard occupied, Color kingColor);
    Bitboard kingDangerSquares(const std::array<Bitboard, 12>& pieceBitboards, Bitboard occupied, Color kingColor);
};

#endif