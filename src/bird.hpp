#include <SDL.h>
#include "frame.hpp"
#include "structs.hpp"
#include "object2d.hpp"
#include "animations/bird_fly.hpp"
#include <string>
#include "timer.hpp"

#ifndef BIRD_HPP
#define BIRD_HPP

class Bird : public Object2D {

    Frame* mFrame;
    BirdFlyAnimation* mFlyAnimation;

    int mNewX;
    Move mMovement;

    Timer* mTimer;

public:

    Bird( int aX, int aY ) {

        mFlyAnimation = new BirdFlyAnimation( aX, aY );
        mFlyAnimation->start( true );
        mNewX = aX;

        mFrame = new Frame();
        mTimer = new Timer();
    }

    ~Bird() {

        delete mFrame;
        delete mFlyAnimation;
        delete mTimer;
    }

    void
    startMove() {

        mTimer->start( mMovement.interval );
    }

    void
    move() {

        if ( mTimer->isTimeOut() ) {

            mFrame = mFlyAnimation->animate();
            mFrame->x = mNewX;
            mNewX -= mMovement.step;
            setCurrentFrame( mFrame );

            mTimer->reset();
        }
    }

    void
    stopMove() {

        mTimer->stop();
    }

    void
    setMovement( Move move ) { 

        mMovement = move; 
    }

    void
    render() {

        if ( mTimer->isStarted() ) move();

        // mFrame->renderHitbox();
        mFrame->renderImage();
    }
};

#endif