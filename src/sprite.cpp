#include <string>
#include <SDL.h>
#include <cmath>
#include <SDL_image.h>
#include "sprite.hpp"
#include "helpers.hpp"

extern SDL_Renderer* gRenderer;

Sprite::Sprite(std::string imagePath, SDL_Rect area, int cols, int rows, SDL_RendererFlip flip ) {

    mCols = cols;
    mRows = rows;
    mArea = area;
    mFlip = flip;

    mTexture = loadTexture( imagePath );
}

Sprite::~Sprite() {

    SDL_DestroyTexture( mTexture );
}

std::vector<Frame>
Sprite::createFrames( SDL_Rect screenRect, int frameDuration ) {

    std::vector<Frame> frames;
    Frame frame;

    int width = round( (float)mArea.w / mCols );
    int height = round( (float)mArea.h / mRows );

    for ( int i = 0; i < mRows; i++ ) {

        for ( int j = 0; j < mCols; j++ ) {
            
            frame = {
                .x = screenRect.x,
                .y = screenRect.y,
                .width = screenRect.w,
                .height = screenRect.h,
                .imageClipX = j * width,
                .imageClipY = i * height,
                .imageClipWidth = width,
                .imageClipHeight = height,
                .imageTexture = mTexture,
                .imageClipFlip = mFlip,
                .duration = frameDuration
            };

            frames.push_back( frame );
        }
    }

    return frames;
}