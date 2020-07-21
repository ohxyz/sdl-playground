#include <SDL.h>

#ifndef STRUCTS_HPP
#define STRUCTS_HPP

enum Direction {
    None,
    Up,
    Right,
    Down,
    Left
};

struct Move {
    Direction direction {Direction::None};
    int step {0};
    unsigned int interval {16}; // milliseconds
};


struct Range {
    int start {0};
    int end {0};
    int amplifier {1}; 
};

#endif