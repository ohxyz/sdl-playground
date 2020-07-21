#include <SDL.h>
#include "frame.hpp"
#include "structs.hpp"
#include "animations/vulture_fly.hpp"

#ifndef VULTURE_HPP
#define VULTURE_HPP

class Vulture {

    VultureFlyAnimation* mFlyAnimation;

    Frame mFrame;
    int mNewX;
    Move mMovement;

    int mMovementTicks;
    bool mIsMovementStarted {false};

public:

    Vulture( int aX, int aY ) {

        mFlyAnimation = new VultureFlyAnimation( aX, aY );
        mFlyAnimation->start( true );

        mMovement = { .direction=Direction::Left, .step=5, .interval=20 };
        mNewX = aX;
    }

    ~Vulture() {

        delete mFlyAnimation;
    }

    void
    startMove() {

        mMovementTicks = SDL_GetTicks();
        mIsMovementStarted = true;
    }

    void
    stopMove() {

        mIsMovementStarted = false;
    }

    void
    move() {

        int currentTicks = SDL_GetTicks();

        if ( currentTicks - mMovementTicks > mMovement.interval ) {

            mFrame = *mFlyAnimation->animate();
            mFrame.x = mNewX;
            mNewX -= mMovement.step;

            mMovementTicks = currentTicks;
        }
    }

    void
    render() {

        if ( mIsMovementStarted ) move();
        mFrame.renderImage();
    }
};

#endif