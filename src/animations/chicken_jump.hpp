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

        for ( int i = 0; i < 12; i++ ) {

            std::string imageIndex = i < 10 ? "0" + std::to_string(i) : std::to_string(i);
            std::string imagePath 
                = mImageFolderPath + "__yellow_chicken_jump_0" + imageIndex + ".png";
            SDL_Texture* imageTexture = helpers::loadTexture( imagePath );
            mTextures.push_back( imageTexture );
        }

        std::vector<Frame*> frames;

        // Jump starting
        for ( int i = 0; i < 3; i++ ) {

            SDL_Texture* imageTexture = mTextures[i];

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
            frame->duration = 10;

            frames.push_back( frame );
        }

        // 40 * 2.3
        int totalFramesInAir = 40;
        double highest = 123.0;
        double exponent = 2.3;
        // double middle = sqrt( highest );
        double middle = pow( highest, 1 / exponent );
        double factor = middle / ( totalFramesInAir / 2.0 );

        int jumpInAirFrameDuration = 10;

        int middleIndex = totalFramesInAir / 2;

        for ( int i = 0; i < totalFramesInAir; i++ ) {

            int eachHeight = -round( pow( abs( middle - factor * i ), exponent ) ) + highest;
            int newY = y - eachHeight;

            // SDL_Log( "@@ %d", eachHeight );

            SDL_Texture* imageTexture;

            // Use one image for every 2 frames;
            if ( i < 2 ) imageTexture = mTextures[3];
            else if ( i < 4 ) imageTexture = mTextures[4];
            else if ( i >= 4 &&  i <= totalFramesInAir - 9 ) imageTexture = mTextures[5];
            else if ( i > totalFramesInAir - 3 ) imageTexture = mTextures[9];
            else if ( i > totalFramesInAir - 5 ) imageTexture = mTextures[8];
            else if ( i > totalFramesInAir - 7 ) imageTexture = mTextures[7];
            else if ( i > totalFramesInAir - 9 ) imageTexture = mTextures[6];

            Frame* frame = new Frame();

            frame->x = x; 
            frame->y = newY;
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
            frame->duration = jumpInAirFrameDuration;

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
            frame->duration = 10;

            frames.push_back( frame );
        }

        return frames;
    }
};


#endif