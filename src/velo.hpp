#include "object2d.hpp"
#include "sprite.hpp"
#include <vector>
#include <SDL.h>

#ifndef VELO_H
#define VELO_H

class Velo : public Object2D {

public:
    Velo();
    ~Velo();
    void walk();
    void jump();

private:
    SDL_Rect mScreenRect;
    Sprite* mWalkSprite;
    std::vector<Frame> mWalkFrames;
    Sprite* mJumpSprite;
    std::vector<Frame> mJumpFrames;
};

#endif