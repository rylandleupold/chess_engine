#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include <cstdint>
#include "square.h"

class Move {
public:
    // < move type (4 bits), origin square (6 bits), target square (6 bits) >
    uint16_t moveBits;

    enum MoveType: uint32_t {
        quiet=0, doublePawnPush=1, kingCastle=2, queenCastle=3, capture=4, epCapture=5,
        knightPromo=8, bishopPromo=9, rookPromo=10, queenPromo=11,
        knightPromoCapture=12, bishopPromoCapture=13, rookPromoCapture=14, queenPromoCapture=15
    };

    static const uint16_t CAPTURE_MASK = 0x4000;
    static const uint16_t PROMOTION_MASK = 0x8000;

    Move(Square origin, Square target, MoveType moveType);
    Move(uint16_t);

    Square getTarget() const;
    Square getOrigin() const;
    Move::MoveType getMoveType() const;
    
    void setTarget(Square s);
    void setOrigin(Square s);
    void setMoveType(Move::MoveType moveType);

    bool isCapture();
    bool isPromotion();

    std::string toString() const;

    void operator=(Move m);
    friend bool operator==(const Move& m1, const Move& m2);
    friend bool operator!=(const Move& m1, const Move& m2);
};

std::ostream& operator<<(std::ostream& os, const Move move);

static const std::string moveTypeToString(Move::MoveType moveType) {
    switch (moveType) {
        case (Move::MoveType::quiet): return "Quiet";
        case (Move::MoveType::doublePawnPush): return "DPP";
        case (Move::MoveType::kingCastle): return "KCastle";
        case (Move::MoveType::queenCastle): return "QCastle";
        case (Move::MoveType::capture): return "Capture";
        case (Move::MoveType::epCapture): return "EPCapture";
        case (Move::MoveType::knightPromo): return "NPromo";
        case (Move::MoveType::bishopPromo): return "BPromo";
        case (Move::MoveType::rookPromo): return "RPromo";
        case (Move::MoveType::queenPromo): return "QPromo";
        case (Move::MoveType::knightPromoCapture): return "NPromoCap";
        case (Move::MoveType::bishopPromoCapture): return "BPromoCap";
        case (Move::MoveType::rookPromoCapture): return "RPromoCap";
        case (Move::MoveType::queenPromoCapture): return "QPromoCap";
        default: return "Unknown";
    }
}

#endif