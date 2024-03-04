#include "castling_rights.h"

CastlingRights::CastlingRights() {
    castlingBits.set();
}

CastlingRights::CastlingRights(std::bitset<4> bits) {
    castlingBits = bits;
}

int CastlingRights::getCastlingBit(bool isWhite, bool isKingside) const {
    // Castling bits = [ Black Queenside, Black Kingside, White Queenside, White Kingside ]
    int i = 0;
    if (isWhite) {
        i += 2;
    }
    if (isKingside) {
        i++;
    }
    return i;
}

bool CastlingRights::canCastle(bool isWhite, bool isKingside) const {
    return castlingBits[getCastlingBit(isWhite, isKingside)];
}

void CastlingRights::setCastlingRight(bool isWhite, bool isKingside) {
    castlingBits.set(getCastlingBit(isWhite, isKingside), true);
}

void CastlingRights::unsetCastlingRight(bool isWhite, bool isKingside) {
    castlingBits.set(getCastlingBit(isWhite, isKingside), false);
}

std::string CastlingRights::toString() {
    std::string result = "----";
    if (canCastle(false, false)) {
        result[0] = 'q';
    }
    if (canCastle(false, true)) {
        result[1] = 'k';
    }
    if (canCastle(true, false)) {
        result[2] = 'Q';
    }
    if (canCastle(true, true)) {
        result[3] = 'K';
    }
    return result;
}

bool operator==(const CastlingRights& cr1, const CastlingRights& cr2) {
	return (cr1.castlingBits == cr2.castlingBits);
}

bool operator!=(const CastlingRights& cr1, const CastlingRights& cr2) {
	return !(cr1 == cr2);
}
