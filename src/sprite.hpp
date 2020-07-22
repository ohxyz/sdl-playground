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
    std::vector<Frame*> mFrames;

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

        mFrames.clear();
        SDL_DestroyTexture( mTexture );
    };
    
    std::vector<Frame*>
    createFrames( int aX, int aY, int aFrameDuration=1000 ) {

        mFrames.clear();

        int width = round( (float)mArea.w / mCols );
        int height = round( (float)mArea.h / mRows );

        for ( int i = 0; i < mRows; i++ ) {

            for ( int j = 0; j < mCols; j++ ) {

                Frame* frame = new Frame();

                frame->x = aX;
                frame->y = aY;
                frame->width = width;
                frame->height = height;
                frame->imageClipX = j * width;
                frame->imageClipY = i * height;
                frame->imageClipWidth = width;
                frame->imageClipHeight = height;
                frame->imageClipFlip = mFlip;
                frame->imageTexture = mTexture;
                frame->duration = aFrameDuration;

                mFrames.push_back( frame );
            }
        }

        return mFrames;
    }

};

#endif