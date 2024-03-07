#include "position.h"
#include "move_generator.h"

Position::Position() {
	fullMoveCounter = 1;
	halfmoveClock = 0;
	colorToMove = Color::white;
	enPassantTarget = Square::noSquare;

	initializePieceBitboardFromPieceList();
	initializeOccupiedFromPieceList();
}

Position::Position(std::string fenString) {
	FenParser fenParser = FenParser(fenString);

	fullMoveCounter = fenParser.getFullMoveCounter();
	halfmoveClock = fenParser.getHalfmoveClock();
	colorToMove = fenParser.getSideToMove();
	enPassantTarget = fenParser.getEpTargetSquare();
	castlingRights = fenParser.getCastlingRights();

	pieceList = fenParser.getPieceList();
	initializePieceBitboardFromPieceList();
	initializeOccupiedFromPieceList();
}

void Position::initializePieceBitboardFromPieceList() {
	for (Square s = Square::A1; s<=Square::H8; s=Square(s+1)) {
		Piece p = pieceList[s];
		if (p != Piece::noPiece) {
			pieceBitboards[p].set(s);
		}
	}
}

void Position::initializeOccupiedFromPieceList() {
	for (Square s=Square::A1; s<=Square::H8; s=Square(s+1)) {
		Piece p = pieceList[s];
		if (p != Piece::noPiece) {
			occupied.set(s);
			if (isWhite(p)) {
				occupiedByColor[Color::white].set(s);
			} else {
				occupiedByColor[Color::black].set(s);
			}
		}
	}
}

