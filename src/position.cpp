#include "position.h"
#include <iostream>


Position::Position() {
	halfMoveCount = 0;
	reversibleMoveCount = 0;
	whiteToMove = true;
	enPassantTarget = Square::noSquare;

	moveGenerator = new MoveGenerator();

	for (Piece p=Piece::whitePawn; p != noPiece; p=(Piece) (p+1)) {
		Bitboard b(p);
		pieceBitboards.insert({p, b});
	};
}

std::array<std::string, 8> Position::getCombinedBitboardsStr() {
	Piece pieces[64];
	for (int i=0; i<64; i++) {
		pieces[i] = Piece::noPiece;
	}

	for (std::map<Piece, Bitboard>::iterator it=pieceBitboards.begin(); it != pieceBitboards.end(); it++) {
		Piece p = it->first;
		Bitboard b = it->second;
		std::vector<Square> setSquares = b.getSetSquares();
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
