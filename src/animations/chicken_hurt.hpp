#include <string>
#include <iostream>
#include <vector>
#include "../frame.h"
#include "../helpers.hpp"
#include "../animation.hpp"

#ifndef ANIMATIONS_CHICKEN_HURT_HPP
#define ANIMATIONS_CHICKEN_HURT_HPP

class ChickenHurtAnimation : public Animation {

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
        int jumpHitboxRight = 50;
        int jumpHitboxBottom = 30;
        int jumpHitboxLeft = 70;
        int jumpHitboxColorA = 150;

        for ( int i = 0; i < 5; i++ ) {

            std::string imagePath 
                = "images/chicken/__yellow_chicken_hurt_00" + std::to_string(i) + ".png";

            SDL_Texture* imageTexture = helpers::loadTexture( imagePath );

            Frame frame = {
                .x = x,
                .y = y, 
                .width = 160, 
                .height = 138,
                .imageClipX = 0,
                .imageClipY = 0,
                .imageClipWidth = 160,
                .imageClipHeight = 138,
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

