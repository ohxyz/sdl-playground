#include "object2d.hpp"

#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

class Obstacle : public Object2D {

    Frame* mFrame;
    int mTicks {0};
    unsigned int mStep {0};
    SDL_Texture* mImageTexture;

public:

    Obstacle() {

        mFrame = new Frame;
        mImageTexture = helpers::loadTexture( "images/obstacle-1.png" );
        
        mFrame->x = 360;
        mFrame->y = 340;
        mFrame->width = 40;
        mFrame->height = 75;
        mFrame->backgroundColorA = 100;
        mFrame->imageClipX = 0;
        mFrame->imageClipY = 0;
        mFrame->imageClipWidth = 40;
        mFrame->imageClipHeight = 75;
        mFrame->imageTexture = mImageTexture;
        mFrame->hitboxTop = 5;
        mFrame->hitboxRight = 5;
        mFrame->hitboxBottom = 0;
        mFrame->hitboxLeft = 5;
        mFrame->hitboxColorA = 150;

        setCurrentFrame( mFrame );
        mTicks = SDL_GetTicks();
    }

    ~Obstacle() {

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