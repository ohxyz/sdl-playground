#include <iostream>
#include "object2d.hpp"
#include "helpers.h"
#include <math.h>

#ifndef CHICKEN_HPP
#define CHICKEN_HPP

class Chicken : public Object2D {

    std::vector<Frame> mWalkFrames;
    std::vector<Frame> mJumpFrames;
    std::vector<SDL_Texture*> mJumpTexture;
    std::vector<Frame> mHurtFrames;
    SDL_Rect mScreenRect;
    
    int mFrameDuration {1000};
    enum State { Idle, Walk, Jump, Hurt } mCurrentState { Idle };

public:

    Chicken() {

        mScreenRect = { -25, 285, 160, 138 };
        mWalkFrames = createWalkFrames();
        mJumpFrames = createJumpFrames();
        mHurtFrames = createHurtFrames();
    }

    ~Chicken() {

        for ( auto &f : mWalkFrames ) SDL_DestroyTexture( f.imageTexture );
        for ( auto t : mJumpTexture ) SDL_DestroyTexture( t );
    }

    void
    init() {
        
        walk();
    }

    void
    walk() {

        if ( mCurrentState == Walk || (mCurrentState == Jump && !isAnimationFinished()) ) {
            return;
        }

        mCurrentState = Walk;
        setAnimationFrames( mWalkFrames );
        startAnimate( true );
    }

    void
    jump() {

        if ( mCurrentState == Jump && !isAnimationFinished() ) return;

        mCurrentState = Jump;
        setAnimationFrames( mJumpFrames );
        startAnimate( false );
    }

    void
    hurt() {

        if ( mCurrentState == Hurt && !isAnimationFinished() ) return;
        
        mCurrentState = Hurt;
        setAnimationFrames( mHurtFrames );
        updateHurtFrames();
        startAnimate( false );
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

        int jumpHitboxTop = 10;
        int jumpHitboxRight = 50;
        int jumpHitboxBottom = 30;
        int jumpHitboxLeft = 70;
        int jumpHitboxColorA = 150;

        for ( int i = 0; i < 12; i++ ) {

            std::string imageIndex = i < 10 ? "0" + std::to_string(i) : std::to_string(i);
            std::string imagePath = "images/chicken/__yellow_chicken_jump_0" + imageIndex + ".png";
            SDL_Texture* imageTexture = helpers::loadTexture( imagePath );
            mJumpTexture.push_back( imageTexture );
        }

        std::vector<Frame> frames;

        // Jump starting
        for ( int i = 0; i < 2; i++ ) {

            SDL_Texture* imageTexture = mJumpTexture[i];

            Frame frame = {
                .x = mScreenRect.x, 
                .y = mScreenRect.y, 
                .width = mScreenRect.w, 
                .height = mScreenRect.h,
                // .backgroundColorA = 100,
                .imageClipX = 0,
                .imageClipY = 0,
                .imageClipWidth = mScreenRect.w,
                .imageClipHeight = mScreenRect.h,
                .imageClipFlip = SDL_FLIP_HORIZONTAL,
                .imageTexture = imageTexture,
                .hitboxTop = jumpHitboxTop,
                .hitboxRight = jumpHitboxRight,
                .hitboxBottom = jumpHitboxBottom,
                .hitboxLeft = jumpHitboxLeft,
                .hitboxColorA = jumpHitboxColorA,
                .duration = mFrameDuration
            };

            frames.push_back( frame );
        }

        // Jump in the air
        int totalInAir = 21;
        int middleIndex = totalInAir / 2;
        float exponent = 2.1;
        int highest = round( pow( middleIndex, exponent ) );

        for ( int i = 0; i < totalInAir; i++ ) {

            int eachHeight = - round( pow( abs(i - middleIndex), exponent ) ) + highest;
            int newY = mScreenRect.y - eachHeight;
            SDL_Texture* imageTexture;

            if ( i == 0 ) imageTexture = mJumpTexture[2];
            else if ( i == 1 ) imageTexture = mJumpTexture[3];
            else if ( i == 2 ) imageTexture = mJumpTexture[4];
            else if ( i == 3 ) imageTexture = mJumpTexture[5];
            else if ( i == totalInAir - 4 ) imageTexture = mJumpTexture[6];
            else if ( i == totalInAir - 3 ) imageTexture = mJumpTexture[7];
            else if ( i == totalInAir - 2 ) imageTexture = mJumpTexture[8];
            else if ( i == totalInAir - 1 ) imageTexture = mJumpTexture[9];
            else imageTexture = mJumpTexture[5];

            Frame frame = {
                .x = mScreenRect.x, 
                .y = newY,
                .width = mScreenRect.w, 
                .height = mScreenRect.h,
                // .backgroundColorA = 100,
                .imageClipX = 0,
                .imageClipY = 0,
                .imageClipWidth = mScreenRect.w,
                .imageClipHeight = mScreenRect.h,
                .imageClipFlip = SDL_FLIP_HORIZONTAL,
                .imageTexture = imageTexture,
                .hitboxTop = jumpHitboxTop,
                .hitboxRight = jumpHitboxRight,
                .hitboxBottom = jumpHitboxBottom,
                .hitboxLeft = jumpHitboxLeft,
                .hitboxColorA = jumpHitboxColorA,
                .duration = mFrameDuration
            };

            frames.push_back( frame );
        }

        // Jump ending
        for ( int i = 0; i < 2; i++ ) {

            SDL_Texture* imageTexture = mJumpTexture[10+i];

            Frame frame = {
                .x = mScreenRect.x, 
                .y = mScreenRect.y, 
                .width = mScreenRect.w, 
                .height = mScreenRect.h,
                // .backgroundColorA = 100,
                .imageClipX = 0,
                .imageClipY = 0,
                .imageClipWidth = mScreenRect.w,
                .imageClipHeight = mScreenRect.h,
                .imageClipFlip = SDL_FLIP_HORIZONTAL,
                .imageTexture = imageTexture,
                .hitboxTop = jumpHitboxTop,
                .hitboxRight = jumpHitboxRight,
                .hitboxBottom = jumpHitboxBottom,
                .hitboxLeft = jumpHitboxLeft,
                .hitboxColorA = jumpHitboxColorA,
                .duration = mFrameDuration
            };

            frames.push_back( frame );
        }

        return frames;
    }

