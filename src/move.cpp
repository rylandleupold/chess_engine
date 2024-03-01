#include "move.h"

Move::Move(Square origin, Square target, MoveType moveType) {
    moveBits = ((moveType & 0xf)<<12) | ((origin & 0x3f)<<6) | ((target & 0x3f));
}

Move::Move(uint16_t bits) {
    moveBits = bits;
}

Square Move::getTarget() const {
    return Square(moveBits & 0x3f);
}

Square Move::getOrigin() const {
    return Square((moveBits >> 6) & 0x3f);
}

Move::MoveType Move::getMoveType() const {
    return MoveType((moveBits >> 12) & 0x0f);
}

void Move::setTarget(Square s) {
    moveBits &= ~0x3f;
    moveBits |= (s & 0x3f);
}

void Move::setOrigin(Square s) {
    moveBits &= ~0xfc0;
    moveBits |= ((s & 0x3f) << 6);
}

void Move::setMoveType(Move::MoveType moveType) {
    moveBits &= ~0xf000;
    moveBits |= ((moveType & 0xf) << 12);
}

bool Move::isCapture() {
    return (moveBits & CAPTURE_MASK) != 0;
}

bool Move::isPromotion() {
    return (moveBits & PROMOTION_MASK) != 0;
}

void Move::operator=(Move m) {
    moveBits = m.moveBits;
}

bool operator==(const Move& m1, const Move& m2) {
    return (m1.moveBits == m2.moveBits);
}

bool operator!=(const Move& m1, const Move& m2) {
    return !(m1 == m2);
}

std::string Move::toString() const {
    return "[" + squareToString(getOrigin()) + "->" + squareToString(getTarget()) + " " + moveTypeToString(getMoveType()) + "]";
}

std::ostream& operator<<(std::ostream& os, const Move move) {
    return os << move.toString();
}