void Position::makeMove(Move move) {
	moveHistory.push_back(move);
	castlingRightsHistory.push_back(castlingRights);
	halfmoveClockHistory.push_back(halfmoveClock);
	enPassantTargetHistory.push_back(enPassantTarget);

	Square origin = move.getOrigin();
	Square target = move.getTarget();
	Move::MoveType moveType = move.getMoveType();
	Piece originPiece = pieceList [origin];
	Piece targetPiece = pieceList[target];
	
	pieceBitboards[originPiece].unset(origin);
	pieceList[origin] = Piece::noPiece;
	occupied.unset(origin);
	occupied.set(target);
	occupiedByColor[colorToMove].unset(origin);
	occupiedByColor[colorToMove].set(target);
	if (move.isPromotion()) {
		Piece promotedPiece;
		switch (moveType) {
			case Move::MoveType::queenPromo:
			case Move::MoveType::queenPromoCapture:
				promotedPiece = Piece(Piece::blackQueen + colorToMove);
				break;
			case Move::MoveType::knightPromo:
			case Move::MoveType::knightPromoCapture:
				promotedPiece = Piece(Piece::blackKnight + colorToMove);
				break;
			case Move::MoveType::bishopPromo:
			case Move::MoveType::bishopPromoCapture:
				promotedPiece = Piece(Piece::blackBishop + colorToMove);
				break;
			case Move::MoveType::rookPromo:
			case Move::MoveType::rookPromoCapture:
				promotedPiece = Piece(Piece::blackRook + colorToMove);
				break;
			default:
				promotedPiece = Piece::noPiece;
				break;
		}
		pieceBitboards[promotedPiece].set(target);
		pieceList[target] = promotedPiece;
	} else {
		pieceBitboards[originPiece].set(target);
		pieceList[target] = originPiece;
	}

	if (move.isCapture()) {
		if (moveType == Move::epCapture) {
			// Handle board updates for EP capture (captured piece is NOT on target square)
			Square capturedPawn = Square(colorToMove == Color::white ? enPassantTarget - 8 : enPassantTarget + 8);
			pieceBitboards[Piece::whitePawn - colorToMove].unset(capturedPawn);
			pieceList[capturedPawn] = Piece::noPiece;
			occupied.unset(capturedPawn);
			occupiedByColor[Color::white - colorToMove].unset(capturedPawn);
			capturedPieceHistory.push_back(Piece(Piece::whitePawn - colorToMove));
		} else {
			pieceBitboards[targetPiece].unset(target);
			occupiedByColor[Color::white - colorToMove].unset(target);
			capturedPieceHistory.push_back(targetPiece);
		}
		if (targetPiece == (Piece::whiteRook - colorToMove)) {
			// Rook was captured, update castling rights if necessary
			Square aFileSquare, hFileSquare;
			if (colorToMove == Color::white) {
				aFileSquare = Square::A8;
				hFileSquare = Square::H8;
			} else {
				aFileSquare = Square::A1;
				hFileSquare = Square::H1;
			}
			if (target == aFileSquare) {
				castlingRights.unsetCastlingRight(colorToMove != Color::white, false);
			}
			if (target == hFileSquare) {
				castlingRights.unsetCastlingRight(colorToMove != Color::white, true);
			}
		}
	} else {
		capturedPieceHistory.push_back(Piece::noPiece);
	}
	
	if (moveType == Move::MoveType::kingCastle) {
		bool isWhite = colorToMove == Color::white;
		Square rookOrigin, rookTarget;
		Piece rook;
		if (isWhite) {
			rookOrigin = Square::H1;
			rookTarget = Square::F1;
			rook = Piece::whiteRook;
		} else {
			rookOrigin = Square::H8;
			rookTarget = Square::F8;
			rook = Piece::blackRook;
		}
		pieceBitboards[rook].unset(rookOrigin);
		pieceBitboards[rook].set(rookTarget);
		pieceList[rookOrigin] = Piece::noPiece;
		pieceList[rookTarget] = rook;
		occupied.unset(rookOrigin);
		occupied.set(rookTarget);
		occupiedByColor[colorToMove].unset(rookOrigin);
		occupiedByColor[colorToMove].set(rookTarget);
		castlingRights.unsetCastlingRight(isWhite, true);
		castlingRights.unsetCastlingRight(isWhite, false);
	} else if (moveType == Move::MoveType::queenCastle) {
		bool isWhite = colorToMove == Color::white;
		Square rookOrigin, rookTarget;
		Piece rook;
		if (isWhite) {
			rookOrigin = Square::A1;
			rookTarget = Square::D1;
			rook = Piece::whiteRook;
		} else {
			rookOrigin = Square::A8;
			rookTarget = Square::D8;
			rook = Piece::blackRook;
		}
		pieceBitboards[rook].unset(rookOrigin);
		pieceBitboards[rook].set(rookTarget);
		pieceList[rookOrigin] = Piece::noPiece;
		pieceList[rookTarget] = rook;
		occupied.unset(rookOrigin);
		occupied.set(rookTarget);
		occupiedByColor[colorToMove].unset(rookOrigin);
		occupiedByColor[colorToMove].set(rookTarget);
		castlingRights.unsetCastlingRight(isWhite, false);
		castlingRights.unsetCastlingRight(isWhite, true);
	}
	
	if (moveType == Move::MoveType::doublePawnPush) {
		enPassantTarget = Square(colorToMove == Color::white ? target - 8 : target + 8);
	} else {
		enPassantTarget = Square::noSquare;
	}

	// Update castling rights if rooks or king are moving
	if (originPiece == (Piece::blackRook + colorToMove)) {
		Square aFileSquare, hFileSquare;
		if (colorToMove == Color::white) {
			aFileSquare = Square::A1;
			hFileSquare = Square::H1;
		} else {
			aFileSquare = Square::A8;
			hFileSquare = Square::H8;
		}
		if (origin == aFileSquare) {
			castlingRights.unsetCastlingRight(colorToMove == Color::white, false);
		} else if (origin == hFileSquare) {
			castlingRights.unsetCastlingRight(colorToMove == Color::white, true);
		}
	}
	if (originPiece == (Piece::blackKing + colorToMove)) {
		if (origin == Square::E1 && colorToMove == Color::white) {
			castlingRights.unsetCastlingRight(true, true);
			castlingRights.unsetCastlingRight(true, false);
		} else if (origin == Square::E8 && colorToMove == Color::black) {
			castlingRights.unsetCastlingRight(false, true);
			castlingRights.unsetCastlingRight(false, false);
		}
	}

	// Only captures and pawn moves reset the halfmove clock
	if (move.isCapture() || originPiece == (Piece::blackPawn + colorToMove)) {
		halfmoveClock = 0;
	} else {
		halfmoveClock++;
	}

	// Full move counter is incremented after each black move
	if (colorToMove == Color::black) {
		colorToMove = Color::white;
		fullMoveCounter++;
	} else {
		colorToMove = Color::black;
	}
}

