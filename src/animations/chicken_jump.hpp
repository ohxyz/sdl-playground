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
        uint8_t jumpHitboxColorA = 0;
        int jumpFrameDuration = 11;

        for ( int i = 0; i < 12; i++ ) {

            std::string imageIndex = i < 10 ? "0" + std::to_string(i) : std::to_string(i);
            std::string imagePath 
                = mImageFolderPath + "__yellow_chicken_jump_0" + imageIndex + ".png";
            SDL_Texture* imageTexture = helpers::loadTexture( imagePath );
            mTextures.push_back( imageTexture );
        }

        std::vector<Frame*> frames;

        // Jump starting, 2 images
        for ( int i = 0; i < 2; i++ ) {

            SDL_Texture* imageTexture = mTextures[i+1];

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
            frame->duration = jumpFrameDuration;

            frames.push_back( frame );
        }

        // Jump rise and fall 
        double peakHeight = 123.0;
        double vertexY = y - peakHeight;
        double exponent = 2.7;
        double vertexX = pow( y - vertexY, 1 / exponent );

        // Jump rise
        int totalFramesOfJumpRise = 23;
        double factorOfJumpRise = vertexX / (double)totalFramesOfJumpRise;

        for ( int i = 0; i < totalFramesOfJumpRise; i++ ) {

            int newY = round( pow( abs( vertexX - factorOfJumpRise * i ), exponent ) ) + vertexY;

            // SDL_Log( "@@ Jump rise %d", newY );

            SDL_Texture* imageTexture;

            // Use one image for every 2 frames;
            if ( i < 2 ) imageTexture = mTextures[3];
            else if ( i < 4 ) imageTexture = mTextures[4];
            else imageTexture = mTextures[5];

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
            frame->duration = jumpFrameDuration;

            frames.push_back( frame );
        }

        // Jump fall
        int totalFramesOfJumpFall = round( 0.9 * (float)totalFramesOfJumpRise );
        double factorOfJumpFall = vertexX / (double)totalFramesOfJumpFall;

        for ( int i = 0; i < totalFramesOfJumpFall; i++ ) {

            int newY = round( pow( factorOfJumpFall * i, exponent ) ) + vertexY;

            // SDL_Log( "@@ Jump fall %d", newY );

            SDL_Texture* imageTexture = mTextures[5];

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
            frame->duration = jumpFrameDuration;

            frames.push_back( frame );
        }

        // Jump ending, 2 images
        for ( int i = 0; i < 2; i++ ) {

            SDL_Texture* imageTexture = mTextures[9+i];

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
            frame->duration = jumpFrameDuration;

            frames.push_back( frame );
        }

        return frames;
    }
};


#endif