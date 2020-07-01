#include <string>
#include <SDL.h>
#include "frame.hpp"
#include <vector>

#ifndef SPRITE_H
#define SPRITE_H

class Sprite {

public:
    Sprite( std::string, SDL_Rect, int=1, int=1, SDL_RendererFlip=SDL_FLIP_NONE );
    ~Sprite();
    std::vector<Frame> createFrames( SDL_Rect );

private:
    int mCols {0};
    int mRows {0};
    SDL_RendererFlip mFlip {SDL_FLIP_NONE};
    SDL_Rect mArea;
    SDL_Texture* mTexture;
};

#endif