void Position::unmakeMove() {
	Move move = moveHistory.back();
	moveHistory.pop_back();

	castlingRights = castlingRightsHistory.back();
	castlingRightsHistory.pop_back();
	halfmoveClock = halfmoveClockHistory.back();
	halfmoveClockHistory.pop_back();
	enPassantTarget = enPassantTargetHistory.back();
	enPassantTargetHistory.pop_back();

	Square origin = move.getOrigin();
	Square target = move.getTarget();
	Move::MoveType moveType = move.getMoveType();
	
	Piece movedPiece = pieceList[target];
	Piece capturedPiece = capturedPieceHistory.back();
	capturedPieceHistory.pop_back();

	pieceBitboards[movedPiece].unset(target);
	pieceBitboards[movedPiece].set(origin);
	pieceList[origin] = movedPiece;
	occupied.unset(target);
	occupied.set(origin);
	occupiedByColor[Color::white - colorToMove].unset(target);
	occupiedByColor[Color::white - colorToMove].set(origin);

	if (move.isCapture()) {
		if (moveType == Move::MoveType::epCapture) {
			Square capturedPawnSquare = Square(colorToMove == Color::white ? target + 8 : target - 8);
			Piece capturedPawn = Piece(Piece::blackPawn + colorToMove);
			pieceBitboards[capturedPawn].set(capturedPawnSquare);
			pieceList[capturedPawnSquare] = capturedPawn;
			pieceList[target] = Piece::noPiece;
			occupied.set(capturedPawnSquare);
			occupiedByColor[colorToMove].set(capturedPawnSquare);
		} else {
			pieceBitboards[capturedPiece].set(target);
			pieceList[target] = capturedPiece;
			occupied.set(target);
			occupiedByColor[colorToMove].set(target);
		}
	} else {
		pieceList[target] = Piece::noPiece;
	}

	if (move.isPromotion()) {
		pieceBitboards[movedPiece].unset(origin);
		pieceBitboards[Piece::whitePawn - colorToMove].set(origin);
		pieceList[origin] = Piece(Piece::whitePawn - colorToMove);
	}

	if (moveType == Move::MoveType::kingCastle) {
		bool isWhite = colorToMove != Color::white;
		Square rookOrigin, rookTarget;
		Piece rook;
		if (isWhite) {
			rookOrigin = Square::H1;
			rookTarget = Square::F1;
			rook = Piece::whiteRook;
		} else {
			rookOrigin = Square::H8;
			rookTarget = Square::F8;
			rook = Piece::blackRook;
		}
		pieceBitboards[rook].unset(rookTarget);
		pieceBitboards[rook].set(rookOrigin);
		pieceList[rookTarget] = Piece::noPiece;
		pieceList[rookOrigin] = rook;
		occupied.unset(rookTarget);
		occupied.set(rookOrigin);
		occupiedByColor[Color::white - colorToMove].unset(rookTarget);
		occupiedByColor[Color::white - colorToMove].set(rookOrigin);
	} else if (moveType == Move::MoveType::queenCastle) {
		bool isWhite = colorToMove != Color::white;
		Square rookOrigin, rookTarget;
		Piece rook;
		if (isWhite) {
			rookOrigin = Square::A1;
			rookTarget = Square::D1;
			rook = Piece::whiteRook;
		} else {
			rookOrigin = Square::A8;
			rookTarget = Square::D8;
			rook = Piece::blackRook;
		}
		pieceBitboards[rook].unset(rookTarget);
		pieceBitboards[rook].set(rookOrigin);
		pieceList[rookTarget] = Piece::noPiece;
		pieceList[rookOrigin] = rook;
		occupied.unset(rookTarget);
		occupied.set(rookOrigin);
		occupiedByColor[Color::white - colorToMove].unset(rookTarget);
		occupiedByColor[Color::white - colorToMove].set(rookOrigin);
	}

	if (colorToMove == Color::white) {
		fullMoveCounter--;
		colorToMove = Color::black;
	} else {
		colorToMove = Color::white;
	}

}

uint64_t Position::perft(int depth, const MoveGenerator& m) {
	std::vector<Move> moveList;
	int nMoves, i;
	uint64_t nodes = 0;

	m.populateMoveList(moveList, (*this));
	nMoves = moveList.size();

	if (depth == 1) 
		return nMoves;

	for (i = 0; i < nMoves; i++) {
		makeMove(moveList[i]);
		nodes += perft(depth - 1, m);
		unmakeMove();
	}
	return nodes;
}

uint64_t Position::perftWithMoveCounts(int depth, const MoveGenerator& m, std::map<Move::MoveType, int>& map) {

	std::vector<Move> moveList;
	int nMoves, i;
	uint64_t nodes = 0;

	if (depth == 0) 
		return 1ULL;

	m.populateMoveList(moveList, (*this));
	nMoves = moveList.size();

	if (depth == 1) {
		for (Move m : moveList) {
			if (map[m.getMoveType()] == 0) {
				map[m.getMoveType()] = 1;
			} else {
				map[m.getMoveType()] += 1;
			}
		}
	}
	for (i = 0; i < nMoves; i++) {
		makeMove(moveList[i]);
		nodes += perftWithMoveCounts(depth - 1, m, map);
		unmakeMove();
	}
	return nodes;

}

void Position::divide(int depth, const MoveGenerator& m, std::map<std::string, uint64_t>& nodesPerMove) {
	std::vector<Move> moveList;
	m.populateMoveList(moveList, (*this));
	for (Move move : moveList) {
		makeMove(move);
		uint64_t i = perft(depth - 1, m);
		nodesPerMove[move.toString()] = i;
		unmakeMove();
		std::cout << move.toString() << ":  " << i << std::endl;
	}
}


