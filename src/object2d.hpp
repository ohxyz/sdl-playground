#include <string>
#include <vector>
#include <SDL.h>
#include "frame.h"
#include "structs.hpp"
#include "helpers.hpp"
#include <iostream>

#ifndef OBJECT2D_HPP
#define OBJECT2D_HPP

typedef void (*EventHandler)(void);

extern SDL_Renderer* gRenderer;

class Object2D {

protected:

    Frame mFrame;
    Frame* mCurrentFrame;

    Move mMovement;
    int mMovementTicks;
    int mCurrentMovementTicks;
    bool mIsMovementStarted {false};

    EventHandler mClickEventHandler;
    EventHandler mTouchEventHandler;

    bool mShouldRender {true};

    SDL_Texture* mImageTexture {NULL};

public:

    Object2D() {

        mCurrentFrame = &mFrame;
    }

    Object2D( Frame frame ) 
    : Object2D() {

        mFrame = frame;
        mCurrentFrame = &mFrame;
    }

    Object2D( int x, int y, int w, int h )
    : Object2D() {

        mCurrentFrame->x = x;
        mCurrentFrame->y = y;
        mCurrentFrame->width = w;
        mCurrentFrame->height = h;
    }

    Object2D( int x, int y, int w, int h, SDL_Rect imageClipRect )
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
    }

    Object2D( int x, int y, int w, int h, SDL_Texture* imageTexture, SDL_Rect imageClipRect={0,0,0,0} )
    : Object2D( x, y, w, h, imageClipRect ) {

        mCurrentFrame->imageTexture = imageTexture;
    }

    Object2D( int x, int y, int w, int h, std::string imagePath, SDL_Rect imageClipRect={0,0,0,0} )
    : Object2D( x, y, w, h, imageClipRect ) {

        mImageTexture = helpers::loadTexture( imagePath );
        mCurrentFrame->imageTexture = mImageTexture;
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

        if ( mImageTexture != NULL ) SDL_DestroyTexture( mImageTexture );
    }

    void
    startMove() {

        mMovementTicks = SDL_GetTicks();
        mCurrentMovementTicks = mMovementTicks;
        mIsMovementStarted = true;
    }

    void
    stopMove() {

        mIsMovementStarted = false;
    }

    void 
    move() {

        if ( mMovement.direction == Direction::None || mMovement.step == 0 ) return;

        mCurrentMovementTicks = SDL_GetTicks();

        if ( mCurrentMovementTicks - mMovementTicks > mMovement.interval ) {

            switch ( mMovement.direction ) {

            case Direction::Up:
                mCurrentFrame->y -= mMovement.step;
                break;

            case Direction::Right:
                mCurrentFrame->x += mMovement.step;
                break;

            case Direction::Down:
                mCurrentFrame->y += mMovement.step;
                break;

            case Direction::Left:
                mCurrentFrame->x -= mMovement.step;
                break;
            }

            mMovementTicks = mCurrentMovementTicks;
        }
    }

    void
    renderBackground() {

        auto rect = getRect();
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

        auto rect = getRect();
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

        auto rect = getHitboxRect();
        SDL_SetRenderDrawColor( 
            gRenderer,
            mCurrentFrame->hitboxColorR, 
            mCurrentFrame->hitboxColorG, 
            mCurrentFrame->hitboxColorB,
            mCurrentFrame->hitboxColorA 
        );
        SDL_RenderFillRect( gRenderer, &rect );
    }

    void 
    renderImage() {

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

        if ( !mShouldRender ) return;
        if ( mIsMovementStarted ) move();

        renderBackground();
        renderBorder();
        renderHitbox();
        renderImage();
    }

    Frame*
    getCurrentFrame() { 

        return mCurrentFrame; 
    }

    SDL_Rect
    getRect() {

        SDL_Rect rect = {
            mCurrentFrame->x,
            mCurrentFrame->y,
            mCurrentFrame->width,
            mCurrentFrame->height
        };

        return rect;
    }

    SDL_Rect
    getHitboxRect() {

        SDL_Rect rect = {
            mCurrentFrame->x + mCurrentFrame->hitboxLeft,
            mCurrentFrame->y + mCurrentFrame->hitboxTop,
            mCurrentFrame->width - mCurrentFrame->hitboxRight - mCurrentFrame->hitboxLeft,
            mCurrentFrame->height - mCurrentFrame->hitboxBottom - mCurrentFrame->hitboxTop
        };

        return rect;
    }

    void
    setCurrentFrame( Frame* frame ) { mCurrentFrame = frame; }

    void
    setCurrentFrameDuration( int ms ) { mCurrentFrame->duration = ms; }

    void
    setMovement( Move move ) { mMovement = move; }

    void
    setMovementDirection( Direction d ) { mMovement.direction = d; }

    void
    setMovementStep( int s ) { mMovement.step = s; }
    
    void
    setMovementInterval( int i ) { mMovement.interval = i; }

    void
    setX( int v ) { mCurrentFrame->x = v; }

    int
    getX() { return mCurrentFrame->x; }

    void
    setY( int v ) { mCurrentFrame->y = v; }

    int
    getY() { return mCurrentFrame->y; }

    int
    getWidth() { return mCurrentFrame->width; }

    int
    getHeight() { return mCurrentFrame->height; }

    void
    setHitbox( int top, int right, int bottom, int left ) {

        mCurrentFrame->hitboxTop = top;
        mCurrentFrame->hitboxRight = right;
        mCurrentFrame->hitboxBottom = bottom;
        mCurrentFrame->hitboxLeft = left;
    }

    void
    setHitboxColor( int r, int g, int b, int a ) {

        mCurrentFrame->hitboxColorR = r;
        mCurrentFrame->hitboxColorG = g;
        mCurrentFrame->hitboxColorB = b;
        mCurrentFrame->hitboxColorA = a;
    }

    void
    setShouldRender( bool flag ) { mShouldRender = flag; }

    void 
    onClick( EventHandler handler ) { mClickEventHandler = handler; }

    void 
    click() { mClickEventHandler(); }

    void
    onTouch( EventHandler handler ) { mTouchEventHandler = handler; }

    void
    touch() { mTouchEventHandler(); }

    bool
    isWithinRect( int x, int y ) {

        return ( x >= mCurrentFrame->x && x <= mCurrentFrame->x + mCurrentFrame->width
            && y >= mCurrentFrame->y && y <= mCurrentFrame->y + mCurrentFrame->height
        );
    }

    bool
    isVisible() { return mShouldRender; }
};

#endif