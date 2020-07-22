#include <string>
#include <SDL.h>
#include <vector>
#include "frame.hpp"
#include <iostream>

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

extern SDL_Renderer* gRenderer;

class Animation {

    std::vector<Frame*> mFrames;
    Frame* mCurrentFrame {NULL};
    int mCurrentFrameIndex {0};
    int mTicks {0};
    bool mIsFinished {false};
    bool mIsEnabled {false};
    uint32_t mRepeats {0}; // 0 - Infinitely, 1 - Repeat once, n - Repeat n times;
    uint32_t mCurrentRepeat {1};

public:

    Animation() {

    }

    ~Animation() {
        
        mFrames.clear();
    }

    Frame*
    animate() {

        if ( !mIsEnabled ) {

            SDL_Log( "Error: Animation not enabled!" );
            return NULL;
        }

        int totalFrames = mFrames.size();

        if ( totalFrames == 0 ) return NULL;

        int currentTicks = SDL_GetTicks();

        if ( (currentTicks - mTicks) > mCurrentFrame->duration ) {

            if ( mCurrentFrameIndex < totalFrames -1 ) {
                mCurrentFrameIndex ++;
            }
            else if ( mRepeats == 0 ) {

                mCurrentFrameIndex = 0;
            }
            else if ( mCurrentRepeat < mRepeats ) {

                mCurrentFrameIndex = 0;
                mCurrentRepeat ++;
            }
            else {
                mIsFinished = true;
            }

            mCurrentFrame = mFrames[ mCurrentFrameIndex ];
            mTicks = currentTicks;
        }

        return mCurrentFrame;
    }

    void
    start( int aRepeats ) {

        if ( mFrames.size() == 0 ) {

            SDL_Log( "Error: No frames found!" );
            return;
        }

        mCurrentFrame = mFrames[0];
        mCurrentFrameIndex = 0;
        mTicks = SDL_GetTicks();
        mIsFinished = false;
        mIsEnabled = true;
        mRepeats = aRepeats;
        mCurrentRepeat = 1;
    }

    void
    start( bool aCanRepeat ) { aCanRepeat ? start(0) : start(1); }

    void
    start() { start(1); }

    void
    stop() {

        mIsEnabled = false;
    }

    void
    resume() {

        mTicks = SDL_GetTicks();
        mIsEnabled = true;
    }

    void
    render() {

        mCurrentFrame->renderHitbox();
        mCurrentFrame->renderImage();
    }

    void
    setFrameDuration( int ms ) {

        for ( auto f : mFrames ) f->duration = ms;
    }

    void
    setFrames( std::vector<Frame*> frames ) { mFrames = frames; }

    std::vector<Frame*>
    getFrames() { return mFrames; }

    Frame*
    getCurrentFrame() { return mCurrentFrame; }

    bool
    isFinished() { return mIsFinished; }
};

#endif