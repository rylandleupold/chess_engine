#include "position.h"
#include "move_generator.h"

Position::Position() {
	fullMoveCounter = 1;
	halfmoveClock = 0;
	colorToMove = Color::white;
	enPassantTarget = Square::noSquare;

	moveGenerator = new MoveGenerator();

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

	moveGenerator = new MoveGenerator();

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
		std::cout << (i + 1) << "| " << bitboardRanks[i] << "  |  " << (i+1) << "| " << pieceListRanks[i] << std::endl;
	}
	std::cout << "  =================  |    =================" << std::endl;
	std::cout << "   A B C D E F G H   |     A B C D E F G H " << std::endl;
}

void Position::printCombinedBitboards() {
	std::array<std::string, 8> ranks = getCombinedBitboardsStr();
	std::cout << "___________________" << std::endl;
	std::cout << " Combined Bitboards" << std::endl;
	for(int i=0; i<8; i++) {
		std::cout << (i+1) << "| " << ranks[i] << std::endl;
	}
	std::cout << "  =================" << std::endl;
	std::cout << "   A B C D E F G H " << std::endl;
}

void Position::printPieceList() {
	std::array<std::string, 8> ranks = getPieceListStr();
	std::cout << "___________________" << std::endl;
	std::cout << "     Piece List    " << std::endl;
	for(int i=0; i<8; i++) {
		std::cout << (i+1) << "| " << ranks[i] << std::endl;
	}
	std::cout << "  =================" << std::endl;
	std::cout << "   A B C D E F G H " << std::endl;
}
