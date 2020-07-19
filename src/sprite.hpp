#include <string>
#include <vector>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include "frame.hpp"
#include "helpers.hpp"

#ifndef SPRITE_HPP
#define SPRITE_HPP

extern SDL_Renderer* gRenderer;

class Sprite {

    int mCols {0};
    int mRows {0};
    SDL_RendererFlip mFlip {SDL_FLIP_NONE};
    SDL_Rect mArea;
    SDL_Texture* mTexture;

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
        mTexture = helpers::loadTexture( imagePath );
    };

    ~Sprite() {

        SDL_DestroyTexture( mTexture );
    };
    
    std::vector<Frame>
    createFrames( int aX, int aY, int aFrameDuration=1000 ) {

        std::vector<Frame> frames;
        Frame frame;

        int width = round( (float)mArea.w / mCols );
        int height = round( (float)mArea.h / mRows );

        for ( int i = 0; i < mRows; i++ ) {

            for ( int j = 0; j < mCols; j++ ) {
                
                frame = {
                    .x = aX,
                    .y = aY,
                    .width = width,
                    .height = height,
                    .imageClipX = j * width,
                    .imageClipY = i * height,
                    .imageClipWidth = width,
                    .imageClipHeight = height,
                    .imageClipFlip = mFlip,
                    .imageTexture = mTexture,
                    .duration = aFrameDuration
                };

                frames.push_back( frame );
            }
        }

        return frames;
    }

};

#endif