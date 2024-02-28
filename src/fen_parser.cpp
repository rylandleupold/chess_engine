#include "fen_parser.h"

FenParser::FenParser(std::string fenStr) {
    std::vector<std::string> components;
    char delimiter = ' ';
    std::string temp = "";
    for(int i=0; i<(int)fenStr.size(); i++) {
        if (fenStr[i] != delimiter) {
            temp += fenStr[i];
        } else {
            components.push_back(temp);
            temp = "";
        }
    }
    if (temp != "") {
        components.push_back(temp);
    }

    if (components.size() != 6) {
        throw std::exception("ERROR (FenParser) FEN string has incorrect number of components. Requires 6, got " + components.size());
    }
    piecePlacementStr = components[0];
    sideToMoveStr = components[1];
    castlingRightsStr = components[2];
    epTargetSquareStr = components[3];
    halfmoveClockStr = components[4];
    fullMoveCounterStr = components[5];
}

std::array<Piece, 64> FenParser::getPieceList() {
    std::array<Piece, 64> pieceList;
    // Clear the existing piece list
    for (Square s=Square::A1; s<=Square::H8; s=Square(s+1)) {
        pieceList[s] = Piece::noPiece;
    }
    // FEN string reads starting at A8, reading each row, ending at H1
    Square curSquare = Square::A8;
    for (char& c : piecePlacementStr) {
        if (std::isdigit(c)) {
            int i = std::stoi(std::string{c});
            curSquare = Square(curSquare + i);
        } else if (c == '/') {
            if (curSquare % 8 != 0) {
                throw std::exception("ERROR (FenParser) piece placement string is malformed");
            }
            // Switch to the next row (current_rank - 1 in the A file)
            curSquare = Square(curSquare - 16);
        } else {
            Piece p = charToPiece(c);
            pieceList[curSquare] = p;
            curSquare = Square(curSquare + 1);
        }
    }
    return pieceList;
}

Color FenParser::getSideToMove() {
    if (sideToMoveStr == "w") {
        return Color::white;
    }
    if (sideToMoveStr == "b") {
        return Color::black;
    }
    throw std::exception("ERROR (FenParser) side to move is malformed, expected 'w' or 'b'");
}

CastlingRights FenParser::getCastlingRights() {
    CastlingRights castlingRights = CastlingRights(std::bitset<4>("0000"));
    if (castlingRightsStr == "-") {
        return castlingRights;
    }
    for (char& c : castlingRightsStr) {
        switch (c) {
        case ('k'): 
            castlingRights.setCastlingRight(false, true);
            break;
        case ('q'):
            castlingRights.setCastlingRight(false, false);
            break;
        case ('K'):
            castlingRights.setCastlingRight(true, true);
            break;
        case ('Q'):
            castlingRights.setCastlingRight(true, false);
            break;
        default:
            throw std::exception("ERROR (FenParser) castling rights is malformed, expected one or many of 'kqKQ'");
        }
    }
    return castlingRights;
}

Square FenParser::getEpTargetSquare() {
    if (epTargetSquareStr == "-") {
        return Square::noSquare;
    }
    Square s = stringToSquare(epTargetSquareStr);
    if (s == Square::noSquare) {
        throw std::exception("ERROR (FenParser) ep target square is malformed, expected '-' or lowercase algebraic notation");
    }
    return s;
}

int FenParser::getHalfmoveClock() {
    int halfmoveClock;
    try {
        halfmoveClock = std::stoi(halfmoveClockStr);
    } catch (...) {
        throw std::exception("ERROR (FenParser) halfmove clock is malformed, expected integer");
    }
    if (halfmoveClock < 0) {
        throw std::exception("ERROR (FenParser) halfmove clock is malformed, cannot be negative");
    }
    return halfmoveClock;
}

int FenParser::getFullMoveCounter() {
    int fullMoveCounter;
    try {
        fullMoveCounter = std::stoi(fullMoveCounterStr);
    } catch (...) {
        throw std::exception("ERROR (FenParser) full move counter is malformed, expected integer");
    }
    if (fullMoveCounter < 1) {
        throw std::exception("ERROR (FenParser) full move counter is malformed, cannot be less than 1>");
    }
    return fullMoveCounter;
}
