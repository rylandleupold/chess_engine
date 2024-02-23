#ifndef DIRECTION_H
#define DIRECTION_H

enum Direction {
    NorthWest, North, NorthEast, East, 
    SouthEast, South, SouthWest, West
};

static const Direction POSITIVE_DIRECTIONS[4] = {NorthWest, North, NorthEast, East};
static const Direction NEGATIVE_DIRECTIONS[4] = {SouthEast, South, SouthWest, West};

#endif