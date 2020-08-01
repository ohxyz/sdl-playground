#include <iostream>
#include "object2d.hpp"
#include "helpers.hpp"
#include <math.h>
#include "animation.hpp"
#include "animations/chicken_hurt.hpp"
#include "animations/chicken_walk.hpp"
#include "animations/chicken_walk_shoot.hpp"
#include "animations/chicken_jump.hpp"
#include "animations/chicken_skid.hpp"
#include "animations/chicken_run.hpp"

#ifndef CHICKEN_HPP
#define CHICKEN_HPP

class Chicken : public Object2D {

    enum State { Idle, Walk, WalkShoot, Jump, Hurt, Skid, Run } mCurrentState { Idle };
    Animation* mCurrentAnimation;
    ChickenHurtAnimation* mHurtAnimation;
    ChickenWalkAnimation* mWalkAnimation;
    ChickenWalkShootAnimation* mWalkShootAnimation;
    ChickenJumpAnimation* mJumpAnimation;
    ChickenSkidAnimation* mSkidAnimation;
    ChickenRunAnimation* mRunAnimation;

    Frame* mCurrentFrame;

public:

    Chicken() {

        int startX = -25;
        int startY = 246;

        mHurtAnimation = new ChickenHurtAnimation( startX, startY );
        mWalkAnimation = new ChickenWalkAnimation( startX, startY );
        mWalkShootAnimation = new ChickenWalkShootAnimation( startX, startY );
        mJumpAnimation = new ChickenJumpAnimation( startX, startY );
        mSkidAnimation = new ChickenSkidAnimation( startX, startY );
        mRunAnimation  = new ChickenRunAnimation( startX, startY );
        mCurrentAnimation = mWalkAnimation;
    }

    ~Chicken() {

        delete mHurtAnimation;
        delete mWalkAnimation;
        delete mWalkShootAnimation;
        delete mJumpAnimation;
        delete mSkidAnimation;
        delete mRunAnimation;
    }

    void
    init() {
    
        walk();
    }

    void
    run() {

        if ( mCurrentState == Run ) return;

        mCurrentState = Run;
        mCurrentAnimation = mRunAnimation;
        mRunAnimation->start( true );
    }

    void
    walk() {

        if ( mCurrentState == Walk ) return;

        mCurrentState = Walk;
        mCurrentAnimation = mWalkAnimation;
        mWalkAnimation->start( true );
    }

    void
    walkShoot() {

        if ( mCurrentState == WalkShoot 
            || ( mCurrentState != Walk && !mCurrentAnimation->isFinished() )
        ) {
            return;
        }

        mCurrentState = WalkShoot;
        mCurrentAnimation = mWalkShootAnimation;
        mWalkShootAnimation->start( 1 );
    }

    void
    skid() {

        if ( mCurrentState == Skid 
            || ( mCurrentState != Walk && !mCurrentAnimation->isFinished() )
        ) {
            return;
        }

        mCurrentState = Skid;
        mCurrentAnimation = mSkidAnimation;
        mSkidAnimation->start( 3 );
    }

    void
    jump() {

        if ( mCurrentState == Jump 
            || ( mCurrentState != Walk && !mCurrentAnimation->isFinished() )
        ) {
            return;
        }
        
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
        for ( auto &f : hurtFrames ) f->y = mCurrentFrame->y;
    }

    void
    render() {

        if ( ( mCurrentState == Jump || mCurrentState == Skid || mCurrentState == WalkShoot ) 
                && mCurrentAnimation->isFinished() 
        ) {

            mCurrentState = Walk;
            mCurrentAnimation = mWalkAnimation;
            // Reset to first walk animation frame
            mWalkAnimation->start( true );
        }

        mCurrentFrame = mCurrentAnimation->animate();

        if ( mCurrentFrame != NULL ) {

            mCurrentFrame->renderImage();
            // mCurrentFrame->renderHitbox();
        }
    }

    void 
    setFrameDuration( int ms ) {

        mWalkAnimation->setFrameDuration( ms );
        mJumpAnimation->setFrameDuration( ms );
    }

    SDL_Rect
    getHitboxRect() { return mCurrentFrame->getHitboxRect(); }

};

#endif