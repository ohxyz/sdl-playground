#include <string>
#include <iostream>
#include <vector>
#include "../frame.h"
#include "../helpers.hpp"
#include "../animation.hpp"

#ifndef ANIMATIONS_CHICKEN_WALK_HPP
#define ANIMATIONS_CHICKEN_WALK_HPP

class ChickenWalkAnimation : public Animation {

public:

    ChickenWalkAnimation( int x=0, int y=0 ) {

        setFrames( createIdleFrames( x, y ) );
    }

    ~ChickenWalkAnimation() {

        for ( auto &f : mFrames ) SDL_DestroyTexture( f.imageTexture );
    }

    std::vector<Frame>
    createIdleFrames( int x, int y ) {

        std::vector<Frame> frames;
        int totalFrames = 16;

        for ( int i = 0; i < totalFrames; i++ ) {

            std::string imageIndex = i < 10 ? "0" + std::to_string(i) : std::to_string(i);
            std::string imagePath = "images/chicken/__yellow_chicken_walk_0" + imageIndex + ".png";
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
                .hitboxTop = 10,
                .hitboxRight = 50,
                .hitboxBottom = 10,
                .hitboxLeft = 70,
                .hitboxColorA = 150,
                .duration = 20
            };

            frames.push_back( frame );
        }

        return frames;
    }
};


#endif