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
    int interval {16}; // milliseconds
};


struct Range {

    float start {0};
    float end {0};
    float amplifier {1}; 
};

#endif