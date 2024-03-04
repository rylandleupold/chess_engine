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
    std::array<std::array<Bitboard, 64>, 64> RAY_BEETWEN;

    void populateKnightMovesArray();
    void populateKingMovesArray();
    void populateSlidingPieceMovesArray();
    void populateRayBetweenArray();
public:
    MoveGenerator();

    Bitboard kingAttacks(Square origin);
    Bitboard knightAttacks(Square origin);
    Bitboard bishopAttacks(Square origin, Bitboard occupied);
    Bitboard rookAttacks(Square origin, Bitboard occupied);
    Bitboard queenAttacks(Square origin, Bitboard occupied);
    Bitboard xrayBishopAttacks(Square origin, Bitboard occupied, Bitboard blockers);
    Bitboard xrayRookAttacks(Square origin, Bitboard occupied, Bitboard blockers);
    Bitboard rayBetween(Square origin, Square target) const;
    Bitboard positiveRayAttacks(Square origin, Direction direction, Bitboard occupied);
    Bitboard negativeRayAttacks(Square origin, Direction direction, Bitboard occupied);
    Bitboard slidingPieceAttacks(Square origin, Direction direction);
    Bitboard pawnCapturesWest(Bitboard pawns, Color color);
    Bitboard pawnCapturesEast(Bitboard pawns, Color color);
    Bitboard pawnCaptures(Bitboard pawns, Color color);
    Bitboard pawnPushes(Bitboard pawns, Color color, Bitboard occupied);
    Bitboard pawnDoublePushes(Bitboard pawns, Color color, Bitboard occupied);
    

    Bitboard attacksToKing(
        const std::array<Bitboard, 12>& pieceBitboards, 
        const Bitboard& occupied, 
        Color kingColor);
    Bitboard kingDangerSquares(
        const std::array<Bitboard, 12>& pieceBitboards, 
        const Bitboard& occupied,
        Color kingColor);

    void populateMoveList(std::vector<Move>& moveList, const Position& p);
    void populateKingMoves(
        std::vector<Move>& moveList,
        const Position& p,
        const Bitboard& dangerSquares);
    void populateKingCastlingMoves(
        std::vector<Move>& moveList,
        const Position& p,
        const Bitboard& dangerSquares);
    void populatePawnMoves(
        std::vector<Move>& moveList, 
        const Position& p,
        const Bitboard& pushMask, 
        const Bitboard& captureMask,
        const Bitboard& pinned);
    void populatePawnEnPassantMoves(
        std::vector<Move>& moveList,
        const Position& p,
        const Bitboard& pushMask, 
        const Bitboard& captureMask,
        const Bitboard& pinned);
    void populateKnightMoves(
        std::vector<Move>& moveList,
        const Position& p, 
        const Bitboard& pushMask, 
        const Bitboard& captureMask,
        const Bitboard& pinned);
    void populateBishopMoves(
        std::vector<Move>& moveList,
        const Position& p,
        const Bitboard& pushMask,
        const Bitboard& captureMask,
        const Bitboard& pinned);
    void populateRookMoves(
        std::vector<Move>& moveList,
        const Position& p,
        const Bitboard& pushMask,
        const Bitboard& captureMask,
        const Bitboard& pinned);
    void populateQueenMoves(
        std::vector<Move>& moveList,
        const Position& p,
        const Bitboard& pushMask,
        const Bitboard& captureMask,
        const Bitboard& pinned);
    Bitboard populatePinnedPieceMoves(
        std::vector<Move>& moveList,
        const Position& p,
        const Bitboard& pushMask,
        const Bitboard& captureMask);
};

#endif
