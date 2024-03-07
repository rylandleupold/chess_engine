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

    Bitboard kingAttacks(Square origin) const;
    Bitboard knightAttacks(Square origin) const;
    Bitboard bishopAttacks(Square origin, Bitboard occupied) const;
    Bitboard rookAttacks(Square origin, Bitboard occupied) const;
    Bitboard queenAttacks(Square origin, Bitboard occupied) const;
    Bitboard xrayBishopAttacks(Square origin, Bitboard occupied, Bitboard blockers) const;
    Bitboard xrayRookAttacks(Square origin, Bitboard occupied, Bitboard blockers) const;
    Bitboard rayBetween(Square origin, Square target) const;
    Bitboard positiveRayAttacks(Square origin, Direction direction, Bitboard occupied) const;
    Bitboard negativeRayAttacks(Square origin, Direction direction, Bitboard occupied) const;
    Bitboard slidingPieceAttacks(Square origin, Direction direction) const;
    Bitboard pawnCapturesWest(Bitboard pawns, Color color) const;
    Bitboard pawnCapturesEast(Bitboard pawns, Color color) const;
    Bitboard pawnCaptures(Bitboard pawns, Color color) const;
    Bitboard pawnPushes(Bitboard pawns, Color color, Bitboard occupied) const;
    Bitboard pawnDoublePushes(Bitboard pawns, Color color, Bitboard occupied) const;
    

    Bitboard attacksToKing(
        const std::array<Bitboard, 12>& pieceBitboards, 
        const Bitboard& occupied, 
        Color kingColor) const;
    Bitboard kingDangerSquares(
        const std::array<Bitboard, 12>& pieceBitboards, 
        const Bitboard& occupied,
        Color kingColor) const;

    void populateMoveList(std::vector<Move>& moveList, const Position& p) const;
    void populateKingMoves(
        std::vector<Move>& moveList,
        const Position& p,
        const Bitboard& dangerSquares) const;
    void populateKingCastlingMoves(
        std::vector<Move>& moveList,
        const Position& p,
        const Bitboard& dangerSquares) const;
    void populatePawnMoves(
        std::vector<Move>& moveList, 
        const Position& p,
        const Bitboard& pushMask, 
        const Bitboard& captureMask,
        const Bitboard& pinned) const;
    void populatePawnEnPassantMoves(
        std::vector<Move>& moveList,
        const Position& p,
        const Bitboard& pushMask, 
        const Bitboard& captureMask,
        const Bitboard& pinned) const;
    void populateKnightMoves(
        std::vector<Move>& moveList,
        const Position& p, 
        const Bitboard& pushMask, 
        const Bitboard& captureMask,
        const Bitboard& pinned) const;
    void populateBishopMoves(
        std::vector<Move>& moveList,
        const Position& p,
        const Bitboard& pushMask,
        const Bitboard& captureMask,
        const Bitboard& pinned) const;
    void populateRookMoves(
        std::vector<Move>& moveList,
        const Position& p,
        const Bitboard& pushMask,
        const Bitboard& captureMask,
        const Bitboard& pinned) const;
    void populateQueenMoves(
        std::vector<Move>& moveList,
        const Position& p,
        const Bitboard& pushMask,
        const Bitboard& captureMask,
        const Bitboard& pinned) const;
    Bitboard populatePinnedPieceMoves(
        std::vector<Move>& moveList,
        const Position& p,
        const Bitboard& pushMask,
        const Bitboard& captureMask) const;
};

#endif
