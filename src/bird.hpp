#include <SDL.h>
#include "frame.hpp"
#include "structs.hpp"
#include "object2d.hpp"
#include "animations/bird_fly.hpp"
#include <string>

#ifndef BIRD_HPP
#define BIRD_HPP

class Bird : public Object2D {

    Frame* mFrame;
    BirdFlyAnimation* mFlyAnimation;

    int mNewX;
    Move mMovement;

    int mMovementTicks;
    bool mIsMovementStarted {false};

public:

    Bird( int aX, int aY ) {

        mFlyAnimation = new BirdFlyAnimation( aX, aY );
        mFlyAnimation->start( true );
        mNewX = aX;

        mFrame = new Frame();
    }

    ~Bird() {

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

        // mFrame->renderHitbox();
        mFrame->renderImage();
    }
};

#endif