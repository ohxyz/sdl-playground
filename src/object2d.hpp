#include <string>
#include <vector>
#include <SDL.h>
#include "frame.h"
#include "helpers.h"

#ifndef OBJECT2D_HPP
#define OBJECT2D_HPP

extern SDL_Renderer* gRenderer;

class Object2D {

public:

    Object2D() {}

    Object2D( std::vector<Frame>& frames ) {

        setFrames( frames );
    }

    Object2D( int x, int y, int w, int h ) {

        mFrame.x = x;
        mFrame.y = y;
        mFrame.width = w;
        mFrame.height = h;

        mFrame.imageClipWidth = w;
        mFrame.imageClipHeight = h;

        mCurrentFrame = &mFrame;
    }

    Object2D( int x, int y, int w, int h, std::string imagePath )
    : Object2D( x, y, w, h ) {

        mCurrentFrame->imageTexture = loadTexture( imagePath );
    }

    Object2D( int x, int y, int w, int h, SDL_Color fillColor )
    : Object2D( x, y, w, h ) {

        mFrame.backgroundColorR = fillColor.r;
        mFrame.backgroundColorG = fillColor.g;
        mFrame.backgroundColorB = fillColor.b;
        mFrame.backgroundColorA = fillColor.a;
    }

    Object2D( int x, int y, int w, int h, SDL_Color fillColor, SDL_Color outlineColor )
    : Object2D( x, y ,w, h, fillColor ) {

        mFrame.borderColorR = outlineColor.r;
        mFrame.borderColorG = outlineColor.g;
        mFrame.borderColorB = outlineColor.b;
        mFrame.borderColorA = outlineColor.a;
    }

    ~Object2D() {

    }

    void
    setFrames( std::vector<Frame>& frames ) {

        mAnimationFrames = frames;
    }

    void
    startAnimation( bool repeat=false ) {

        if ( mAnimationFrames.size() == 0 ) {

            SDL_Log( "No frames found!" );
            return;
        }

        mCurrentFrame = &mAnimationFrames[0];
        mAnimationFrameIndex = 0;
        mAnimationTicks = SDL_GetTicks();
        mIsAnimationEnabled = true;
        mIsAnimationFinished = false;
        mCanAnimationRepeat = repeat;
    }

    void
    stopAnimation() {

        mIsAnimationEnabled = false;
    }

    void
    resumeAnimation() {

        mAnimationTicks = SDL_GetTicks();
        mIsAnimationEnabled = true;
    }

    virtual void
    animate() {

        int totalFrames = mAnimationFrames.size();

        if ( totalFrames == 0 ) return;

        int currentTicks = SDL_GetTicks();

        if ( (currentTicks - mAnimationTicks) > mCurrentFrame->duration ) {

            if ( mAnimationFrameIndex < totalFrames -1 ) {
                mAnimationFrameIndex ++;
            }
            else if ( mCanAnimationRepeat ) {
                mAnimationFrameIndex = 0;
            }
            else {
                mIsAnimationFinished = true;
            }

            mCurrentFrame = &mAnimationFrames[ mAnimationFrameIndex ];
            mAnimationTicks = currentTicks;
        }
    }

    void
    render() {

        if ( mAnimationFrames.size() > 0 && mIsAnimationEnabled ) animate();

        SDL_Rect screenRect = {
            mCurrentFrame->x, 
            mCurrentFrame->y, 
            mCurrentFrame->width, 
            mCurrentFrame->height 
        };
        
        // 1. Render background
        SDL_SetRenderDrawColor( 
            gRenderer,
            mCurrentFrame->backgroundColorR, 
            mCurrentFrame->backgroundColorG, 
            mCurrentFrame->backgroundColorB, 
            mCurrentFrame->backgroundColorA 
        );
        SDL_RenderFillRect( gRenderer, &screenRect );
        
        // 2. Render Border
        SDL_SetRenderDrawColor( 
            gRenderer,
            mCurrentFrame->borderColorR, 
            mCurrentFrame->borderColorG, 
            mCurrentFrame->borderColorB, 
            mCurrentFrame->borderColorA 
        );
        SDL_RenderDrawRect( gRenderer, &screenRect );    

        // 2. Render image
        SDL_Rect clipRect = {
            mCurrentFrame->imageClipX,
            mCurrentFrame->imageClipY,
            mCurrentFrame->imageClipWidth,
            mCurrentFrame->imageClipHeight
        };

        SDL_RenderCopyEx( 
            gRenderer, 
            mCurrentFrame->imageTexture,
            &clipRect,
            &screenRect,
            0, 
            NULL, 
            mCurrentFrame->imageClipFlip
        );
    }

    bool isAnimationFinished() { return mIsAnimationFinished; };

private:
    int mAnimationTicks;
    int mAnimationFrameIndex {0};
    std::vector<Frame> mAnimationFrames;
    bool mIsAnimationEnabled {false};
    bool mIsAnimationFinished {false};
    bool mCanAnimationRepeat {false};

    Frame mFrame;
    Frame* mCurrentFrame;
};

#endif