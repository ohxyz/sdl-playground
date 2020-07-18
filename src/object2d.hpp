#include <string>
#include <vector>
#include <SDL.h>
#include "frame.hpp"
#include "structs.hpp"
#include "helpers.hpp"
#include <iostream>

#ifndef OBJECT2D_HPP
#define OBJECT2D_HPP

typedef void (*EventHandler)(void);

extern SDL_Renderer* gRenderer;

class Object2D {

protected:

    Frame* mFrame;
    Frame* mCurrentFrame;

    Move mMovement;
    int mMovementTicks;
    bool mIsMovementStarted {false};

    EventHandler mClickEventHandler;
    EventHandler mTouchEventHandler;

    bool mShouldRender {true};

    SDL_Texture* mImageTexture {NULL};

public:

    Object2D() {

        mFrame = new Frame;
        mCurrentFrame = mFrame;
    }

    Object2D( Frame* frame ) 
    : Object2D() {

        mCurrentFrame = frame;
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

        delete mFrame;
        if ( mImageTexture != NULL ) SDL_DestroyTexture( mImageTexture );
    }

    void
    startMove() {

        mMovementTicks = SDL_GetTicks();
        mIsMovementStarted = true;
    }

    void
    stopMove() {

        mIsMovementStarted = false;
    }

    void 
    moveOnce() {

        if ( mMovement.direction == Direction::None || mMovement.step == 0 ) return;

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
    }

    void 
    move() {

        int currentTicks = SDL_GetTicks();

        if ( currentTicks - mMovementTicks > mMovement.interval ) {

            moveOnce();
            mMovementTicks = currentTicks;
        }
    }

    void
    renderBorder() { mCurrentFrame->renderBorder(); }

    void
    renderBackground() { mCurrentFrame->renderBackground(); }

    void
    renderHitbox() { mCurrentFrame->renderHitbox(); }

    void 
    renderImage() { mCurrentFrame->renderImage(); }

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
    getCurrentFrame() { return mCurrentFrame; }

    SDL_Rect
    getRect() { return mCurrentFrame->getRect(); }

    SDL_Rect
    getHitboxRect() { return mCurrentFrame->getHitboxRect(); }

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

        mCurrentFrame->setHitbox( top, right, bottom, left );
    }

    void
    setHitboxColor( int r, int g, int b, int a ) {

        mCurrentFrame->setHitboxColor( r, g, b, a );
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
    isWithinRect( int x, int y ) { return mCurrentFrame->isWithinRect( x, y ); }

    bool
    isVisible() { return mShouldRender; }
};

#endif