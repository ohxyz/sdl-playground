#include "object2d.hpp"
#include "structs.hpp"
#include <string>

#ifndef SCROLLABLE_HPP
#define SCROLLABLE_HPP

class Scrollable : public Object2D {

    bool mShouldRepeatHorizontal {false};

public:

    Scrollable( int x, int y, int w, int h, std::string imagePath )
    : Object2D( x, y, w, h, imagePath ) {

    }

    Scrollable( int x, int y, int w, int h, std::string imagePath, SDL_Rect imageClipRect, Move movement )
    : Object2D( x, y, w, h, imagePath, imageClipRect ) {

        mMovement = movement;
        mShouldRepeatHorizontal = true;
        mCurrentFrame->width = mCurrentFrame->width * 2;
    }

    Scrollable( int x, int y, int w, int h, std::string imagePath, Move movement )
    : Scrollable( x, y, w, h, imagePath, {0, 0, 0, 0}, movement ) {

    }

    void
    startMove() {

        Object2D::startMove();

        if ( mShouldRepeatHorizontal ) {

            if ( mMovement.direction == Direction::Left ) {
                mCurrentFrame->x = 0;
            }
            else if ( mMovement.direction == Direction::Right ) {
                mCurrentFrame->x = -mCurrentFrame->imageClipWidth;
            }
        }
    }

    void
    move() {

        if ( mMovement.direction == Direction::None || mMovement.step == 0 ) return;

        int currentTicks = SDL_GetTicks();

        if ( currentTicks - mMovementTicks > mMovement.interval ) {

            switch ( mMovement.direction ) {

            case Direction::Right:

                if ( mShouldRepeatHorizontal && mCurrentFrame->x >= -mMovement.step ) {

                    mCurrentFrame->x = -mCurrentFrame->imageClipWidth;
                }
                else {

                    mCurrentFrame->x += mMovement.step;
                }

                break;

            case Direction::Left:

                if ( mShouldRepeatHorizontal 
                        && mCurrentFrame->x + mCurrentFrame->imageClipWidth <= mMovement.step ) {

                    mCurrentFrame->x = 0;
                }
                else {

                    mCurrentFrame->x -= mMovement.step;
                }

                break;
            }

            mMovementTicks = currentTicks;
        }
    }

    void
    setRepeatHorizontal( bool flag ) {

        mShouldRepeatHorizontal = flag; 
    }

    void
    render() {

        if ( mIsMovementStarted ) move();

        renderImage();
    }


};

#endif