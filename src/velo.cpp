#include "velo.hpp"
#include <math.h>
#include "helpers.hpp"

Velo::Velo() : Object2D() {

    mScreenRect = {50, 350, 200, 199};

    mWalkSprite = new Sprite( "images/walk.png", { .x=0, .y=0, .w=800, .h=795 }, 4, 4, SDL_FLIP_HORIZONTAL );
    mWalkFrames = mWalkSprite->createFrames( mScreenRect, 50 );

    mJumpSprite = new Sprite( "images/jump.png", { .x=0, .y=0, .w=800, .h=596 }, 4, 3, SDL_FLIP_HORIZONTAL );
    mJumpFrames = mJumpSprite->createFrames( mScreenRect, 50 );
}

Velo::~Velo() {

    delete mWalkSprite;
    delete mJumpSprite;
}

void
Velo::walk() {

    setFrames( mWalkFrames );
    startAnimation( true );
}

void
Velo::jump() {

    Frame frame;
    std::vector<Frame> frames;

    int totalFrames = 11;
    int middleIndex = totalFrames / 2;
    float exponent = 2.5;
    int highest = round( pow( middleIndex, exponent ) );
    int eachHeight;
    int newY;

    int imageClipX;
    int imageClipY;
    int imageClipWidth;
    int imageClipHeight;

    SDL_Texture* imageTexture = loadTexture( "images/jump.png" );

    for ( int i = 0; i < totalFrames; i ++ ) {

        eachHeight = - round( pow( abs(i - middleIndex), exponent ) ) + highest;
        newY = mScreenRect.y - eachHeight;

        SDL_Log( "each %d", eachHeight ); 

        frame = {
            .x = mScreenRect.x, 
            .y = newY, 
            .width = mScreenRect.w, 
            .height = mScreenRect.h,
            .backgroundColorA = 134,
            .imageClipX = 3 * mScreenRect.w,
            .imageClipY = 0,
            .imageClipWidth = mScreenRect.w,
            .imageClipHeight = mScreenRect.h,
            .imageTexture = imageTexture,
            .duration = 50
        };

        frames.push_back( frame );
    }

    setFrames( frames );
    startAnimation( true );
}