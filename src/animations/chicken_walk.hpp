#include <string>
#include <iostream>
#include <vector>
#include "../frame.hpp"
#include "../helpers.hpp"
#include "../animation.hpp"

#ifndef ANIMATIONS_CHICKEN_WALK_HPP
#define ANIMATIONS_CHICKEN_WALK_HPP

class ChickenWalkAnimation : public Animation {

    int mImageWidth = 141;
    int mImageHeight = 122;
    std::string mImageFolderPath = "images/chicken/";

public:

    ChickenWalkAnimation( int x=0, int y=0 ) {

        setFrames( createFrames( x, y ) );
    }

    ~ChickenWalkAnimation() {

        for ( auto &f : mFrames ) SDL_DestroyTexture( f.imageTexture );
    }

    std::vector<Frame>
    createFrames( int x, int y ) {

        std::vector<Frame> frames;
        int totalFrames = 16;

        int hitboxTop = 10;
        int hitboxRight = 45;
        int hitboxBottom = 0;
        int hitboxLeft = 65;
        uint8_t hitboxColorA = 150;
        int frameDuration = 20;

        for ( int i = 0; i < totalFrames; i++ ) {

            std::string imageIndex = i < 10 ? "0" + std::to_string(i) : std::to_string(i);
            std::string imagePath = mImageFolderPath + "__yellow_chicken_walk_0" + imageIndex + ".png";
            SDL_Texture* imageTexture = helpers::loadTexture( imagePath );

            Frame frame;
            frame.x = x; 
            frame.y = y; 
            frame.width = mImageWidth; 
            frame.height = mImageHeight;
            frame.imageClipX = 0;
            frame.imageClipY = 0;
            frame.imageClipWidth = mImageWidth;
            frame.imageClipHeight = mImageHeight;
            frame.imageClipFlip = SDL_FLIP_HORIZONTAL;
            frame.imageTexture = imageTexture;
            frame.hitboxTop = hitboxTop;
            frame.hitboxRight = hitboxRight;
            frame.hitboxBottom = hitboxBottom;
            frame.hitboxLeft = hitboxLeft;
            frame.hitboxColorA = hitboxColorA;
            frame.duration = frameDuration;
            
            frames.push_back( frame );
        }

        return frames;
    }
};


#endif