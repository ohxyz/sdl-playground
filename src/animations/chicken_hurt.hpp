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

public:

    ChickenHurtAnimation( int x=0, int y=0 ) {

        setFrames( createFrames( x, y ) );
    }

    ~ChickenHurtAnimation() {

        for ( auto &f : mFrames ) SDL_DestroyTexture( f.imageTexture );
    }

    std::vector<Frame>
    createFrames( int x, int y ) {

        std::vector<Frame> frames;

        // Use jump hitbox to debug
        int jumpHitboxTop = 10;
        int jumpHitboxRight = 40;
        int jumpHitboxBottom = 15;
        int jumpHitboxLeft = 60;
        uint8_t jumpHitboxColorA = 150;

        for ( int i = 0; i < 5; i++ ) {

            std::string imagePath 
                = mImageFolderPath + "__yellow_chicken_hurt_00" + std::to_string(i) + ".png";

            SDL_Texture* imageTexture = helpers::loadTexture( imagePath );

            Frame frame = {
                .x = x,
                .y = y, 
                .width = mImageWidth, 
                .height = mImageHeight,
                .imageClipX = 0,
                .imageClipY = 0,
                .imageClipWidth = mImageWidth,
                .imageClipHeight = mImageHeight,
                .imageClipFlip = SDL_FLIP_HORIZONTAL,
                .imageTexture = imageTexture,
                .hitboxTop = jumpHitboxTop,
                .hitboxRight = jumpHitboxRight,
                .hitboxBottom = jumpHitboxBottom,
                .hitboxLeft = jumpHitboxLeft,
                .hitboxColorA = jumpHitboxColorA,
                .duration = 20
            };

            frames.push_back( frame );
        }

        return frames;
    }
};


#endif

