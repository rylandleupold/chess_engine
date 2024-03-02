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

Bitboard MoveGenerator::pawnCapturesWest(Bitboard pawns, Color color) {
    return color == Color::black ? pawns.shiftSW() : pawns.shiftNW();
}

Bitboard MoveGenerator::pawnCapturesEast(Bitboard pawns, Color color) {
    return color == Color::black ? pawns.shiftSE() : pawns.shiftNE();
}

Bitboard MoveGenerator::pawnCaptures(Bitboard pawns, Color color) {
    return color == Color::black 
        ? (pawns.shiftSE() | pawns.shiftSW())
        : (pawns.shiftNE() | pawns.shiftNW());
}

Bitboard MoveGenerator::pawnPushes(Bitboard pawns, Color color, Bitboard occupied) {
    if (color == Color::black) {
        return (pawns.shiftS() & ~occupied);
    } else {
        return (pawns.shiftN() & ~occupied);
    }
} 

Bitboard MoveGenerator::pawnDoublePushes(Bitboard pawns, Color color, Bitboard occupied) {
    Bitboard singlePushes;
    if (color == Color::black) {
        singlePushes = (pawns.shiftS() & ~occupied);
        return ((singlePushes & Mask::RANK_6).shiftS() & ~occupied);
    } else {
        singlePushes = (pawns.shiftN() & ~occupied);
        return ((singlePushes & Mask::RANK_3).shiftN() & ~occupied);
    }
}

Bitboard MoveGenerator::attacksToKing(
        const std::array<Bitboard, 12>& pieceBitboards,
        const Bitboard& occupied, 
        Color kingColor) {
    Square kingSquare = pieceBitboards[Piece::blackKing + kingColor].lsb();
	Bitboard opPawns = pieceBitboards[Piece::whitePawn - kingColor];
	Bitboard opKnights = pieceBitboards[Piece::whiteKnight - kingColor];
	Bitboard opRQ, opBQ = pieceBitboards[Piece::whiteQueen - kingColor];
	opRQ |= pieceBitboards[Piece::whiteRook - kingColor];
	opBQ |= pieceBitboards[Piece::whiteBishop - kingColor];
	return (
		(pawnCaptures(Bitboard(kingSquare), kingColor) & opPawns)
		| (knightAttacks(kingSquare) & opKnights)
		| (bishopAttacks(kingSquare, occupied) & opBQ)
		| (rookAttacks(kingSquare, occupied) & opRQ));
}

Bitboard MoveGenerator::kingDangerSquares(
        const std::array<Bitboard, 12>& pieceBitboards, 
        const Bitboard& occupied,
        Color kingColor) {
    Bitboard occupiedKingRemoved = occupied;
    occupiedKingRemoved.unset(pieceBitboards[Piece::blackKing + kingColor].lsb());
    Bitboard dangerSquares;
    Square opKingSquare = pieceBitboards[Piece::whiteKing - kingColor].lsb();
    if (opKingSquare != Square::noSquare) {
        dangerSquares |= kingAttacks(opKingSquare);
    }
    dangerSquares |= pawnCaptures(pieceBitboards[Piece::whitePawn - kingColor], Color(Color::white - kingColor));
    for (Square s : pieceBitboards[Piece::whiteKnight - kingColor].getSetSquares()) {
        dangerSquares |= knightAttacks(s);
    }
    for (Square s : pieceBitboards[Piece::whiteBishop - kingColor].getSetSquares()) {
        dangerSquares |= bishopAttacks(s, occupiedKingRemoved);
    }
    for (Square s : pieceBitboards[Piece::whiteRook - kingColor].getSetSquares()) {
        dangerSquares |= rookAttacks(s, occupiedKingRemoved);
    }
    for (Square s : pieceBitboards[Piece::whiteQueen - kingColor].getSetSquares()) {
        dangerSquares |= queenAttacks(s, occupiedKingRemoved);
    }
    return dangerSquares;
}

