#include <SDL.h>
#include "frame.hpp"
#include "structs.hpp"
#include "object2d.hpp"
#include "animations/vulture_fly.hpp"
#include <string>

#ifndef VULTURE_HPP
#define VULTURE_HPP

class Vulture : public Object2D {

    Frame* mFrame;
    VultureFlyAnimation* mFlyAnimation;

    int mNewX;
    Move mMovement;

    int mMovementTicks;
    bool mIsMovementStarted {false};

public:

    Vulture( int aX, int aY ) {

        mFlyAnimation = new VultureFlyAnimation( aX, aY );
        mFlyAnimation->start( true );
        mNewX = aX;

        mFrame = new Frame();
    }

    ~Vulture() {

        delete mFrame;
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

            mFrame = mFlyAnimation->animate();
            mFrame->x = mNewX;
            mNewX -= mMovement.step;
            setCurrentFrame( mFrame );

            mMovementTicks = currentTicks;
        }
    }

    void
    setMovement( Move move ) { mMovement = move; }

    void
    render() {

        if ( mIsMovementStarted ) move();

        mFrame->renderHitbox();
        mFrame->renderImage();
    }
};

#endif