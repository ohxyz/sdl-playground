#include "object2d.hpp"

#ifndef CACTUS_HPP
#define CACTUS_HPP

// SDL_Texture* cactusTexture = helpers::loadTexture( "images/cactus.png" );

class Cactus : public Object2D {

    Frame* mFrame;
    int mTicks {0};
    unsigned int mStep {0};
    SDL_Texture* mImageTexture;

public:

    Cactus() {

        mFrame = new Frame;
        mImageTexture = helpers::loadTexture( "images/cactus.png" );
        
        mFrame->x = 360;
        mFrame->y = 386;
        mFrame->width = 64;
        mFrame->height = 83;
        mFrame->backgroundColorA = 100;
        mFrame->imageClipX = 0;
        mFrame->imageClipY = 0;
        mFrame->imageClipWidth = 64;
        mFrame->imageClipHeight = 83;
        mFrame->imageTexture = mImageTexture;
        mFrame->hitboxTop = 10;
        mFrame->hitboxRight = 10;
        mFrame->hitboxBottom = 0;
        mFrame->hitboxLeft = 20;
        mFrame->hitboxColorA = 150;

        setCurrentFrame( mFrame );
        mTicks = SDL_GetTicks();
    }

    ~Cactus() {

        delete mFrame;
        SDL_DestroyTexture( mImageTexture );
    }

    void
    moveLeft() {

        if ( mStep == 0 ) return;

        int currentTicks = SDL_GetTicks();
        auto frame = getCurrentFrame();

        if ( currentTicks - mTicks > frame->duration ) {

            frame->x -= mStep;
            mTicks = currentTicks;
        }
    }

    void
    render() {

        moveLeft();
        // renderBackground();
        // renderHitbox();
        renderImage();
    }

    void
    setStep( int step ) {

        mStep = step;
    }

};

#endif