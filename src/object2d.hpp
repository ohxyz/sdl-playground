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

    Object2D( Frame frame ) {

        mCurrentFrame = &frame;
    }

    Object2D( std::vector<Frame>& frames ) {

        setFrames( frames );
    }

    Object2D( int x, int y, int w, int h ) {

        mCurrentFrame = new Frame;

        mCurrentFrame->x = x;
        mCurrentFrame->y = y;
        mCurrentFrame->width = w;
        mCurrentFrame->height = h;

    }

    Object2D( int x, int y, int w, int h, std::string imagePath, SDL_Rect imageClipRect={0,0,0,0} )
    : Object2D( x, y, w, h ) {

        if ( imageClipRect.w == 0 || imageClipRect.h == 0 ) {

            mCurrentFrame->imageClipX = 0;
            mCurrentFrame->imageClipY = 0;
            mCurrentFrame->imageClipWidth = w;
            mCurrentFrame->imageClipHeight = h;
        }
        else {

            mCurrentFrame->imageClipX = imageClipRect.x;
            mCurrentFrame->imageClipY = imageClipRect.y;
            mCurrentFrame->imageClipWidth = imageClipRect.w;
            mCurrentFrame->imageClipHeight = imageClipRect.h;
        }

        mCurrentFrame->imageTexture = helpers::loadTexture( imagePath );
    }

    Object2D( int x, int y, int w, int h, SDL_Color fillColor )
    : Object2D( x, y, w, h ) {

        mCurrentFrame->backgroundColorR = fillColor.r;
        mCurrentFrame->backgroundColorG = fillColor.g;
        mCurrentFrame->backgroundColorB = fillColor.b;
        mCurrentFrame->backgroundColorA = fillColor.a;
    }

    Object2D( int x, int y, int w, int h, SDL_Color fillColor, SDL_Color outlineColor )
    : Object2D( x, y ,w, h, fillColor ) {

        mCurrentFrame->borderColorR = outlineColor.r;
        mCurrentFrame->borderColorG = outlineColor.g;
        mCurrentFrame->borderColorB = outlineColor.b;
        mCurrentFrame->borderColorA = outlineColor.a;
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

    void
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
    renderBackground() {

        auto rect = getCurrentRect();
        SDL_SetRenderDrawColor( 
            gRenderer,
            mCurrentFrame->backgroundColorR, 
            mCurrentFrame->backgroundColorG, 
            mCurrentFrame->backgroundColorB, 
            mCurrentFrame->backgroundColorA 
        );
        SDL_RenderFillRect( gRenderer, &rect );
    }

    void 
    renderBorder() {

        auto rect = getCurrentRect();
        SDL_SetRenderDrawColor( 
            gRenderer,
            mCurrentFrame->borderColorR, 
            mCurrentFrame->borderColorG, 
            mCurrentFrame->borderColorB, 
            mCurrentFrame->borderColorA 
        );
        SDL_RenderDrawRect( gRenderer, &rect );
    }

    void 
    renderHitbox() {

        auto rect = getCurrentHitboxRect();
        SDL_SetRenderDrawColor( 
            gRenderer,
            mCurrentFrame->hitboxColorR, 
            mCurrentFrame->hitboxColorG, 
            mCurrentFrame->hitboxColorB,
            mCurrentFrame->hitboxColorA 
        );
        SDL_RenderFillRect( gRenderer, &rect );
    }

    void renderImage() {

        if ( mCurrentFrame->imageTexture == NULL ) {
            return;
        }

        int targetWidth = mCurrentFrame->imageClipWidth > mCurrentFrame->width  
                        ? mCurrentFrame->width 
                        : mCurrentFrame->imageClipWidth;

        int targetHeight = mCurrentFrame->imageClipHeight > mCurrentFrame->height
                         ? mCurrentFrame->height
                         : mCurrentFrame->imageClipHeight;

        SDL_Rect clipRect = {
            mCurrentFrame->imageClipX,
            mCurrentFrame->imageClipY,
            targetWidth,
            targetHeight
        };

        SDL_Rect targetRect = {
            mCurrentFrame->x,
            mCurrentFrame->y,
            targetWidth,
            targetHeight
        };

        while ( true ) {

            // Repeat on x-axis
            while ( true ) {

                SDL_RenderCopyEx( 
                    gRenderer, 
                    mCurrentFrame->imageTexture,
                    &clipRect,
                    &targetRect,
                    0, 
                    NULL, 
                    mCurrentFrame->imageClipFlip
                );

                if ( !mCurrentFrame->imageClipRepeatX ) {
                    break;
                }

                targetRect.x += mCurrentFrame->imageClipWidth;

                if ( targetRect.x > mCurrentFrame->x + mCurrentFrame->width ) {
                    break;
                }

                if ( targetRect.x + mCurrentFrame->imageClipWidth > mCurrentFrame->x + mCurrentFrame->width ) {
                    targetRect.w = mCurrentFrame->x + mCurrentFrame->width - targetRect.x;
                    clipRect.w = targetRect.w;
                }
                else {
                    targetRect.w = mCurrentFrame->imageClipWidth;
                }
            }

            if ( !mCurrentFrame->imageClipRepeatY ) {
                break;
            }

            // Repeat on y-axis
            // Reset
            targetRect.x = mCurrentFrame->x;
            targetRect.w = targetWidth;
            clipRect.w = targetWidth;

            targetRect.y += mCurrentFrame->imageClipHeight;

            if ( targetRect.y > mCurrentFrame->y + mCurrentFrame->height ) {
                break;
            }

            if ( targetRect.y + mCurrentFrame->imageClipHeight > mCurrentFrame->y + mCurrentFrame->height ) {
                targetRect.h = mCurrentFrame->y + mCurrentFrame->height - targetRect.y;
                clipRect.h = targetRect.h;
            }
            else {
                targetRect.h = mCurrentFrame->imageClipHeight;
            }
        }
    }

    virtual void
    render() {

        if ( mIsAnimationEnabled ) animate();

        renderBackground();
        renderBorder();
        renderHitbox();
        renderImage();
    }

    bool 
    isAnimationFinished() { 

        return mIsAnimationFinished; 
    }

    Frame*
    getCurrentFrame() { 

        return mCurrentFrame; 
    }

    SDL_Rect
    getCurrentRect() {

        SDL_Rect rect = {
            mCurrentFrame->x,
            mCurrentFrame->y,
            mCurrentFrame->width,
            mCurrentFrame->height
        };

        return rect;
    }

    SDL_Rect
    getCurrentHitboxRect() {

        SDL_Rect rect = {
            mCurrentFrame->x + mCurrentFrame->hitboxLeft,
            mCurrentFrame->y + mCurrentFrame->hitboxTop,
            mCurrentFrame->width - mCurrentFrame->hitboxRight - mCurrentFrame->hitboxLeft,
            mCurrentFrame->height - mCurrentFrame->hitboxBottom - mCurrentFrame->hitboxTop
        };

        return rect;
    }

    bool
    isAnimationEnabled() {

        return mIsAnimationEnabled;
    }

private:

    int mAnimationTicks;
    int mAnimationFrameIndex {0};
    std::vector<Frame> mAnimationFrames;
    bool mIsAnimationEnabled {false};
    bool mIsAnimationFinished {true};
    bool mCanAnimationRepeat {false};
    Frame* mCurrentFrame;
};

#endif