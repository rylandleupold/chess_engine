#include "move_generator.h"

MoveGenerator::MoveGenerator() {
    populateKnightMovesArray();
    populateKingMovesArray();
    populateSlidingPieceMovesArray();
    populateRayBetweenArray();
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

void MoveGenerator::populateRayBetweenArray() {
    for (Square origin=Square::A1; origin<=Square::H8; origin=Square(origin+1)) {
        for (Square target=Square::A1; target<=Square::H8; target=Square(target+1)) {
            if (target == origin) {
                RAY_BEETWEN[target][origin] = Bitboard();
            } else if (target - origin > 0) {
                for (Direction d : ALL_POSITIVE_DIRECTIONS) {
                    Bitboard ray = Bitboard();
                    Bitboard currSquare = Bitboard(origin).shift(d);
                    while (!currSquare.isEmpty() && currSquare != Bitboard(target)) {
                        ray |= currSquare;
                        currSquare = currSquare.shift(d);
                    }
                    if (!currSquare.isEmpty()) {
                        RAY_BEETWEN[origin][target] = ray;
                        break;
                    }
                }
            } else {
                for (Direction d : ALL_NEGATIVE_DIRECTIONS) {
                    Bitboard ray = Bitboard();
                    Bitboard currSquare = Bitboard(origin).shift(d);
                    while (!currSquare.isEmpty() && currSquare != Bitboard(target)) {
                        ray |= currSquare;
                        currSquare = currSquare.shift(d);
                    }
                    if (!currSquare.isEmpty()) {
                        RAY_BEETWEN[origin][target] = ray;
                        break;
                    }
                }
            }
        }
    }
}

Bitboard MoveGenerator::kingAttacks(Square origin) const {
    return KING_MOVES[origin];
}

Bitboard MoveGenerator::knightAttacks(Square origin) const {
    return KNIGHT_MOVES[origin];
}

Bitboard MoveGenerator::bishopAttacks(Square origin, Bitboard occupied) const {
    Bitboard targets;
    for (Direction direction : DIAGONAL_POSITIVE_DIRECTIONS) {
        targets |= positiveRayAttacks(origin, direction, occupied);
    }
    for (Direction direction : DIAGONAL_NEGATIVE_DIRECTIONS) {
        targets |= negativeRayAttacks(origin, direction, occupied);
    }
    return targets;
}

Bitboard MoveGenerator::rookAttacks(Square origin, Bitboard occupied) const {
    Bitboard targets;
    for (Direction direction : STRAIGHT_POSITIVE_DIRECTIONS) {
        targets |= positiveRayAttacks(origin, direction, occupied);
    }
    for (Direction direction : STRAIGHT_NEGATIVE_DIRECTIONS) {
        targets |= negativeRayAttacks(origin, direction, occupied);
    }
    return targets;
}

Bitboard MoveGenerator::queenAttacks(Square origin, Bitboard occupied) const {
    Bitboard targets;
    for (Direction direction : ALL_POSITIVE_DIRECTIONS) {
        targets |= positiveRayAttacks(origin, direction, occupied);
    }
    for (Direction direction : ALL_NEGATIVE_DIRECTIONS) {
        targets |= negativeRayAttacks(origin, direction, occupied);
    }
    return targets;
}

Bitboard MoveGenerator::xrayBishopAttacks(Square origin, Bitboard occupied, Bitboard blockers) const {
    Bitboard attacks = bishopAttacks(origin, occupied);
    blockers &= attacks;
    return attacks ^ bishopAttacks(origin, occupied ^ blockers);
}

Bitboard MoveGenerator::xrayRookAttacks(Square origin, Bitboard occupied, Bitboard blockers) const {
    Bitboard attacks = rookAttacks(origin, occupied);
    blockers &= attacks;
    return attacks ^ rookAttacks(origin, occupied ^ blockers);
}


Bitboard MoveGenerator::positiveRayAttacks(Square origin, Direction direction, Bitboard occupied) const {
    Bitboard targets = slidingPieceAttacks(origin, direction);
    Bitboard blockers = targets & occupied;
    if (!blockers.isEmpty()) {
        Square blockerSquare = blockers.lsb();
        targets ^= slidingPieceAttacks(blockerSquare, direction);
    }
    return targets;
}

Bitboard MoveGenerator::negativeRayAttacks(Square origin, Direction direction, Bitboard occupied) const {
    Bitboard targets = slidingPieceAttacks(origin, direction);
    Bitboard blockers = targets & occupied;
    if (!blockers.isEmpty()) {
        Square blockerSquare = blockers.msb();
        targets ^= slidingPieceAttacks(blockerSquare, direction);
    }
    return targets;
}

Bitboard MoveGenerator::rayBetween(Square origin, Square target) const {
    return RAY_BEETWEN[origin][target];
}

Bitboard MoveGenerator::slidingPieceAttacks(Square origin, Direction direction)  const{
    return SLIDING_PIECE_MOVES[direction][origin];
}

Bitboard MoveGenerator::pawnCapturesWest(Bitboard pawns, Color color) const {
    return color == Color::black ? pawns.shiftSW() : pawns.shiftNW();
}

Bitboard MoveGenerator::pawnCapturesEast(Bitboard pawns, Color color) const {
    return color == Color::black ? pawns.shiftSE() : pawns.shiftNE();
}

Bitboard MoveGenerator::pawnCaptures(Bitboard pawns, Color color) const {
    return color == Color::black 
        ? (pawns.shiftSE() | pawns.shiftSW())
        : (pawns.shiftNE() | pawns.shiftNW());
}

Bitboard MoveGenerator::pawnPushes(Bitboard pawns, Color color, Bitboard occupied) const {
    if (color == Color::black) {
        return (pawns.shiftS() & ~occupied);
    } else {
        return (pawns.shiftN() & ~occupied);
    }
} 

Bitboard MoveGenerator::pawnDoublePushes(Bitboard pawns, Color color, Bitboard occupied) const {
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
        Color kingColor) const {
    Square kingSquare = pieceBitboards[Piece::blackKing + kingColor].lsb();
	Bitboard opPawns = pieceBitboards[Piece::whitePawn - kingColor];
	Bitboard opKnights = pieceBitboards[Piece::whiteKnight - kingColor];
	Bitboard opRQ = pieceBitboards[Piece::whiteQueen - kingColor];
    Bitboard opBQ = opRQ;
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
        Color kingColor) const {
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

void MoveGenerator::populateMoveList(std::vector<Move>& moveList, const Position& p) const {
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
        Square checkerSquare = checkers.lsb();
        // TODO: update push mask to be squares between checker and king
        if (isSlider(p.pieceList[checkerSquare])) {
            pushMask = rayBetween(checkerSquare, p.pieceBitboards[Piece::blackKing + p.colorToMove].lsb());
        } else {
            // Checks by non-sliding pieces cannot be blocked
            pushMask = Bitboard(0ULL);
        }
    }

    // Pinned pieces have special move generation, and should be removed from regular generation (below)
    Bitboard pinned = populatePinnedPieceMoves(moveList, p, pushMask, captureMask);

    // Not in check, generate all moves (castling is only legal when not in check)
    if (numCheckers <= 0) {
        populateKingCastlingMoves(moveList, p, dangerSquares);
    }
    populatePawnMoves(moveList, p, pushMask, captureMask, pinned);
    populatePawnEnPassantMoves(moveList, p, pushMask, captureMask, pinned);
    populateKnightMoves(moveList, p, pushMask, captureMask, pinned);
    populateBishopMoves(moveList, p, pushMask, captureMask, pinned);
    populateRookMoves(moveList, p, pushMask, captureMask, pinned);
    populateQueenMoves(moveList, p, pushMask, captureMask, pinned);

}

void MoveGenerator::populateKingMoves(
        std::vector<Move>& moveList,
        const Position& p,
        const Bitboard& dangerSquares) const {
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

void MoveGenerator::populateKingCastlingMoves(
        std::vector<Move>& moveList,
        const Position& p,
        const Bitboard& dangerSquares) const {
    // If the king has castling right and squares b/w king and rook are not occupied and not attacked, then you can castle
    if (p.colorToMove == Color::white) {
        if (p.castlingRights.canCastle(true, true) 
                && (Mask::F1_AND_G1 & p.occupied).isEmpty()
                && (Mask::F1_AND_G1 & dangerSquares).isEmpty()) {
            moveList.push_back(Move(Square::E1, Square::G1, Move::MoveType::kingCastle));
        }
        if (p.castlingRights.canCastle(true, false) 
                && (Mask::B1_TO_D1 & p.occupied).isEmpty() 
                && (Mask::C1_AND_D1 & dangerSquares).isEmpty()) {
            moveList.push_back(Move(Square::E1, Square::C1, Move::MoveType::queenCastle));
        }
    } else {
        if (p.castlingRights.canCastle(false, true)
                && (Mask::F8_AND_G8 & p.occupied).isEmpty()
                && (Mask::F8_AND_G8 & dangerSquares).isEmpty()) {
            moveList.push_back(Move(Square::E8, Square::G8, Move::MoveType::kingCastle));
        }
        if (p.castlingRights.canCastle(false, false) 
                && (Mask::B8_TO_D8 & p.occupied).isEmpty() 
                && (Mask::C8_AND_D8 & dangerSquares).isEmpty()) {
            moveList.push_back(Move(Square::E8, Square::C8, Move::MoveType::queenCastle));
        }
    }
}

void MoveGenerator::populatePawnMoves(
        std::vector<Move>& moveList, 
        const Position& p,
        const Bitboard& pushMask, 
        const Bitboard& captureMask,
        const Bitboard& pinned) const {
    Color colorToMove = p.colorToMove;
    Bitboard pawnBitboard = p.pieceBitboards[Piece::blackPawn + colorToMove] & ~pinned;
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
        const Bitboard& captureMask,
        const Bitboard& pinned) const {
    Square epTargetSquare = p.enPassantTarget;
    Color colorToMove = p.colorToMove;
    Bitboard pawnBitboard = p.pieceBitboards[Piece::blackPawn + colorToMove] & ~pinned;
    if (epTargetSquare == Square::noSquare) {
        return;
    }
    Bitboard eastOrigin, westOrigin, kingMask;
    Square epPawnSquare;
    if (colorToMove == Color::white) {
        eastOrigin = Bitboard(epTargetSquare).shiftSW();
        westOrigin = Bitboard(epTargetSquare).shiftSE();
        epPawnSquare = Square(epTargetSquare - 8);
        kingMask = Mask::RANK_5;
    } else {
        eastOrigin = Bitboard(epTargetSquare).shiftNW();
        westOrigin = Bitboard(epTargetSquare).shiftNE();
        epPawnSquare = Square(epTargetSquare + 8);
        kingMask = Mask::RANK_4;
    }
    Bitboard xrayAttacksToKing;
    Bitboard kingBitboard = p.pieceBitboards[Piece::blackKing + colorToMove];
    Bitboard opRQ = p.pieceBitboards[Piece::whiteRook - colorToMove] | p.pieceBitboards[Piece::whiteQueen - colorToMove];
    if (!(pawnBitboard & eastOrigin).isEmpty() && (captureMask.isSet(epPawnSquare) || pushMask.isSet(epTargetSquare))) {
        Bitboard occupiedWithoutpawns = p.occupied;
        occupiedWithoutpawns.unset(epPawnSquare);
        occupiedWithoutpawns.unset(eastOrigin.lsb());
        xrayAttacksToKing = (positiveRayAttacks(kingBitboard.lsb(), Direction::East, occupiedWithoutpawns) | negativeRayAttacks(kingBitboard.lsb(), Direction::West, occupiedWithoutpawns)) & opRQ;
        if (xrayAttacksToKing.isEmpty() || (kingBitboard & kingMask).isEmpty()) {
            moveList.push_back(Move(eastOrigin.lsb(), epTargetSquare, Move::MoveType::epCapture));
        }
    }
    if (!(pawnBitboard & westOrigin).isEmpty() && (captureMask.isSet(epPawnSquare) || pushMask.isSet(epTargetSquare))) {
        Bitboard occupiedWithoutpawns = p.occupied;
        occupiedWithoutpawns.unset(epPawnSquare);
        occupiedWithoutpawns.unset(westOrigin.lsb());
        xrayAttacksToKing = (positiveRayAttacks(kingBitboard.lsb(), Direction::East, occupiedWithoutpawns) | negativeRayAttacks(kingBitboard.lsb(), Direction::West, occupiedWithoutpawns)) & opRQ;
        if (xrayAttacksToKing.isEmpty() || (kingBitboard & kingMask).isEmpty()) {
            moveList.push_back(Move(westOrigin.lsb(), epTargetSquare, Move::MoveType::epCapture));
        }
    }
}

void MoveGenerator::populateKnightMoves(
        std::vector<Move>& moveList,
        const Position& p, 
        const Bitboard& pushMask, 
        const Bitboard& captureMask,
        const Bitboard& pinned) const {
    Bitboard knightBitboard = p.pieceBitboards[Piece::blackKnight + p.colorToMove] & ~pinned;
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

void MoveGenerator::populateBishopMoves(
        std::vector<Move>& moveList,
        const Position& p,
        const Bitboard& pushMask,
        const Bitboard& captureMask,
        const Bitboard& pinned) const {
    Bitboard bishopBitboard = p.pieceBitboards[Piece::blackBishop + p.colorToMove] & ~pinned;
    Bitboard opPieces = p.occupiedByColor[Color::white - p.colorToMove];
    Bitboard targets, captures, pushes;
    Square o, t;
    while(!bishopBitboard.isEmpty()) {
        o = bishopBitboard.lsb();
        targets = bishopAttacks(o, p.occupied);
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
        bishopBitboard.clearLsb();
    }
}

void MoveGenerator::populateRookMoves(
        std::vector<Move>& moveList,
        const Position& p,
        const Bitboard& pushMask,
        const Bitboard& captureMask,
        const Bitboard& pinned) const {
    Bitboard rookBitboard = p.pieceBitboards[Piece::blackRook + p.colorToMove] & ~pinned;
    Bitboard opPieces = p.occupiedByColor[Color::white - p.colorToMove];
    Bitboard targets, captures, pushes;
    Square o, t;
    while (!rookBitboard.isEmpty()) {
        o = rookBitboard.lsb();
        targets = rookAttacks(o, p.occupied);
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
        rookBitboard.clearLsb();
    }
}

void MoveGenerator::populateQueenMoves(
        std::vector<Move>& moveList,
        const Position& p,
        const Bitboard& pushMask,
        const Bitboard& captureMask,
        const Bitboard& pinned) const {
    Bitboard queenBitboard = p.pieceBitboards[Piece::blackQueen + p.colorToMove] & ~pinned;
    Bitboard opPieces = p.occupiedByColor[Color::white - p.colorToMove];
    Bitboard targets, captures, pushes;
    Square o, t;
    while (!queenBitboard.isEmpty()) {
        o = queenBitboard.lsb();
        targets = queenAttacks(o, p.occupied);
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
        queenBitboard.clearLsb();
    }
}

Bitboard MoveGenerator::populatePinnedPieceMoves(
        std::vector<Move>& moveList,
        const Position& p,
        const Bitboard& pushMask,
        const Bitboard& captureMask) const {
    Square kingSquare = p.pieceBitboards[Piece::blackKing + p.colorToMove].lsb();
    Bitboard opRQ = p.pieceBitboards[Piece::whiteRook - p.colorToMove];
    Bitboard opBQ = p.pieceBitboards[Piece::whiteBishop - p.colorToMove];
    opRQ |= p.pieceBitboards[Piece::whiteQueen - p.colorToMove];
    opBQ |= p.pieceBitboards[Piece::whiteQueen - p.colorToMove];
    Bitboard pinners = xrayRookAttacks(kingSquare, p.occupied, p.occupiedByColor[Color::black + p.colorToMove]) & opRQ;
    pinners |= xrayBishopAttacks(kingSquare, p.occupied, p.occupiedByColor[Color::black + p.colorToMove]) & opBQ;
    Square pinnedSquare, pinnerSquare;
    Bitboard pinned, attacks, captures, pushes;
    Piece pinnedPiece;
    while (!pinners.isEmpty()) {
        Bitboard updatedPushMask, updatedCaptureMask, attacks, captures, pushes, currPinned;
        pinnerSquare = pinners.lsb();
        currPinned = rayBetween(pinnerSquare, kingSquare) & p.occupiedByColor[Color::black + p.colorToMove];
        pinnedSquare = currPinned.lsb();
        pinnedPiece = p.pieceList[pinnedSquare];
        updatedPushMask = rayBetween(pinnerSquare, kingSquare) & pushMask;
        updatedCaptureMask = Bitboard(pinnerSquare) & captureMask;
        switch (Piece(pinnedPiece - p.colorToMove)) {
            case (Piece::blackBishop):
                attacks = bishopAttacks(pinnedSquare, p.occupied);
                captures = attacks & updatedCaptureMask;
                pushes = attacks & updatedPushMask;
                break;
            case (Piece::blackRook):
                attacks = rookAttacks(pinnedSquare, p.occupied);
                captures = attacks & updatedCaptureMask;
                pushes = attacks & updatedPushMask;
                break;
            case (Piece::blackQueen):
                attacks = queenAttacks(pinnedSquare, p.occupied);
                captures = attacks & updatedCaptureMask;
                pushes = attacks & updatedPushMask;
                break;
            case (Piece::blackPawn): {
                pushes = pawnPushes(Bitboard(pinnedSquare), p.colorToMove, p.occupied) & updatedPushMask;
                Bitboard dppPushes = pawnDoublePushes(Bitboard(pinnedSquare), p.colorToMove, p.occupied) & updatedPushMask;
                if (!dppPushes.isEmpty()) {
                    moveList.push_back(Move(pinnedSquare, dppPushes.lsb(), Move::MoveType::doublePawnPush));
                }
                Bitboard naiveCaptures = pawnCaptures(Bitboard(pinnedSquare), p.colorToMove);
                captures = naiveCaptures & updatedCaptureMask;
                if (p.enPassantTarget != Square::noSquare && updatedPushMask.isSet(p.enPassantTarget) && naiveCaptures.isSet(p.enPassantTarget)) {
                    moveList.push_back(Move(pinnedSquare, p.enPassantTarget, Move::MoveType::epCapture));
                }
                break;
            }
            // Knights can never move along a pin ray, and kings will never be pinned
            default: break;
        }
        Square target;
        while (!captures.isEmpty()) {
            target = captures.lsb();
            moveList.push_back(Move(pinnedSquare, target, Move::MoveType::capture));
            captures.clearLsb();
        }
        while (!pushes.isEmpty()) {
            target = pushes.lsb();
            moveList.push_back(Move(pinnedSquare, target, Move::MoveType::quiet));
            pushes.clearLsb();
        }
        pinned |= currPinned;
        pinners.clearLsb();
    }
    return pinned;
}