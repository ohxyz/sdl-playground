#include <string>
#include <iostream>
#include <vector>
#include "../frame.hpp"
#include "../helpers.hpp"
#include "../animation.hpp"

#ifndef ANIMATIONS_CHICKEN_JUMP_HPP
#define ANIMATIONS_CHICKEN_JUMP_HPP

class ChickenJumpAnimation : public Animation {

    int mImageWidth = 141;
    int mImageHeight = 122;
    std::string mImageFolderPath = "images/chicken/";

    std::vector<SDL_Texture*> mTextures;

public:

    ChickenJumpAnimation( int x=0, int y=0 ) {

        setFrames( createFrames( x, y ) );
    }

    ~ChickenJumpAnimation() {

        for ( auto &f : mFrames ) SDL_DestroyTexture( f.imageTexture );
    }

    std::vector<Frame>
    createFrames( int x, int y ) {

        int jumpHitboxTop = 10;
        int jumpHitboxRight = 45;
        int jumpHitboxBottom = 15;
        int jumpHitboxLeft = 65;
        uint8_t jumpHitboxColorA = 150;
        int frameDuration = 20;

        for ( int i = 0; i < 12; i++ ) {

            std::string imageIndex = i < 10 ? "0" + std::to_string(i) : std::to_string(i);
            std::string imagePath 
                = mImageFolderPath + "__yellow_chicken_jump_0" + imageIndex + ".png";
            SDL_Texture* imageTexture = helpers::loadTexture( imagePath );
            mTextures.push_back( imageTexture );
        }

        std::vector<Frame> frames;

        // Jump starting
        for ( int i = 0; i < 2; i++ ) {

            SDL_Texture* imageTexture = mTextures[i];

            Frame frame = {
                .x = x, 
                .y = y, 
                .width = mImageWidth, 
                .height = mImageHeight,
                // .backgroundColorA = 100,
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
                .duration = frameDuration
            };

            frames.push_back( frame );
        }

        // Jump in the air
        int totalInAir = 23;
        int middleIndex = totalInAir / 2;
        float exponent = 2.0;
        int highest = round( pow( middleIndex, exponent ) );

        for ( int i = 0; i < totalInAir; i++ ) {

            int eachHeight = - round( pow( abs(i - middleIndex), exponent ) ) + highest;
            int newY = y - eachHeight;
            SDL_Texture* imageTexture;

            if ( i == 0 ) imageTexture = mTextures[2];
            else if ( i == 1 ) imageTexture = mTextures[3];
            else if ( i == 2 ) imageTexture = mTextures[4];
            else if ( i == 3 ) imageTexture = mTextures[5];
            else if ( i == totalInAir - 4 ) imageTexture = mTextures[6];
            else if ( i == totalInAir - 3 ) imageTexture = mTextures[7];
            else if ( i == totalInAir - 2 ) imageTexture = mTextures[8];
            else if ( i == totalInAir - 1 ) imageTexture = mTextures[9];
            else imageTexture = mTextures[5];

            Frame frame = {
                .x = x, 
                .y = newY,
                .width = mImageWidth, 
                .height = mImageHeight,
                // .backgroundColorA = 100,
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
                .duration = frameDuration
            };

            frames.push_back( frame );
        }

        // Jump ending
        for ( int i = 0; i < 2; i++ ) {

            SDL_Texture* imageTexture = mTextures[10+i];

            Frame frame = {
                .x = x, 
                .y = y, 
                .width = mImageWidth, 
                .height = mImageHeight,
                // .backgroundColorA = 100,
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
                .duration = frameDuration
            };

            frames.push_back( frame );
        }

        return frames;
    }
};


#endif