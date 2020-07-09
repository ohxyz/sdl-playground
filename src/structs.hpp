#ifndef STRUCTS_H
#define STRUCTS_H

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

#endif