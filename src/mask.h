#ifndef MASK_H
#define MASK_H

#include <cstdint>

enum Mask: uint64_t {
    RANK_8 = 0xFF00000000000000,
    RANK_1 = 0x00000000000000FF,
    FILE_A = 0x0101010101010101,
    FILE_H = 0x8080808080808080,
};

#endif