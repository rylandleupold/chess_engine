#ifndef DIRECTION_H
#define DIRECTION_H

enum Direction {
    SouthWest, South, SouthEast, West, East, NorthWest, North, NorthEast
};

static const Direction ALL_POSITIVE_DIRECTIONS[4] = {NorthWest, North, NorthEast, East};
static const Direction ALL_NEGATIVE_DIRECTIONS[4] = {SouthEast, South, SouthWest, West};
static const Direction DIAGONAL_POSITIVE_DIRECTIONS[2] = {NorthWest, NorthEast};
static const Direction DIAGONAL_NEGATIVE_DIRECTIONS[2] = {SouthEast, SouthWest};
static const Direction STRAIGHT_POSITIVE_DIRECTIONS[2] = {North, East};
static const Direction STRAIGHT_NEGATIVE_DIRECTIONS[2] = {South, West};

#endif