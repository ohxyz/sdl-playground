#include "object2d.hpp"
#include "structs.hpp"
#include <string>

#ifndef SCROLLABLE_HPP
#define SCROLLABLE_HPP

class Scrollable : public Object2D {

    bool mShouldRepeatHorizontal {false};

    Move mMovement;
    int mMovementTicks {0};
    bool mIsMovementStarted {false};

public:

    Scrollable( int x, int y, int w, int h, std::string imagePath, SDL_Rect imageClipRect, Move movement )
    : Object2D( x, y, w, h, imagePath, imageClipRect ) {

        mMovement = movement;
        mShouldRepeatHorizontal = true;
        getCurrentFrame()->width = getCurrentFrame()->width * 2;
    }

    Scrollable( int x, int y, int w, int h, std::string imagePath, Move movement )
    : Scrollable( x, y, w, h, imagePath, {0, 0, 0, 0}, movement ) {

    }

    void
    startMove() {

        mMovementTicks = SDL_GetTicks();
        mIsMovementStarted = true;

        if ( mShouldRepeatHorizontal ) {

            if ( mMovement.direction == Direction::Left ) {
                getCurrentFrame()->x = 0;
            }
            else if ( mMovement.direction == Direction::Right ) {
                getCurrentFrame()->x = -getCurrentFrame()->imageClipWidth;
            }
        }
    }

    void
    stopMove() {

        mIsMovementStarted = false;
    }

    void
    move() {

        if ( mMovement.direction == Direction::None || mMovement.step == 0 ) return;

        int currentTicks = SDL_GetTicks();

        if ( currentTicks - mMovementTicks > mMovement.interval ) {

            switch ( mMovement.direction ) {

            case Direction::Right:

                if ( mShouldRepeatHorizontal && getCurrentFrame()->x >= -mMovement.step ) {

                    getCurrentFrame()->x = -getCurrentFrame()->imageClipWidth;
                }
                else {

                    getCurrentFrame()->x += mMovement.step;
                }

                break;

            case Direction::Left:

                if ( mShouldRepeatHorizontal 
                        && getCurrentFrame()->x + getCurrentFrame()->imageClipWidth <= mMovement.step ) {

                    getCurrentFrame()->x = 0;
                }
                else {

                    getCurrentFrame()->x -= mMovement.step;
                }

                break;
            }

            mMovementTicks = currentTicks;
        }
    }

    void
    setMovement( Move move ) {

        mMovement = move;
    }

    void
    setRepeatHorizontal( bool flag ) {

        mShouldRepeatHorizontal = flag; 
    }

    void
    render() {

        if ( mIsMovementStarted ) move();

        getCurrentFrame()->renderImage();
    }
};

#endif