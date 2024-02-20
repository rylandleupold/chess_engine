#ifndef CASTLING_RIGHTS_H
#define CASTLING_RIGHTS_H

#include <bitset>

class CastlingRights {
private:
    std::bitset<4> castlingBits;
    int getCastlingBit(bool isWhite, bool isKingside);
public:
    CastlingRights();
    CastlingRights(std::bitset<4> bits);
    bool canCastle(bool isWhite, bool isKingside);
    void setCastlingRight(bool isWhite, bool isKingside);
    void unsetCastlingRight(bool isWhite, bool isKingside);
};

#endif