void MoveGenerator::populateMoveList(std::vector<Move>& moveList, const Position& p) {
    // Remove old moves
    moveList.clear();

    // All squares are valid for pushing and capturing unless we are in check
    Bitboard captureMask = Bitboard((uint64_t) 0xFFFFFFFFFFFFFFFF);
    Bitboard pushMask = Bitboard((uint64_t) 0xFFFFFFFFFFFFFFFF);

    // Calculate the squares attacked by opposing pieces after removing king from the board
    Bitboard dangerSquares = kingDangerSquares(p.pieceBitboards, p.occupied, p.colorToMove);
    Bitboard opPieces = p.occupiedByColor[Color::white - p.colorToMove];
    // Populate normal king moves (not castling)
    populateKingMoves(moveList, p, dangerSquares);

    Bitboard checkers = attacksToKing(p.pieceBitboards, p.occupied, p.colorToMove);
    int numCheckers = checkers.popCount();
    if (numCheckers > 1) {
        // Double check. Only king moves are legal
        return;
    }

    if (numCheckers == 1) {
        // Single check. Only king moves and capturing or blocking the checking piece are legal
        captureMask = checkers;
    }

    // Not in check, generate all moves

}

void MoveGenerator::populateKingMoves(
        std::vector<Move>& moveList,
        const Position& p,
        const Bitboard& dangerSquares) {
    Square kingSquare = p.pieceBitboards[Piece::blackKing + p.colorToMove].lsb();
    Bitboard attacks = (kingAttacks(kingSquare) & ~dangerSquares);
    Bitboard captures = attacks & p.occupiedByColor[Color::white - p.colorToMove];
    Bitboard pushes = (attacks & ~p.occupied);
    Square target;
    while (!captures.isEmpty()) {
        target = captures.lsb();
        moveList.push_back(Move(kingSquare, target, Move::MoveType::capture));
        captures.clearLsb();
    }
    while (!pushes.isEmpty()) {
        target = pushes.lsb();
        moveList.push_back(Move(kingSquare, target, Move::MoveType::quiet));
        pushes.clearLsb();
    }
}

void MoveGenerator::populatePawnMoves(
        std::vector<Move>& moveList, 
        const Position& p,
        const Bitboard& pushMask, 
        const Bitboard& captureMask) {
    Color colorToMove = p.colorToMove;
    Bitboard pawnBitboard = p.pieceBitboards[Piece::blackPawn + colorToMove];
    Bitboard opPieces = p.occupiedByColor[Color::white - colorToMove];
    Bitboard singlePushes = pawnPushes(pawnBitboard, colorToMove, p.occupied) & pushMask;
    Bitboard doublePushes = pawnDoublePushes(pawnBitboard, colorToMove, p.occupied) & pushMask;
    Bitboard capturesEast = pawnCapturesEast(pawnBitboard, colorToMove) & opPieces & captureMask;
    Bitboard capturesWest = pawnCapturesWest(pawnBitboard, colorToMove) & opPieces & captureMask;

    int eastOffset, westOffset, pushOffset;
    Bitboard promotions, promoCapturesEast, promoCapturesWest;
    if (colorToMove == Color::white) {
        eastOffset = -9;
        westOffset = -7;
        pushOffset = -8;
        promotions = singlePushes & Mask::RANK_8;
        singlePushes &= Mask::NOT_RANK_8;
        promoCapturesEast = capturesEast & Mask::RANK_8;
        capturesEast &= Mask::NOT_RANK_8;
        promoCapturesWest = capturesWest & Mask::RANK_8;
        capturesWest &= Mask::NOT_RANK_8;
    } else {
        eastOffset = 7;
        westOffset = 9;
        pushOffset = 8;
        promotions = singlePushes & Mask::RANK_1;
        singlePushes &= Mask::NOT_RANK_1;
        promoCapturesEast = capturesEast & Mask::RANK_1;
        capturesEast &= Mask::NOT_RANK_1;
        promoCapturesWest = capturesWest & Mask::RANK_1;
        capturesWest &= Mask::NOT_RANK_1;
    }

    Square target;
    while (!capturesEast.isEmpty()) {
        target = capturesEast.lsb();
        moveList.push_back(Move(Square(target + eastOffset), target, Move::MoveType::capture));
        capturesEast.clearLsb();
    }
    while (!capturesWest.isEmpty()) {
        target = capturesWest.lsb();
        moveList.push_back(Move(Square(target + westOffset), target, Move::MoveType::capture));
        capturesWest.clearLsb();
    }
    while (!doublePushes.isEmpty()) {
        target = doublePushes.lsb();
        moveList.push_back(Move(Square(target + (2*pushOffset)), target, Move::MoveType::doublePawnPush));
        doublePushes.clearLsb();
    }
    while (!singlePushes.isEmpty()) {
        target = singlePushes.lsb();
        moveList.push_back(Move(Square(target + pushOffset), target, Move::MoveType::quiet));
        singlePushes.clearLsb();
    }
    while (!promotions.isEmpty()) {
        target = promotions.lsb();
        moveList.push_back(Move(Square(target + pushOffset), target, Move::MoveType::queenPromo));
        moveList.push_back(Move(Square(target + pushOffset), target, Move::MoveType::rookPromo));
        moveList.push_back(Move(Square(target + pushOffset), target, Move::MoveType::bishopPromo));
        moveList.push_back(Move(Square(target + pushOffset), target, Move::MoveType::knightPromo));
        promotions.clearLsb();
    }
    while (!promoCapturesEast.isEmpty()) {
        target = promoCapturesEast.lsb();
        moveList.push_back(Move(Square(target + eastOffset), target, Move::MoveType::queenPromoCapture));
        moveList.push_back(Move(Square(target + eastOffset), target, Move::MoveType::rookPromoCapture));
        moveList.push_back(Move(Square(target + eastOffset), target, Move::MoveType::bishopPromoCapture));
        moveList.push_back(Move(Square(target + eastOffset), target, Move::MoveType::knightPromoCapture));
        promoCapturesEast.clearLsb();
    }
    while (!promoCapturesWest.isEmpty()) {
        target = promoCapturesWest.lsb();
        moveList.push_back(Move(Square(target + westOffset), target, Move::MoveType::queenPromoCapture));
        moveList.push_back(Move(Square(target + westOffset), target, Move::MoveType::rookPromoCapture));
        moveList.push_back(Move(Square(target + westOffset), target, Move::MoveType::bishopPromoCapture));
        moveList.push_back(Move(Square(target + westOffset), target, Move::MoveType::knightPromoCapture));
        promoCapturesWest.clearLsb();
    }
}