    std::vector<Frame>
    createWalkFrames() {

        std::vector<Frame> frames;
        int totalFrames = 16;

        for ( int i = 0; i < totalFrames; i++ ) {

            std::string imageIndex = i < 10 ? "0" + std::to_string(i) : std::to_string(i);
            std::string imagePath = "images/chicken/__yellow_chicken_walk_0" + imageIndex + ".png";
            SDL_Texture* imageTexture = helpers::loadTexture( imagePath );

            Frame frame = {
                .x = mScreenRect.x, 
                .y = mScreenRect.y, 
                .width = mScreenRect.w, 
                .height = mScreenRect.h,
                // .backgroundColorA = 100,
                .imageClipX = 0,
                .imageClipY = 0,
                .imageClipWidth = mScreenRect.w,
                .imageClipHeight = mScreenRect.h,
                .imageClipFlip = SDL_FLIP_HORIZONTAL,
                .imageTexture = imageTexture,
                .hitboxTop = 10,
                .hitboxRight = 50,
                .hitboxBottom = 10,
                .hitboxLeft = 70,
                .hitboxColorA = 150,
                .duration = mFrameDuration
            };

            frames.push_back( frame );
        }

        return frames;
    }


    void
    updateHurtFrames() {    

        auto currentFrame = getCurrentFrame();

        for ( auto &f : mHurtFrames ) f.y = currentFrame->y;
    }

    std::vector<Frame>
    createHurtFrames() {

        std::vector<Frame> frames;

        // Use jump hitbox to debug
        int jumpHitboxTop = 10;
        int jumpHitboxRight = 50;
        int jumpHitboxBottom = 30;
        int jumpHitboxLeft = 70;
        int jumpHitboxColorA = 150;

        for ( int i = 0; i < 5; i++ ) {

            std::string imagePath 
                = "images/chicken/__yellow_chicken_hurt_00" + std::to_string(i) + ".png";

            SDL_Texture* imageTexture = helpers::loadTexture( imagePath );

            Frame frame = {
                .x = mScreenRect.x,
                .y = mScreenRect.y, 
                .width = mScreenRect.w, 
                .height = mScreenRect.h,
                .imageClipX = 0,
                .imageClipY = 0,
                .imageClipWidth = mScreenRect.w,
                .imageClipHeight = mScreenRect.h,
                .imageClipFlip = SDL_FLIP_HORIZONTAL,
                .imageTexture = imageTexture,
                .hitboxTop = jumpHitboxTop,
                .hitboxRight = jumpHitboxRight,
                .hitboxBottom = jumpHitboxBottom,
                .hitboxLeft = jumpHitboxLeft,
                .hitboxColorA = jumpHitboxColorA,
                .duration = 10
            };

            frames.push_back( frame );
        }

        return frames;
    }

    void
    render() {

        animate();
        // renderBackground();
        // renderHitbox();
        renderImage();
    }

    void setFrameDuration( int ms ) {

        for ( auto &f : mWalkFrames ) f.duration = ms;
        for ( auto &f : mJumpFrames ) f.duration = ms;
    }

};

#endif