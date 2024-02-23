#include "move_generator.h"

MoveGenerator::MoveGenerator() {
    populateKnightMovesArray();
    populateKingMovesArray();
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

Bitboard MoveGenerator::kingMoves(Square kingSquare) {
    return KING_MOVES[kingSquare];
}

Bitboard MoveGenerator::knightMoves(Square knightSquare) {
    return KNIGHT_MOVES[knightSquare];
}