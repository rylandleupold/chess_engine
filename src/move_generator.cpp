#include "move_generator.h"

MoveGenerator::MoveGenerator() {
    populateKnightMovesArray();
    populateKingMovesArray();
    populateSlidingPieceMovesArray();
}

void MoveGenerator::populateKnightMovesArray() {
    for (Square s=Square::A1; s <= Square::H8; s=Square(s+1)) {
        Bitboard origin(s);
        Bitboard targets;
        targets |= origin.shiftN().shiftNE();
        targets |= origin.shiftN().shiftNW();
        targets |= origin.shiftS().shiftSE();
        targets |= origin.shiftS().shiftSW();
        targets |= origin.shiftE().shiftNE();
        targets |= origin.shiftE().shiftSE();
        targets |= origin.shiftW().shiftNW();
        targets |= origin.shiftW().shiftSW();
        KNIGHT_MOVES[s] = targets;
    }
}

void MoveGenerator::populateKingMovesArray() {
    for (Square s=Square::A1; s <= Square::H8; s=Square(s+1)) {
        Bitboard origin(s);
        Bitboard targets;
        targets |= origin.shiftNW();
        targets |= origin.shiftN();
        targets |= origin.shiftNE();
        targets |= origin.shiftE();
        targets |= origin.shiftSE();
        targets |= origin.shiftS();
        targets |= origin.shiftSW();
        targets |= origin.shiftW();
        KING_MOVES[s] = targets;
    }
}

void MoveGenerator::populateSlidingPieceMovesArray() {
    for (Direction d=Direction::SouthWest; d<=Direction::NorthEast; d=Direction(d+1)) {
        for (Square s=Square::A1; s<=Square::H8; s=Square(s+1)) {
            Bitboard targets;
            Bitboard currentTarget = Bitboard(s).shift(d);
            while (!currentTarget.isEmpty()) {
                targets |= currentTarget;
                currentTarget = currentTarget.shift(d);
            }
            SLIDING_PIECE_MOVES[d][s] = targets;

        }
    }
}

Bitboard MoveGenerator::kingAttacks(Square origin) {
    return KING_MOVES[origin];
}

Bitboard MoveGenerator::knightAttacks(Square origin) {
    return KNIGHT_MOVES[origin];
}

Bitboard MoveGenerator::bishopAttacks(Square origin, Bitboard occupied) {
    Bitboard targets;
    for (Direction direction : DIAGONAL_POSITIVE_DIRECTIONS) {
        targets |= positiveRayAttacks(origin, direction, occupied);
    }
    for (Direction direction : DIAGONAL_NEGATIVE_DIRECTIONS) {
        targets |= negativeRayAttacks(origin, direction, occupied);
    }
    return targets;
}

Bitboard MoveGenerator::rookAttacks(Square origin, Bitboard occupied) {
    Bitboard targets;
    for (Direction direction : STRAIGHT_POSITIVE_DIRECTIONS) {
        targets |= positiveRayAttacks(origin, direction, occupied);
    }
    for (Direction direction : STRAIGHT_NEGATIVE_DIRECTIONS) {
        targets |= negativeRayAttacks(origin, direction, occupied);
    }
    return targets;
}

Bitboard MoveGenerator::queenAttacks(Square origin, Bitboard occupied) {
    Bitboard targets;
    for (Direction direction : ALL_POSITIVE_DIRECTIONS) {
        targets |= positiveRayAttacks(origin, direction, occupied);
    }
    for (Direction direction : ALL_NEGATIVE_DIRECTIONS) {
        targets |= negativeRayAttacks(origin, direction, occupied);
    }
    return targets;
}

Bitboard MoveGenerator::positiveRayAttacks(Square origin, Direction direction, Bitboard occupied) {
    Bitboard targets = slidingPieceAttacks(origin, direction);
    Bitboard blockers = targets & occupied;
    if (!blockers.isEmpty()) {
        Square blockerSquare = blockers.lsb();
        targets ^= slidingPieceAttacks(blockerSquare, direction);
    }
    return targets;
}

Bitboard MoveGenerator::negativeRayAttacks(Square origin, Direction direction, Bitboard occupied) {
    Bitboard targets = slidingPieceAttacks(origin, direction);
    Bitboard blockers = targets & occupied;
    if (!blockers.isEmpty()) {
        Square blockerSquare = blockers.msb();
        targets ^= slidingPieceAttacks(blockerSquare, direction);
    }
    return targets;
}

Bitboard MoveGenerator::slidingPieceAttacks(Square origin, Direction direction) {
    return SLIDING_PIECE_MOVES[direction][origin];
}
