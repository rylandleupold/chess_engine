#include "castling_rights.h"

CastlingRights::CastlingRights() {
    castlingBits.set();
}

CastlingRights::CastlingRights(std::bitset<4> bits) {
    castlingBits = bits;
}

int CastlingRights::getCastlingBit(bool isWhite, bool isKingside) {
    // Castling bits = [ Black Queenside, Black Kingside, White Queenside, White Kingside ]
    int i = 0;
    if (isWhite) {
        i++;
    }
    if (isKingside) {
        i++;
    }
    return i;
}

bool CastlingRights::canCastle(bool isWhite, bool isKingside) {
    return castlingBits[getCastlingBit(isWhite, isKingside)];
}

void CastlingRights::setCastlingRight(bool isWhite, bool isKingside) {
    castlingBits.set(getCastlingBit(isWhite, isKingside), true);
}

void CastlingRights::unsetCastlingRight(bool isWhite, bool isKingside) {
    castlingBits.set(getCastlingBit(isWhite, isKingside), false);
}
