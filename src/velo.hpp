#include "object2d.hpp"
#include "sprite.hpp"
#include <vector>
#include <SDL.h>
#include <math.h>
#include "helpers.h"

#ifndef VELO_HPP
#define VELO_HPP

class Velo : public Object2D {

public:

    Velo() : Object2D() {

        mScreenRect = {50, 300, 200, 199};
        mWalkSprite = new Sprite( "images/walk.png", { .x=0, .y=0, .w=800, .h=795 }, 4, 4, SDL_FLIP_HORIZONTAL );
        mWalkFrames = mWalkSprite->createFrames( mScreenRect, 40 );

        //debug
        // for ( auto &f : mWalkFrames ) {

        //     f.backgroundColorA = 100;
        //     f.hitboxTop = 10;
        //     f.hitboxRight = 60;
        //     f.hitboxBottom = 50;
        //     f.hitboxLeft = 10;
        //     f.hitboxColorA = 200;
        // }   

        mJumpFrames = createJumpFrames();
    }

    ~Velo() {

        delete mWalkSprite;
    }

    void
    walk() {
        
        if ( mCurrentState == Walk
            || ( mCurrentState == Jump && !isAnimationFinished() )
        ) {

            return;
        }

        mCurrentState = Walk;
        setFrames( mWalkFrames );
        startAnimation( true );
    }

    void
    jump() {

        if ( mCurrentState == Jump && !isAnimationFinished() ) return;

        mCurrentState = Jump;
        setFrames( mJumpFrames );
        startAnimation( false );
    }

    void
    animate() {

        Object2D::animate();

        if ( mCurrentState == Jump && isAnimationFinished() ) {
            walk();
        }
    }

    std::vector<Frame>
    createJumpFrames() {

        Frame frame;
        std::vector<Frame> frames;

        int totalFrames = 21;
        int middleIndex = totalFrames / 2;
        float exponent = 2.2;
        int highest = round( pow( middleIndex, exponent ) );
        int eachHeight;
        int newY;

        int clipX;
        int clipY;
        SDL_Texture* imageTexture = helpers::loadTexture( "images/jump.png" );
        int frameDuration = 40;
        
        // Prepare for jump
        for ( int j = 0; j < 3; j ++ ) {

            frame = {
                .x = mScreenRect.x, 
                .y = mScreenRect.y, 
                .width = mScreenRect.w, 
                .height = mScreenRect.h,
                .imageClipX = mScreenRect.w * j,
                .imageClipY = 0,
                .imageClipWidth = mScreenRect.w,
                .imageClipHeight = mScreenRect.h,
                .imageClipFlip = SDL_FLIP_HORIZONTAL,
                .imageTexture = imageTexture,
                .duration = frameDuration
            };
            frames.push_back( frame );
        }

        // Start to jump
        for ( int i = 0; i < totalFrames; i ++ ) {

            eachHeight = - round( pow( abs(i - middleIndex), exponent ) ) + highest;
            newY = mScreenRect.y - eachHeight;

            if ( i == 0 ) {
                clipX = 3 * mScreenRect.w;
                clipY = 0;
            }
            else if ( i == 1 ) {
                clipX = 0;
                clipY = mScreenRect.h;
            }
            else if ( i == 2 ) {
                clipX = mScreenRect.w;
                clipY = mScreenRect.h;
            }
            else if ( i == 3 ) {
                clipX = mScreenRect.w * 2;
                clipY = mScreenRect.h;
            }
            else if ( i == totalFrames - 5 ) {
                clipX = mScreenRect.w * 3;
                clipY = mScreenRect.h;
            }
            else if ( i == totalFrames - 4 ) {
                clipX = 0;
                clipY = mScreenRect.h * 2;
            }
            else if ( i == totalFrames - 3 ) {
                clipX = mScreenRect.w;
                clipY = mScreenRect.h * 2;
            }
            else if ( i == totalFrames - 2 ) {
                clipX = mScreenRect.w * 2;
                clipY = mScreenRect.h * 2;
            }
            else if ( i == totalFrames - 1 ) {
                clipX = mScreenRect.w * 3;
                clipY = mScreenRect.h * 2;
            }

            frame = {
                .x = mScreenRect.x, 
                .y = newY, 
                .width = mScreenRect.w, 
                .height = mScreenRect.h,
                .imageClipX = clipX,
                .imageClipY = clipY,
                .imageClipWidth = mScreenRect.w,
                .imageClipHeight = mScreenRect.h,
                .imageClipFlip = SDL_FLIP_HORIZONTAL,
                .imageTexture = imageTexture,
                .duration = frameDuration
            };

            frames.push_back( frame );
        }

        // for ( auto &f : frames ) {

        //     f.backgroundColorA = 100;
        //     f.hitboxTop = 10;
        //     f.hitboxRight = 60;
        //     f.hitboxBottom = 50;
        //     f.hitboxLeft = 10;
        //     f.hitboxColorA = 200;
        // }   

        return frames;
    }

    void
    render() {

        animate();
        renderBackground();
        renderHitbox();
        renderImage();
    }

private:

    SDL_Rect mScreenRect;
    Sprite* mWalkSprite;
    std::vector<Frame> mWalkFrames;
    std::vector<Frame> mJumpFrames;
    enum State { Idle, Walk, Jump } mCurrentState {Idle};

};

#endif