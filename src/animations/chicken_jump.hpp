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
    std::vector<Frame*> mFrames;

public:

    ChickenJumpAnimation( int x=0, int y=0 ) {

        mFrames = createFrames( x, y );
        setFrames( mFrames );
    }

    ~ChickenJumpAnimation() {

        for ( auto &t : mTextures ) SDL_DestroyTexture( t );
        for ( auto &f : mFrames ) SDL_DestroyTexture( f->imageTexture );
        mFrames.clear();
    }

    std::vector<Frame*>
    createFrames( int x, int y ) {

        int jumpHitboxTop = 15;
        int jumpHitboxRight = 45;
        int jumpHitboxBottom = 15;
        int jumpHitboxLeft = 65;
        uint8_t jumpHitboxColorA = 150;
        int frameDuration = 30;

        for ( int i = 0; i < 12; i++ ) {

            std::string imageIndex = i < 10 ? "0" + std::to_string(i) : std::to_string(i);
            std::string imagePath 
                = mImageFolderPath + "__yellow_chicken_jump_0" + imageIndex + ".png";
            SDL_Texture* imageTexture = helpers::loadTexture( imagePath );
            mTextures.push_back( imageTexture );
        }

        std::vector<Frame*> frames;

        // Jump starting
        for ( int i = 0; i < 2; i++ ) {

            SDL_Texture* imageTexture = mTextures[i];

            Frame* frame = new Frame();
            frame->x = x; 
            frame->y = y; 
            frame->width = mImageWidth; 
            frame->height = mImageHeight;
            // frame->backgroundColorA = 100;
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

            Frame* frame = new Frame();

            frame->x = x; 
            frame->y = newY;
            frame->width = mImageWidth; 
            frame->height = mImageHeight;
            // frame->backgroundColorA = 100;
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

        // Jump ending
        for ( int i = 0; i < 2; i++ ) {

            SDL_Texture* imageTexture = mTextures[10+i];

            Frame* frame = new Frame();

            frame->x = x;
            frame->y = y; 
            frame->width = mImageWidth; 
            frame->height = mImageHeight;
            // frame->backgroundColorA = 100;
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