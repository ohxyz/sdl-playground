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

    Frame* mFrame;
    Frame* mCurrentFrame;

    Move mMovement;
    int mMovementTicks;
    bool mIsMovementStarted {false};
    
    bool mShouldRender {true};

    SDL_Texture* mImageTexture {NULL};

    EventHandler mClickEventHandler;
    EventHandler mTouchEventHandler;

public:

    Object2D() {

        mFrame = new Frame();
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

    virtual void
    startMove() {

        mMovementTicks = SDL_GetTicks();
        mIsMovementStarted = true;
    }

    virtual void
    stopMove() {

        mIsMovementStarted = false;
    }

    virtual void
    moveOnce( Direction aDirection, int aStep ) {

        if ( aDirection == Direction::None || aStep == 0 ) return;

        switch ( aDirection ) {

        case Direction::Up:
            mCurrentFrame->y -= aStep;
            break;

        case Direction::Right:
            mCurrentFrame->x += aStep;
            break;

        case Direction::Down:
            mCurrentFrame->y += aStep;
            break;

        case Direction::Left:
            mCurrentFrame->x -= aStep;
            break;

        case Direction::None:
            break;
        }
    }

    virtual void 
    move() {

        int currentTicks = SDL_GetTicks();

        if ( currentTicks - mMovementTicks > mMovement.interval ) {

            moveOnce( mMovement.direction, mMovement.step );
            mMovementTicks = currentTicks;
        }
    }

    virtual void
    renderBorder() { mCurrentFrame->renderBorder(); }

    virtual void
    renderBackground() { mCurrentFrame->renderBackground(); }

    virtual void
    renderHitbox() { mCurrentFrame->renderHitbox(); }

    virtual void 
    renderImage() { mCurrentFrame->renderImage(); }

    virtual void
    render() {

        if ( !mShouldRender ) return;
        if ( mIsMovementStarted ) move();

        mCurrentFrame->renderBackground();
        mCurrentFrame->renderBorder();
        mCurrentFrame->renderHitbox();
        mCurrentFrame->renderImage();
    }

    bool
    collide( Object2D* target ) {

        return helpers::collide( getHitboxRect(), target->getHitboxRect() );
    }

    virtual SDL_Rect
    getRect() { return mCurrentFrame->getRect(); }

    virtual SDL_Rect
    getHitboxRect() { return mCurrentFrame->getHitboxRect(); }

    Frame*
    getCurrentFrame() { return mCurrentFrame; }
    
    void
    setCurrentFrame( Frame* frame ) { mCurrentFrame = frame; }

    void
    setMovement( Move move ) { mMovement = move; }

    Move
    getMovement() { return mMovement; }

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