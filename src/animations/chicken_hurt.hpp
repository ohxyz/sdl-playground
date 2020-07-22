#include <string>
#include <iostream>
#include <vector>
#include "../frame.hpp"
#include "../helpers.hpp"
#include "../animation.hpp"

#ifndef ANIMATIONS_CHICKEN_HURT_HPP
#define ANIMATIONS_CHICKEN_HURT_HPP

class ChickenHurtAnimation : public Animation {

    int mImageWidth = 141;
    int mImageHeight = 122;
    std::string mImageFolderPath = "images/chicken/";

    std::vector<Frame*> mFrames;

public:

    ChickenHurtAnimation( int x=0, int y=0 ) {

        mFrames = createFrames( x, y );
        setFrames( mFrames );
    }

    ~ChickenHurtAnimation() {

        for ( auto &f : mFrames ) SDL_DestroyTexture( f->imageTexture );
        mFrames.clear();
    }
    
    std::vector<Frame*>
    createFrames( int x, int y ) {

        std::vector<Frame*> frames;
        // Use jump hitbox to debug
        int jumpHitboxTop = 15;
        int jumpHitboxRight = 45;
        int jumpHitboxBottom = 15;
        int jumpHitboxLeft = 65;
        uint8_t jumpHitboxColorA = 150;
        int frameDuration = 30;

        for ( int i = 0; i < 5; i++ ) {

            std::string imagePath 
                = mImageFolderPath + "__yellow_chicken_hurt_00" + std::to_string(i) + ".png";

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
            frame->hitboxTop = jumpHitboxTop;
            frame->hitboxRight = jumpHitboxRight;
            frame->hitboxBottom = jumpHitboxBottom;
            frame->hitboxLeft = jumpHitboxLeft;
            frame->hitboxColorA = jumpHitboxColorA;
            frame->duration = frameDuration;

            frames.push_back( frame );
        }

        return frames;
    }
};


#endif

