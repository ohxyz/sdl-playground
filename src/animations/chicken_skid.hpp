#include <string>
#include <iostream>
#include <vector>
#include "../frame.hpp"
#include "../helpers.hpp"
#include "../animation.hpp"

#ifndef ANIMATIONS_CHICKEN_SKID_HPP
#define ANIMATIONS_CHICKEN_SKID_HPP

class ChickenSkidAnimation : public Animation {

    int mImageWidth = 141;
    int mImageHeight = 122;
    std::string mImageFolderPath = "images/chicken/";

public:

    ChickenSkidAnimation( int x=0, int y=0 ) {

        setFrames( createFrames( x, y ) );
    }

    ~ChickenSkidAnimation() {

        for ( auto &f : mFrames ) SDL_DestroyTexture( f.imageTexture );
    }

    std::vector<Frame>
    createFrames( int x, int y ) {

        std::vector<Frame> frames;
        int totalFrames = 10;

        int hitboxTop = 35;
        int hitboxRight = 40;
        int hitboxBottom = 0;
        int hitboxLeft = 65;
        uint8_t hitboxColorA = 150;
        int frameDuration = 20;

        for ( int i = 0; i < totalFrames; i++ ) {

            std::string imageIndex = i < 10 ? "0" + std::to_string(i) : std::to_string(i);
            std::string imagePath = mImageFolderPath + "__yellow_chicken_skid_0" + imageIndex + ".png";
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
                .hitboxTop = hitboxTop,
                .hitboxRight = hitboxRight,
                .hitboxBottom = hitboxBottom,
                .hitboxLeft = hitboxLeft,
                .hitboxColorA = hitboxColorA,
                .duration = frameDuration
            };

            frames.push_back( frame );
        }

        return frames;
    }
};


#endif