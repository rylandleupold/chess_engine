#ifndef FEN_PARSER_H
#define FEN_PARSER_H

#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "bitboard.h"
#include "castling_rights.h"
#include "color.h"
#include "piece.h"
#include "square.h"

class FenParser {
private:
    std::string piecePlacementStr;
    std::string sideToMoveStr;
    std::string castlingRightsStr;
    std::string epTargetSquareStr;
    std::string halfmoveClockStr;
    std::string fullMoveCounterStr;
public:
    FenParser(std::string fenStr);
    std::array<Piece, 64> getPieceList();
    Color getSideToMove();
    CastlingRights getCastlingRights();
    Square getEpTargetSquare();
    int getHalfmoveClock();
    int getFullMoveCounter();
};

#endif