std::array<std::string, 8> Position::getCombinedBitboardsStr() {
	Piece pieces[64];
	for (int i=0; i<64; i++) {
		pieces[i] = Piece::noPiece;
	}

	for (Piece p=Piece::blackPawn; p!=Piece::noPiece; p=Piece(p+1)) {
		std::vector<Square> setSquares = pieceBitboards[p].getSetSquares();
		for (Square s : setSquares) {
			pieces[s] = p;
		}
    }

	std::array<std::string, 8> ranks;
	for (int rank=0; rank<8; rank++) {
		std::string rankStr = "";
		for (int file=0; file<8; file++) {
			Square s = Square((rank*8) + file);
			Piece p = pieces[s];
			rankStr.append(pieceToString(p));
			rankStr.append(" ");
		}
		ranks[rank] = rankStr;
	}
	std::reverse(ranks.begin(), ranks.end());
	return ranks;
}

std::array<std::string, 8> Position::getPieceListStr() {
	std::array<std::string, 8> ranks;
	for (int rank=0; rank<8; rank++) {
		std::string rankStr = "";
		for (int file=0; file<8; file++) {
			Square s = Square((rank*8) + file);
			Piece p = pieceList[s];
			rankStr.append(pieceToString(p));
			rankStr.append(" ");
		}
		ranks[rank] = rankStr;
	}
	std::reverse(ranks.begin(), ranks.end());
	return ranks;
}

void Position::print() {
	std::array<std::string, 8> bitboardRanks = getCombinedBitboardsStr();
	std::array<std::string, 8> pieceListRanks = getPieceListStr();
	std::cout << "____________________________________________" << std::endl;
	std::cout << "                 POSITION                   " << std::endl;
	std::cout << " Castling: " << castlingRights.toString();
	std::cout << "  To Move: " << (colorToMove == Color::white ? "W" : "B");
	std::cout << "  EP Target: " << squareToString(enPassantTarget) << std::endl;
	std::cout << " Halfmove Clock: " << halfmoveClock << std::endl;
	std::cout << " Full Move Counter: " << fullMoveCounter << std::endl;
	std::cout << " __________________________________________ " << std::endl;
	std::cout << " Combined Bitboards  |       Piece List    " << std::endl;
	for (int i=0; i<bitboardRanks.size(); i++) {
		std::cout << (8 - i) << "| " << bitboardRanks[i] << "  |  " << (8 - i) << "| " << pieceListRanks[i] << std::endl;
	}
	std::cout << "  =================  |    =================" << std::endl;
	std::cout << "   A B C D E F G H   |     A B C D E F G H " << std::endl;
}

void Position::printCombinedBitboards() {
	std::array<std::string, 8> ranks = getCombinedBitboardsStr();
	std::cout << "___________________" << std::endl;
	std::cout << " Combined Bitboards" << std::endl;
	for(int i=0; i<8; i++) {
		std::cout << (8-i) << "| " << ranks[i] << std::endl;
	}
	std::cout << "  =================" << std::endl;
	std::cout << "   A B C D E F G H " << std::endl;
}

void Position::printPieceList() {
	std::array<std::string, 8> ranks = getPieceListStr();
	std::cout << "___________________" << std::endl;
	std::cout << "     Piece List    " << std::endl;
	for(int i=0; i<8; i++) {
		std::cout << (8-i) << "| " << ranks[i] << std::endl;
	}
	std::cout << "  =================" << std::endl;
	std::cout << "   A B C D E F G H " << std::endl;
}

bool operator==(const Position& p1, const Position& p2) {
	for (Piece p=Piece::blackPawn; p<=Piece::whiteKing; p=Piece(p+1)) {
		if (p1.pieceBitboards[p] != p2.pieceBitboards[p]) {
			return false;
		}
	}
	for (Square s=Square::A1; s<=Square::H8; s=Square(s+1)) {
		if (p1.pieceList[s] != p2.pieceList[s]) {
			return false;
		}
	}
	if (p1.occupied != p2.occupied) {
		return false;
	}
	if (p1.occupiedByColor[Color::black] != p2.occupiedByColor[Color::black]) {
		return false;
	}
	if (p1.occupiedByColor[Color::white] != p2.occupiedByColor[Color::white]) {
		return false;
	}
	if (p1.castlingRights != p2.castlingRights) {
		return false;
	}
	if (p1.fullMoveCounter != p2.fullMoveCounter) {
		return false;
	}
	if (p1.halfmoveClock != p2.halfmoveClock) {
		return false;
	}
	if (p1.enPassantTarget != p2.enPassantTarget) {
		return false;
	}
	return true;
}

bool operator!=(const Position& p1, const Position& p2) {
	return !(p1 == p2);
}