void MoveGenerator::populatePawnEnPassantMoves(
        std::vector<Move>& moveList,
        const Position& p,
        const Bitboard& pushMask, 
        const Bitboard& captureMask) {
    Square epTargetSquare = p.enPassantTarget;
    Color colorToMove = p.colorToMove;
    Bitboard pawnBitboard = p.pieceBitboards[Piece::blackPawn + colorToMove];
    if (epTargetSquare == Square::noSquare) {
        return;
    }
    Square eastOrigin, westOrigin, epPawnSquare;
    if (colorToMove == Color::white) {
        eastOrigin = Square(epTargetSquare - 9);
        westOrigin = Square(epTargetSquare - 7);
        epPawnSquare = Square(epTargetSquare - 8);
    } else {
        eastOrigin = Square(epTargetSquare + 7);
        westOrigin = Square(epTargetSquare + 9);
        epPawnSquare = Square(epTargetSquare + 8);
    }
    if (pawnBitboard.isSet(eastOrigin) && (captureMask.isSet(epPawnSquare) || pushMask.isSet(epTargetSquare))) {
        moveList.push_back(Move(eastOrigin, epTargetSquare, Move::MoveType::epCapture));
    }
    if (pawnBitboard.isSet(westOrigin) && (captureMask.isSet(epPawnSquare) || pushMask.isSet(epTargetSquare))) {
        moveList.push_back(Move(westOrigin, epTargetSquare, Move::MoveType::epCapture));
    }
}

void MoveGenerator::populateKnightMoves(
        std::vector<Move>& moveList,
        const Position& p, 
        const Bitboard& pushMask, 
        const Bitboard& captureMask) {
    Bitboard knightBitboard = p.pieceBitboards[Piece::blackKnight + p.colorToMove];
    Bitboard opPieces = p.occupiedByColor[Color::white - p.colorToMove];
    Bitboard targets, captures, pushes;
    Square o, t;
    while (!knightBitboard.isEmpty()) {
        o = knightBitboard.lsb();
        targets = knightAttacks(o);
        captures = targets & opPieces & captureMask;
        pushes = targets & (~p.occupied) & pushMask;
        while (!captures.isEmpty()) {
            t = captures.lsb();
            moveList.push_back(Move(o, t, Move::MoveType::capture));
            captures.clearLsb();
        }
        while (!pushes.isEmpty()) {
            t = pushes.lsb();
            moveList.push_back(Move(o, t, Move::MoveType::quiet));
            pushes.clearLsb();
        }
        knightBitboard.clearLsb();
    }
}
