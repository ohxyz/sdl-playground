#include <iostream>
#include "object2d.hpp"
#include "helpers.hpp"
#include <math.h>
#include "animation.hpp"
#include "animations/chicken_hurt.hpp"
#include "animations/chicken_walk.hpp"
#include "animations/chicken_jump.hpp"
#include "animations/chicken_skid.hpp"

#ifndef CHICKEN_HPP
#define CHICKEN_HPP

class Chicken : public Object2D {

    enum State { Idle, Walk, Jump, Hurt, Skid } mCurrentState { Idle };
    Animation* mCurrentAnimation;
    ChickenHurtAnimation* mHurtAnimation;
    ChickenWalkAnimation* mWalkAnimation;
    ChickenJumpAnimation* mJumpAnimation;
    ChickenSkidAnimation* mSkidAnimation;

    Frame* mCurrentFrame;

public:

    Chicken() {

        int startX = -25;
        int startY = 246;

        mHurtAnimation = new ChickenHurtAnimation( startX, startY );
        mWalkAnimation = new ChickenWalkAnimation( startX, startY );
        mJumpAnimation = new ChickenJumpAnimation( startX, startY );
        mSkidAnimation = new ChickenSkidAnimation( startX, startY );
        mCurrentAnimation = mWalkAnimation;
    }

    ~Chicken() {

        delete mHurtAnimation;
        delete mWalkAnimation;
        delete mJumpAnimation;
        delete mSkidAnimation;
    }

    void
    init() {
        
        walk();
    }

    void
    walk() {

        if ( mCurrentState == Walk ) return;

        mCurrentState = Walk;
        mCurrentAnimation = mWalkAnimation;
        mWalkAnimation->start( true );
    }

    void
    skid() {

        if ( ( mCurrentState == Skid && !mSkidAnimation->isFinished() )
            || ( mCurrentState == Jump && !mJumpAnimation->isFinished() )
        ) {
            return;
        }

        mCurrentState = Skid;
        mCurrentAnimation = mSkidAnimation;
        mSkidAnimation->start( 3 );
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
        for ( auto &f : hurtFrames ) f->y = mCurrentFrame->y;
    }

    void
    render() {

        if ( ( mCurrentState == Jump || mCurrentState == Skid ) 
                && mCurrentAnimation->isFinished() 
        ) {

            mCurrentAnimation = mWalkAnimation;
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