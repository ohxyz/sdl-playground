#include <SDL_image.h>
#include "object2d.hpp"

using std::string;
using std::vector;

extern SDL_Renderer* gRenderer;

Object2D::Object2D() {

}

Object2D::Object2D( std::vector<Frame>& frames ) {

    setFrames( frames );
}

Object2D::Object2D( int x, int y, int w, int h ) {

    mFrame.x = x;
    mFrame.y = y;
    mFrame.width = w;
    mFrame.height = h;

    mFrame.imageClipWidth = w;
    mFrame.imageClipHeight = h;

    mCurrentFrame = &mFrame;
}

Object2D::Object2D( int x, int y, int w, int h, string imagePath )
: Object2D( x, y, w, h ) {

    SDL_Surface* surface = IMG_Load( imagePath.c_str() );

    if ( surface == NULL ) {

        printf( "Failed to load image. SDL Error: %s\n", SDL_GetError() );
    }
    else {
     
        mCurrentFrame->imageTexture = SDL_CreateTextureFromSurface( gRenderer, surface );
        SDL_FreeSurface( surface );
    }
}

Object2D::Object2D( int x, int y, int w, int h, SDL_Color fillColor )
: Object2D( x, y, w, h ) {

    mFrame.backgroundColorR = fillColor.r;
    mFrame.backgroundColorG = fillColor.g;
    mFrame.backgroundColorB = fillColor.b;
    mFrame.backgroundColorA = fillColor.a;
}

Object2D::Object2D( int x, int y, int w, int h, SDL_Color fillColor, SDL_Color outlineColor )
: Object2D( x, y ,w, h, fillColor ) {

    mFrame.borderColorR = outlineColor.r;
    mFrame.borderColorG = outlineColor.g;
    mFrame.borderColorB = outlineColor.b;
    mFrame.borderColorA = outlineColor.a;
}

Object2D::~Object2D() {

}

void
Object2D::setFrames( std::vector<Frame>& frames ) {

    mAnimationFrames = frames;
}

void
Object2D::startAnimation( bool repeat ) {

    if ( mAnimationFrames.size() == 0 ) {

        SDL_Log( "No frames found!" );
        return;
    }

    mCurrentFrame = &mAnimationFrames[0];
    mAnimationFrameIndex = 0;
    mAnimationTicks = SDL_GetTicks();
    mIsAnimationEnabled = true;
    mCanAnimationRepeat = repeat;
}

void
Object2D::stopAnimation() {

    mIsAnimationEnabled = false;
}

void
Object2D::resumeAnimation() {

    mAnimationTicks = SDL_GetTicks();
    mIsAnimationEnabled = true;
}

void
Object2D::animate() {

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

        mCurrentFrame = &mAnimationFrames[ mAnimationFrameIndex ];
        mAnimationTicks = currentTicks;
    }
}

void
Object2D::render() {

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
