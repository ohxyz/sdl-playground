#include <string>
#include <iostream>
#include <vector>
#include "../frame.hpp"
#include "../helpers.hpp"
#include "../animation.hpp"

#ifndef ANIMATIONS_CHICKEN_WALK_SHOOT_HPP
#define ANIMATIONS_CHICKEN_WALK_SHOOT_HPP

class ChickenWalkShootAnimation : public Animation {

    int mImageWidth = 141;
    int mImageHeight = 122;
    std::string mImageFolderPath = "images/chicken/";

    std::vector<Frame*> mFrames;

public:

    ChickenWalkShootAnimation( int x=0, int y=0 ) {

        createFrames( x, y );
        setFrames( mFrames );
    }

    ~ChickenWalkShootAnimation() {

        for ( auto &f : mFrames ) SDL_DestroyTexture( f->imageTexture );
        mFrames.clear();
    }
    
    void
    createFrames( int x, int y ) {

        int totalFrames = 16;

        int hitboxTop = 15;
        int hitboxRight = 45;
        int hitboxBottom = 0;
        int hitboxLeft = 65;
        uint8_t hitboxColorA = 150;
        int frameDuration = 20;

        for ( int i = 0; i < totalFrames; i++ ) {

            std::string imageIndex = i < 10 ? "0" + std::to_string(i) : std::to_string(i);
            std::string imagePath = mImageFolderPath + "__yellow_chicken_walk_shooting_0" + imageIndex + ".png";
            SDL_Texture* imageTexture = helpers::loadTexture( imagePath );

            Frame* frame = new Frame();

            frame->x = x; 
            frame->y = y;
            frame->width = mImageWidth; 
            frame->height = mImageHeight;
            frame->imageClipX = 0;
            frame->imageClipY = 0;
            frame->imageClipWidth = mImageWidth;
            frame->imageClipHeight = mImageHeight;
            frame->imageClipFlip = SDL_FLIP_HORIZONTAL;
            frame->imageTexture = imageTexture;
            frame->hitboxTop = hitboxTop;
            frame->hitboxRight = hitboxRight;
            frame->hitboxBottom = hitboxBottom;
            frame->hitboxLeft = hitboxLeft;
            frame->hitboxColorA = hitboxColorA;
            frame->duration = frameDuration;
            
            mFrames.push_back( frame ); 
        }
    }
};


#endif