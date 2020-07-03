#include <string>
#include <vector>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include "frame.h"
#include "helpers.h"

#ifndef SPRITE_HPP
#define SPRITE_HPP

extern SDL_Renderer* gRenderer;

class Sprite {

public:

   Sprite(  std::string imagePath, 
            SDL_Rect area, 
            int cols, 
            int rows, 
            SDL_RendererFlip flip=SDL_FLIP_NONE ) {

        mCols = cols;
        mRows = rows;
        mArea = area;
        mFlip = flip;
        mTexture = loadTexture( imagePath );
    };

    ~Sprite() {

        SDL_DestroyTexture( mTexture );
    };
    
    std::vector<Frame>
    createFrames( SDL_Rect screenRect, int frameDuration=1000 ) {

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
                    .imageTexture = mTexture,
                    .duration = frameDuration
                };

                frames.push_back( frame );
            }
        }

        return frames;
    }

private:

    int mCols {0};
    int mRows {0};
    SDL_RendererFlip mFlip {SDL_FLIP_NONE};
    SDL_Rect mArea;
    SDL_Texture* mTexture;
};

#endif