#include <iostream>
#include "object2d.hpp"
#include "helpers.hpp"
#include <math.h>
#include "animation.hpp"
#include "animations/chicken_hurt.hpp"
#include "animations/chicken_walk.hpp"
#include "animations/chicken_jump.hpp"

#ifndef CHICKEN_HPP
#define CHICKEN_HPP

class Chicken : public Object2D {

    enum State { Idle, Walk, Jump, Hurt } mCurrentState { Idle };
    Animation* mCurrentAnimation;
    ChickenHurtAnimation* mHurtAnimation;
    ChickenWalkAnimation* mWalkAnimation;
    ChickenJumpAnimation* mJumpAnimation;

public:

    Chicken() {

        mHurtAnimation = new ChickenHurtAnimation( -25, 230 );
        mWalkAnimation = new ChickenWalkAnimation( -25, 230 );
        mJumpAnimation = new ChickenJumpAnimation( -25, 230 );
        mCurrentAnimation = mWalkAnimation;
    }

    ~Chicken() {

        delete mHurtAnimation;
        delete mWalkAnimation;
        delete mJumpAnimation;
    }

    void
    init() {
        
        walk();
    }

    void
    walk() {

        if ( mCurrentState == Walk || (mCurrentState == Jump && !mJumpAnimation->isFinished()) ) {
            return;
        }

        mCurrentState = Walk;
        mCurrentAnimation = mWalkAnimation;
        mWalkAnimation->start( true );
    }

    void
    jump() {

        if ( mCurrentState == Jump && !mJumpAnimation->isFinished() ) return;

        mCurrentState = Jump;
        mCurrentAnimation = mJumpAnimation;
        mJumpAnimation->start( false );
    }

    void
    hurt() {

        if ( mCurrentState == Hurt && !mHurtAnimation->isFinished() ) return;
        
        mCurrentState = Hurt;
        updateHurtFrames();
        mCurrentAnimation = mHurtAnimation;
        mHurtAnimation->start( false );
    }

    void
    updateHurtFrames() {    

        auto hurtFrames = mHurtAnimation->getFrames();
        for ( auto &f : *hurtFrames ) f.y = mCurrentFrame->y;
    }

    void
    render() {

        if ( mCurrentState == Jump && mCurrentAnimation->isFinished() ) {

            mCurrentAnimation = mWalkAnimation;
        }

        mCurrentFrame = mCurrentAnimation->animate();

        if ( mCurrentFrame != NULL ) {

            renderImage();
            // renderBackground();
            // renderHitbox();
        }
    }

    void setFrameDuration( int ms ) {

        mWalkAnimation->setFrameDuration( ms );
        mJumpAnimation->setFrameDuration( ms );
    }

};

#endif