#include "object2d.hpp"
#include "helpers.h"

#ifndef LAND_HPP
#define LAND_HPP

class Land : public Object2D {

    Frame* mFrame;
    unsigned int mStep {0};
    SDL_Texture* mImageTexture;
    int mTicks;

public:

    Land() {

        mFrame = new Frame;
        mImageTexture = helpers::loadTexture( "images/land.png" );

        init();
        
        mTicks = SDL_GetTicks();
    }

    ~Land() {

        delete mFrame;
        SDL_DestroyTexture( mImageTexture );
    }

    void
    init() {

        mFrame->x = 0;
        mFrame->y = 467;
        mFrame->width = 420; // 360 + 60
        mFrame->height = 173;
        mFrame->imageClipX = 0;
        mFrame->imageClipY = 0;
        mFrame->imageClipWidth = 60;
        mFrame->imageClipHeight = 173;
        mFrame->imageTexture = mImageTexture;

        setCurrentFrame( mFrame );
    }

    void scrollLeft() {

        if ( mStep == 0 ) return; 

        int currentTicks = SDL_GetTicks();

        if ( currentTicks - mTicks > mFrame->duration ) {

            if ( mFrame->x - mStep > -mFrame->imageClipWidth ) {
                mFrame->x -= mStep;
            }
            else {
                mFrame->x = 0;
            }

            mTicks = currentTicks;
        }
    }

    void
    setStep( int dist ) {

        mStep = dist;
    }

    void
    setFrameDuration( int ms ) {

        mFrame->duration = ms;
    }

    void
    render() {

        scrollLeft();
        renderImage();
    }
};

#endif