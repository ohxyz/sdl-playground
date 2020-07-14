#include <string>
#include <SDL.h>
#include <vector>
#include "frame.h"

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

extern SDL_Renderer* gRenderer;

class Animation {

protected:

    std::vector<Frame> mFrames;
    Frame* mCurrentFrame {NULL};
    int mCurrentFrameIndex {0};
    int mTicks {0};
    bool mIsFinished {false};
    bool mIsEnabled {false};
    bool mCanRepeat {false};

public:

    Animation() {

    }

    ~Animation() {

        mFrames.clear();
    }

    Frame*
    animate() {

        if ( !mIsEnabled ) return NULL;

        int totalFrames = mFrames.size();

        if ( totalFrames == 0 ) return NULL;

        int currentTicks = SDL_GetTicks();

        if ( (currentTicks - mTicks) > mCurrentFrame->duration ) {

            if ( mCurrentFrameIndex < totalFrames -1 ) {
                mCurrentFrameIndex ++;
            }
            else if ( mCanRepeat ) {
                mCurrentFrameIndex = 0;
            }
            else {
                mIsFinished = true;
            }

            mCurrentFrame = &mFrames[ mCurrentFrameIndex ];
            mTicks = currentTicks;
        }

        return mCurrentFrame;
    }

    void
    start( bool repeat=false ) {

        if ( mFrames.size() == 0 ) {

            SDL_Log( "Error: No frames found!" );
            return;
        }

        mCurrentFrame = &mFrames[0];
        mCurrentFrameIndex = 0;
        mTicks = SDL_GetTicks();
        mIsFinished = false;
        mIsEnabled = true;
        mCanRepeat = repeat;
    }

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
    renderCurrentFrame() {

        SDL_Rect clipRect = {
            mCurrentFrame->imageClipX,
            mCurrentFrame->imageClipY,
            mCurrentFrame->imageClipWidth,
            mCurrentFrame->imageClipHeight
        };

        SDL_Rect targetRect = {
            mCurrentFrame->x,
            mCurrentFrame->y,
            mCurrentFrame->width,
            mCurrentFrame->height
        };

        SDL_RenderCopyEx( 
            gRenderer,
            mCurrentFrame->imageTexture,
            &clipRect,
            &targetRect,
            0, 
            NULL, 
            mCurrentFrame->imageClipFlip
        );
    }

    void
    setFrameDuration( int ms ) {

        for ( auto &f : mFrames ) f.duration = ms;
    }

    void
    setFrames( std::vector<Frame> frames ) { mFrames = frames; }

    std::vector<Frame>*
    getFrames() { return &mFrames; }

    Frame*
    getCurrentFrame() { return mCurrentFrame; }

    bool
    isFinished() { return mIsFinished; }
};

#endif