#include <string>
#include <SDL.h>
#include <cmath>
#include <SDL_image.h>
#include "sprite.hpp"

extern SDL_Renderer* gRenderer;

Sprite::Sprite(std::string imagePath, SDL_Rect area, int cols, int rows, SDL_RendererFlip flip ) {

    mCols = cols;
    mRows = rows;
    mArea = area;
    mFlip = flip;

    SDL_Surface* surface = IMG_Load( imagePath.c_str() );

    if ( surface == NULL ) {

        printf( "Failed to load image. SDL Error: %s\n", SDL_GetError() );
    }
    else {
     
        mTexture = SDL_CreateTextureFromSurface( gRenderer, surface );
        SDL_FreeSurface( surface );
    }
}

Sprite::~Sprite() {

    SDL_DestroyTexture( mTexture );
}

std::vector<Frame>
Sprite::createFrames( SDL_Rect screenRect ) {

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
                .imageClipFlip = mFlip,
                .imageTexture = mTexture
            };

            frames.push_back( frame );
        }
    }

    return frames;
}